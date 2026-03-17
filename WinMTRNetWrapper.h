#pragma once
// Bridge header — proper Windows/winsock includes then engine module imports

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2ipdef.h>
#include <windns.h>
#include <string>

import WinMTR.Net;
import WinMTRSNetHost;
import WinMTRIPUtils;

// Helper: SOCKADDR_INET -> wstring IP string
inline std::wstring addr_to_wstring(const SOCKADDR_INET& addr)
{
    wchar_t buf[64] = {};
    if (addr.si_family == AF_INET) {
        InetNtopW(AF_INET,  &addr.Ipv4.sin_addr,  buf, 64);
    } else if (addr.si_family == AF_INET6) {
        InetNtopW(AF_INET6, &addr.Ipv6.sin6_addr, buf, 64);
    }
    return buf;
}
