# OpenMTR

**OpenMTR** is a modern, lightweight network diagnostic tool for Windows that combines traceroute and ping into a single real-time view. Built on the battle-tested [WinMTR-refresh](https://github.com/leeter/WinMTR-refresh) engine with a clean Qt6 interface designed to feel native on Windows 11.


![OpenMTR Screenshot](https://i.imgur.com/7ZBfHab.png)

```
OpenMTR Export
Target  : gov.bw
Date    : 2026-03-17 03:20:05

+-----+-------+-------------------------------------------------------------+-----------------+-------+------+------+------+------+------+------+
| Hop | ASN   | Hostname                                                    | IP              | Loss% | Sent | Recv | Best | Avrg | Wrst | Last |
+-----+-------+-------------------------------------------------------------+-----------------+-------+------+------+------+------+------+------+
| 1   | -     | RT-BE88U                                                    | 192.168.1.1     |     0 |   51 |   51 |    0 |    0 |    0 |    0 |
| 2   | -     | 10.26.202.187                                               | 10.26.202.187   |     0 |   51 |   51 |    1 |    1 |    2 |    2 |
| 3   | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 4   | 16019 | 217.77.171.153                                              | 217.77.171.153  |     0 |   51 |   51 |    3 |    3 |    4 |    3 |
| 5   | 16019 | 914.1-1-7.sitpe00.oskarmobil.cz                             | 217.77.160.49   |     8 |   39 |   36 |    3 |    3 |    4 |    3 |
| 6   | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 7   | -     | 20ge1-3.core1.prg1.he.net                                   | 91.210.16.201   |     0 |   51 |   51 |    4 |    5 |   17 |    5 |
| 8   | 6939  | 100ge0-65.core3.fra1.he.net                                 | 184.105.213.233 |    90 |   29 |    3 |    0 |   41 |   61 |   61 |
| 9   | 6939  | be47.core4.fra1.he.net                                      | 184.105.213.207 |     0 |   51 |   51 |   11 |   12 |   19 |   14 |
| 10  | 6939  | be1.core3.par2.he.net                                       | 72.52.92.157    |    12 |   35 |   31 |   42 |   44 |   46 |   44 |
| 11  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 12  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 13  | 6939  | port-channel6.core1.lis1.he.net                             | 184.104.193.150 |    20 |   26 |   21 |    0 |   43 |   45 |   43 |
| 14  | 6939  | west-indian-ocean-cable-company-ltd.e0-27.core2.lis1.he.net | 184.104.204.94  |     0 |   51 |   51 |   43 |   43 |   49 |   44 |
| 15  | 37662 | 154.66.247.98                                               | 154.66.247.98   |     0 |   51 |   51 |  170 |  171 |  186 |  171 |
| 16  | 37662 | 154.66.247.107                                              | 154.66.247.107  |     0 |   51 |   51 |  156 |  157 |  161 |  157 |
| 17  | 37662 | 154.66.247.67                                               | 154.66.247.67   |     0 |   51 |   51 |  172 |  173 |  187 |  187 |
| 18  | 37662 | 102.68.115.249                                              | 102.68.115.249  |     0 |   51 |   51 |  171 |  171 |  173 |  172 |
| 19  | 37678 | 129.205.206.150                                             | 129.205.206.150 |     0 |   51 |   51 |  176 |  176 |  177 |  177 |
| 20  | 37678 | 129.205.195.134                                             | 129.205.195.134 |     0 |   51 |   51 |  175 |  176 |  179 |  178 |
| 21  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 22  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 23  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 24  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 25  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 26  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 27  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 28  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 29  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
| 30  | -     |                                                             |                 |   100 |   34 |    0 |    0 |    0 |    0 |    0 |
+-----+-------+-------------------------------------------------------------+-----------------+-------+------+------+------+------+------+------+
```

## Features

**Real-time route tracing** — Continuously probes every hop between you and the target, updating statistics live as packets return. Combines the power of traceroute and ping in one view.

**Per-hop statistics** — Each hop shows ASN, hostname, IP address, packet loss %, sent/received counts, and best / average / worst / last latency in milliseconds.

**ASN lookup** — Autonomous System Numbers are resolved automatically for each hop via Team Cymru's DNS service, giving you instant context on which network owns each router.

**IPv4 & IPv6** — Full dual-stack support. Toggle IPv6 with a single checkbox before starting a trace. If the target can't be resolved with the selected protocol, the app automatically switches to the other one.

**Configurable ping size** — Adjust the ICMP payload from 64 to 8192 bytes to test path behaviour under different packet sizes.

**Route discovery overlay** — A "Discovering route..." screen hides the initial burst of setup packets so your statistics start clean, without false packet loss on the first few pings. Automatically dismisses when the route is fully mapped, with a smart timeout for destinations that don't respond to ICMP.

**Light & dark themes** — Switches instantly between light and dark mode. On Windows 11 the title bar follows your choice using the native Mica/DWM dark title bar API. The app also auto-detects your system theme on launch.

**Export & copy** — Save results as `.txt` or `.csv` with a timestamped filename, or copy the full report to clipboard in one click. Double-click any cell in the results table to copy its value individually.

**No admin rights required** — Runs as a standard user. No elevated privileges, no UAC prompts.

**HiDPI aware** — Declared Per-Monitor V2 DPI aware in the app manifest for crisp rendering on high-resolution and mixed-DPI multi-monitor setups.

---

## Requirements

- Windows 11 recommended (required for Mica title bar); Windows 10 22H2+ supported with reduced visual effects
- Qt 6.10+ with `msvc2022_64` kit
- Visual Studio 2022 with C++20 modules support

---

## Building

1. Install [Qt 6.10+](https://www.qt.io/download) with the `msvc2022_64` component
2. If not using the `QT_ROOT_DIR` environment variable, update `QtDir` in `OpenMTR.vcxproj` to match your Qt installation path
3. Open `OpenMTR.sln` in Visual Studio 2022
4. Build → **Release x64**

Releases are also built automatically via GitHub Actions on every push.

---

## Credits

- Network engine: [WinMTR-refresh](https://github.com/leeter/WinMTR-refresh) by Leetsoftwerx
- Original WinMTR by [Appnor MSP](http://www.appnor.com) (Vasile Laurentiu Stanimir, 2000)

---

## License

GPL v2 — see [LICENSE](LICENSE).
