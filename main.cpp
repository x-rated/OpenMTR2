#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "CrashHandler.h"

// Do NOT call RoInitialize/CoInitialize here.
//
// Qt6 on Windows manages COM apartments internally across its threads
// (UI thread, render thread, etc.).  Calling RoInitialize(STA) on the
// main thread before QApplication is constructed puts the UI thread into
// an STA apartment that conflicts with Qt's own COM initialisation for
// Direct2D / DirectWrite rendering, causing a null COM interface pointer
// dereference inside Qt6Widgets -> crash.
//
// The WinMTR-refresh engine's WinRT context issue (get_current_winrt_context
// capturing an invalid apartment) is addressed by constructing WinMTRNet
// lazily — inside MainWindow — only after the Qt event loop has started and
// Qt has fully initialised its own COM/WinRT state.  WinMTRNet is already
// constructed in MainWindow's constructor (not in main), so this is already
// the case.  No extra RoInitialize call is needed or safe here.

int main(int argc, char* argv[])
{
    CrashHandler::install();

    // DPI awareness is declared in app.manifest (PerMonitorV2).
    QApplication app(argc, argv);
    app.setApplicationName("OpenMTR");
    app.setApplicationVersion("1.0.0");
    app.setStyle("Fusion");

    MainWindow w;
    w.show();

    return app.exec();
}
