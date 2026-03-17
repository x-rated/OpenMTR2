# engine/winmtr-redux — WinMTR Redux source

This folder contains the source files from **White-Tiger/WinMTR** (WinMTR Redux), copied here for reference.

These files are **not compiled** as part of OpenMTR2. They exist to:
- Preserve the history and credits of the upstream work
- Serve as a reference when porting logic or bug fixes into the C++20 engine layer above
- Make it easy to diff upstream changes in the future

## Origin

- Repository: https://github.com/White-Tiger/WinMTR
- Author: White-Tiger
- License: GPL-2.0 (same as this project)
- Last synced from: master branch

## Original WinMTR

- Original author: Vasile Laurentiu Stanimir / Appnor MSP (2000)
- Source: http://winmtr.net / https://sourceforge.net/projects/winmtr/

## Files

These are the original MFC-based C++ source files for the classic WinMTR Redux UI and network engine:

- `WinMTR.cpp` / `WinMTR.h` — MFC application entry point
- `WinMTRNet.cpp` / `WinMTRNet.h` — Network engine (ICMP ping + trace)
- `WinMTRDlg.cpp` / `WinMTRDlg.h` — Main dialog (MFC UI)
- `WinMTRProperties.cpp` / `WinMTRProperties.h` — Options/properties dialog
- `stdafx.h` / `stdafx.cpp` — Precompiled headers

The **active engine** used by OpenMTR2 is the C++20 module rewrite in `engine/` (WinMTR-refresh by leeter), which builds on the same algorithms as these files.
