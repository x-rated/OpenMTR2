#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "CrashHandler.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
    CrashHandler::install();

    // Initialise Winsock once for the lifetime of the process.
    // This must happen before any getaddrinfo / DNS calls, including
    // the ones in MainWindow::onStartStop before WinMTRNet is created.
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // DPI awareness is declared in app.manifest (PerMonitorV2).
    QApplication app(argc, argv);
    app.setApplicationName("OpenMTR");
    app.setApplicationVersion("1.0.0");
    app.setStyle("Fusion");

    MainWindow w;
    w.show();
    int ret = app.exec();

    WSACleanup();
    return ret;
}
