#pragma once

// CrashHandler.h
//
// Writes a minidump + text log on unhandled exceptions.
//
// KEY DESIGN CONSTRAINT
// ─────────────────────
// Neither MiniDumpWriteDump nor any DbgHelp/dbgcore API may be called directly
// from a Vectored Exception Handler (VEH).  Both APIs activate internal Windows
// activation contexts via RtlActivateActivationContext.  When the fault fires on
// a thread-pool thread (e.g. TpWaitForTimer, a WinRT coroutine resume, or a PPL
// task continuation) the thread's activation-context stack is in an indeterminate
// state, so the matching RtlDeactivateActivationContextUnsafeFast dereferences a
// freed/invalid record => second 0xC0000005 *inside* the crash handler.
//
// SOLUTION: the VEH captures the EXCEPTION_POINTERS by value into a global, then
// spawns a brand-new plain thread (CreateThread, not a pool thread) and waits for
// it to finish.  The new thread has a clean, freshly-initialized activation-context
// stack, so MiniDumpWriteDump works correctly there.

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <DbgHelp.h>
#include <fstream>
#include <string>
#include <ctime>

#pragma comment(lib, "DbgHelp.lib")

namespace CrashHandler {

// ── shared state between VEH and dump thread ──────────────────────────────────

struct DumpRequest {
    EXCEPTION_RECORD  ExceptionRecord;
    CONTEXT           Context;
    DWORD             ThreadId;
};

static DumpRequest g_dumpRequest;

// ── helpers ───────────────────────────────────────────────────────────────────

static std::wstring getDumpPath()
{
    wchar_t exe[MAX_PATH];
    GetModuleFileNameW(nullptr, exe, MAX_PATH);
    std::wstring path(exe);
    auto pos = path.rfind(L'\\');
    if (pos != std::wstring::npos) path = path.substr(0, pos + 1);
    return path;
}

// ── dump thread ───────────────────────────────────────────────────────────────
// Runs on a fresh thread with a clean activation-context stack, so
// MiniDumpWriteDump (which calls into dbgcore.dll) is safe here.

static DWORD WINAPI dumpThreadProc(LPVOID) noexcept
{
    auto base = getDumpPath();

    // ── Minidump ──────────────────────────────────────────────────────────────
    auto dmpPath = base + L"OpenMTR_crash.dmp";
    HANDLE f = CreateFileW(dmpPath.c_str(), GENERIC_WRITE, 0, nullptr,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f != INVALID_HANDLE_VALUE) {
        // Re-package the saved exception info so MiniDumpWriteDump can use it.
        EXCEPTION_POINTERS ep;
        ep.ExceptionRecord = &g_dumpRequest.ExceptionRecord;
        ep.ContextRecord   = &g_dumpRequest.Context;

        MINIDUMP_EXCEPTION_INFORMATION mei{};
        mei.ThreadId          = g_dumpRequest.ThreadId;
        mei.ExceptionPointers = &ep;
        mei.ClientPointers    = FALSE;

        MiniDumpWriteDump(
            GetCurrentProcess(), GetCurrentProcessId(), f,
            (MINIDUMP_TYPE)(MiniDumpWithDataSegs | MiniDumpWithThreadInfo |
                            MiniDumpWithProcessThreadData | MiniDumpWithFullMemoryInfo),
            &mei, nullptr, nullptr);
        CloseHandle(f);
    }

    // ── Text log ──────────────────────────────────────────────────────────────
    auto txtPath = base + L"OpenMTR_crash.txt";
    std::wofstream out(txtPath, std::ios::app);
    if (!out) return 0;

    time_t t = time(nullptr);
    wchar_t timebuf[64];
    struct tm tm_info;
    localtime_s(&tm_info, &t);
    wcsftime(timebuf, 64, L"%Y-%m-%d %H:%M:%S", &tm_info);

    out << L"\n=== CRASH " << timebuf << L" ===\n";
    out << L"Exception: 0x" << std::hex << g_dumpRequest.ExceptionRecord.ExceptionCode
        << std::dec << L"\n";
    out << L"Address:   0x" << std::hex
        << reinterpret_cast<DWORD64>(g_dumpRequest.ExceptionRecord.ExceptionAddress)
        << std::dec << L"\n";
    out << L"ThreadId:  " << g_dumpRequest.ThreadId << L"\n";
    out << L"Dump:      " << dmpPath << L"\n";
    out << L"(Open the .dmp in WinDbg or Visual Studio for the full symbolicated stack)\n";
    out.flush();

    return 0;
}

// ── VEH handler ───────────────────────────────────────────────────────────────

static LONG WINAPI vehHandler(EXCEPTION_POINTERS* ep)
{
    // Only intercept fatal hardware exceptions.
    // Skip C++ EH (0xE06D7363), single-step, and breakpoints.
    DWORD code = ep->ExceptionRecord->ExceptionCode;
    if (code == 0xE06D7363 ||
        code == EXCEPTION_SINGLE_STEP ||
        code == EXCEPTION_BREAKPOINT)
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    // Write dump exactly once even if multiple threads fault simultaneously.
    static LONG written = 0;
    if (InterlockedCompareExchange(&written, 1, 0) != 0)
        return EXCEPTION_CONTINUE_SEARCH;

    // Copy exception data into the global — plain POD copy, no heap allocation,
    // no C++ objects, safe from any thread context.
    g_dumpRequest.ExceptionRecord = *ep->ExceptionRecord;
    g_dumpRequest.Context         = *ep->ContextRecord;
    g_dumpRequest.ThreadId        = GetCurrentThreadId();

    // Spawn a fresh plain thread (not a pool thread) so MiniDumpWriteDump runs
    // with a clean activation-context stack.  Wait for it to finish before
    // returning so the dump is complete before the process exits.
    HANDLE hThread = CreateThread(nullptr, 0, dumpThreadProc, nullptr, 0, nullptr);
    if (hThread) {
        WaitForSingleObject(hThread, 30'000);   // 30 s timeout — should never need it
        CloseHandle(hThread);
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

// ── install ───────────────────────────────────────────────────────────────────

static void install()
{
    AddVectoredExceptionHandler(1, vehHandler);
}

} // namespace CrashHandler
