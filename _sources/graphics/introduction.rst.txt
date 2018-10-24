========================================
Linux Graphics
========================================


.. contents:: 目錄



歷史發展
========================================

Console and Frame Buffer
------------------------------

當出 Linux 被寫出來的時候，
其 console 是直接使用 VGA 硬體的（text mode）。
剛開始時，
第一批有繪圖的應用程式都會自帶驅動程式，
後來第一批繪圖 Library 出現（例如 SVGALib）。
當時的應用程式必須維持繪圖硬體的狀態，
開始執行時儲存狀態，
結束執行後還原狀態，
而這樣的模式仍適用於現在的 X Server。

接著第一個 Kernel 內的繪圖 framework 『Framebuffer Devices』 出現了，
通常會被簡稱為『fbdev』，

::

    　+---------------------+
      | Console Application |
      +---------------------+
                |
                v
           +-----------+
    +------| /dev/tty1 |------+
    |      +-----------+      |
    | Linux Console Subsystem |
    +-------------------------+
                |
                v
        +---------------+   +-----------------------+
        | fbcon         |   | Graphical Application |
        +---------------+   +-----------------------+
                  |             |
                  v             v
                +-----------------+
              +-| /dev/fb0        |-+
              | +-----------------+ |
              | Framebuffer Driver  |
              +---------------------+
                         |
                         v
              +---------------------+
              | Hardware            |
              +---------------------+


* 移植需求：很多平台不支援 text mode
* 針對不同硬體而做的驅動程式，卻有通用的 API
    - z.B. intelfb, atifb
    - vesafb：不依賴特定硬體，使用繪圖卡的 VESA BIOS
    - efifb：類似 vesafb，但適用於 UEFI
* userspace 存取： /dev/fbX
* 簡單的 API
* fbcon：text console 模擬，有 bitmapped fonts 和企鵝，在 kernel 內完成，而非 userspace


X Window System
------------------------------

X Window System
++++++++++++++++++++

X Window System 是 Linux 上最通用的繪圖架構，
也在所有 Unix-like 的平台上流行，
常被簡稱為『X11』、『X』。
其為 client/server 架構，
client 是應用程式，
server 則負責輸入輸出。
這個 client/server 架構具有 Network Transparent 的特性，
不限定兩邊要跑在同一臺機器上，
中間可以利用 TCP/IP 傳輸，
或者在本地端使用 Unix Domain Sockets 溝通。

X11 是它的 protocol 名稱。

X Server 會管理整個視窗層級

* root window：桌面背景
* top-level window：應用程式的視窗
* subwindows：控制（例如按鈕之類的）

::

    +-------------+     +-------------+
    | Application |     | Application |
    | (X Client)  |     | (X Client)  |
    +-------------+     +-------------+
         ^  |                 ^  |
         |  | X11 protocol    |  | X11 protocol
         |  v                 |  v
    +---------------------------------+
    | X Server                        |
    |                                 |
    |  +--------+       +--------+    |
    +--| Driver |-------| Driver |----+
       +--------+       +--------+
           ^                |
           |                v
    +---------------+  +-----------------+
    | Input Devices |  | Display Devices |
    +---------------+  +-----------------+


X Clients and Servers
+++++++++++++++++++++

X Client 不直接實做 X11 protocol，
它們會使用 Libraries：

* 傳統的 Xlib
* 較新、較輕量的 XCB （X11 C Bindings）
* 其他工具包內部也是使用 Xlib 或 XCB，例如 Motif、GTK、Qt 。

::

    +------+ +----+ +------+ +--------+ +-------+ +-----------+
    |      | |    | |      | | Athena | | Motif | | Open Look |
    |      | |    | |      | | (Xaw)  | | (Xm)  | | (Xview)   |
    |      | |    | |      | +--------+ +-------+ +-----------+
    |      | |    | |      |     |          |          |
    |      | |    | |      |     v          v          v
    | GTK+ | | Qt | | FLTK | +----------------------------+
    |      | |    | |      | | X-Toolkit (Xt)             |
    +------+ +----+ +------+ +----------------------------+
       |       |        |                |
       v       v        v                v
    +-----------------------------------------------------+
    | Client Libraries                                    |
    | (Xlib, XCB)                                         |
    +-----------------------------------------------------+


      Display Server            Window Manager


Window Manager 是特別的 X Client，
負責管理 top-level 視窗和畫出視窗的外框（frames）（decorations）。

X Server 要負責管理輸入（鍵盤、滑鼠等）和輸出（只有圖像）：

* 通用的部份：DIX （Device Independent X）
* 針對特殊硬體的部份：DDX （Device Dependent X）
    - 包含輸入、輸出裝置的驅動程式


大多數流行的 X Server 實做（XFree86 和現今的 X.Org）：

* DDX 部份是模組化的，驅動程式為獨立的模組
* DDX 的界面會隨著 Server 版本更動


X Extensions
++++++++++++++++++++

X protocol 可以利用 Extensions 擴充能力，
例如：

* XSHM （X Shared Memory）：針對 bitmap 的更快速本地端顯示
* Xv （X Video）：硬體加速的影像顯示
* GLX：X 上的 OpenGL
* Xinerama：多螢幕支援
* XRandR （Resize and Rotate）：不用重開 X Server 的繪圖模式設定
* XRendr：現代化的反鋸齒（平滑化）、透明度混合（alpha-blended）的 2D 圖像
    - 現今用於幾乎每個 2D 的圖像程式


2D Acceleration in X
++++++++++++++++++++

在 XFree86 或 X.Org 中，
要使用硬體加速的 2D 繪圖有好幾種方式：

* XAA （XFree86 Acceleration Architecture，1996）：簡單地加速線段繪製和填滿操作
* EXA （2005）：從 KAA （Kdrive Acceleration Architecture，2004）衍生而來，專門針對 XRendr 的加速
* UXA （Unified Memory Acceleration Acceleration，2008）：由 Intel 開發，設計要來取代 EXA，不被非 Intel 的驅動程式採用
* SNA （Sandy Bridge New Acceleration，2011）：完全針對 Intel 需求特製的，但也因此非常快
* Glamor （2011）：用 OpenGL 實做所有的 2D 加速功能，因此不依賴特定廠商的硬體


OpenGL
------------------------------

OpenGL
++++++++++++++++++++

OpenGL （Open Graphics Language）是針對 3D 繪圖的工業標準，
由 Khronos Group 管理，
功能為硬體加速地繪製三角形結構。

OpenGL ES （OpenGL for Embedded Systems）大致上是 OpenGL 的子集合，
有大約 90% 的相容度。

OpenGL 2.0 後加入了可程式化的 Shader，
為一個 C-like 的語言稱為 GLSL （OpenGL Shading Language）。

OpenGL 具有擴充的機制，
類似 X11。

OpenGL 需要額外的一些 API 作為和視窗系統間的膠水：

* GLX：針對 X 視窗系統
* WGL：針對 Windows
* AGL：針對 Mac OS X
* EGL：使用 OpenGL ES 的版本（Embedded Linux、Android、iOS 等）
    - 在各系統皆可取得，最後會取代 GLX


Indirect v.s. Direct Rendering
++++++++++++++++++++++++++++++

OpenGL 在 Linux 上的 X.Org 會以以下方式運作，

X.Org 會把 GLX 作為 X protocol 的一部分，

Indirect Rendering 的狀況會把 OpenGL 指令透過 GLX protocol 傳輸。
在早期的一段時間，這樣的作法不能使用到硬體加速。

::

    +-------------+
    | Application |
    +-------------+
          | X11 + GLX
          v
    +-------------+
    | X Server  +--------+
    +-----------| OpenGL |
                +--------+


Direct Rendering 只能用於本地端，
不能透過網路傳輸，
client 會連結到 libGL.so 並直接使用。
libGL.so 會包含 OpenGL 實做（可能是針對某個硬體的）。

::

    +-------------+ direct function calls
    | Application |-----------------------+
    +-------------+                       |
           | X11 + GLX                    |
           v                              v
    +-------------+                   +--------+
    | X Server    |<~~~~~~~~~~~~~~~~~>| OpenGL |
    +-------------+      GLX          +--------+



Mesa
++++++++++++++++++++

Linux 上的 OpenGL 實做有兩種，
一種是私有的驅動程式（例如 NVIDIA 和 AMD），
另一種是開源的 Mesa。
Mesa 的實做也包含 GLX、EGL、OpenGL ES，
起初只有軟體渲染的功能，
而現今為各開源 3D 驅動程式的基礎。


Gallium3D
++++++++++++++++++++

Gallium3D 是不依賴特定 OS 的 GPU 驅動程式 framework，
其中一部份依賴 Mesa，
包含的功能不只 3D 渲染，
還包括 GPU 運算、硬體影像解碼。

三個基本的部份：

* State Tracker ：client API 的實做
    - OpenGL （利用 Mesa）
    - OpenCL （計算用）
    - VDPAU （影像）
    - OpenMAX （影像）
* WinSys Driver ：實做 GLX 或 EGL
* Pipe Driver ：特定 GPU 的後端
    - llvmpipe ：較快地軟體渲染
    - NVIDIA GPU ： nv30, nv50, nvc0, nve0
    - AMD GPU ： radeonsi

Gallium3D 使用 TGSI （Tungsten Graphics Shader Infrastructure）作為 shader 的表示方式，
某些後端內部會使用 LLVM。


OpenGL Driver Stacks
++++++++++++++++++++

把不同實做搭配起來，
OpenGL 可能會有四種驅動程式運作的架構：

* 私有的驅動程式：取代 libGL.so
* 典型的 Mesa ：通用的 libGL.so，搭配 Mesa 內針對某些硬體的後端
* Mesa + Gallium3D ：使用 Mesa 作為 State Tracker，Gallium3D 作為後端（TGSI）
* Mesa + Gallium3D + LLVM ：使用 Mesa 作為 State Tracker，Gallium3D 作為後端（LLVM）


::

    +-------------+     +-------------+         +-------------+     +-------------+
    | Application |     | Application |         | Application |     | Application |
    +-------------+     +-------------+         +-------------+     +-------------+
          | OpenGL            | OpenGL                | OpenGL            | OpenGL
          v                   v                       v                   v
    +---------------+   +-------------------+   +---------------+   +---------------+
    | proprietary   |   | Mesa              |   | Mesa          |   | Mesa          |
    | OpenGL driver |   +-------------------+   +---------------+   +---------------+
    +---------------+   | hardware-specific |   | Gallium3D     |   | Gallium3D     |
          |             | driver backend    |   | State Tracker |   | State Tracker |
          |             +-------------------+   +---------------+   +---------------+
          |                   |                       | Gallium3D         | Gallium3D
          |                   |                       | (TGSI)            | (TGSI)
          |                   |                       v                   |
          |                   |                 +-------------+     +-----|---------------+
          |                   |                 | Gallium3D   |     |     v   Pipe Driver |
          |                   |                 | Pipe Driver |     | +---------+         |
          |                   |                 +-------------+     | | gallivm |         |
          |                   |                       |             | +---------+         |
          |                   |                       |             |     | LLVM IR       |
          |                   |                       |             |     v               |
          |                   |                       |             | +---------+         |
          |                   |                       |             | | LLVM    |         |
          |                   |                       |             | +---------+         |
          |                   |                       |             | | Backend |         |
          |                   |                       |             | +---------+         |
          |                   |                       |             +---------------------+
          |                   |                       |                   |
          v                   v                       v                   v
    +-------------+     +-------------+         +-------------+     +-------------+
    | GPU         |     | GPU         |         | GPU         |     | GPU         |
    +-------------+     +-------------+         +-------------+     +-------------+


OpenCL
++++++++++++++++++++

現今的 GPU 因為有著快速的浮點數運算能力，
會被拿來用於非繪圖的運算，
被稱為 GPGPU （General Purpose GPU）。

GPGPU 的標準 API 為 OpenCL （Open Compute Language），
和 OpenGL 一樣由 Khronos Group 管理、制定。
Linux 上的支援方式類似 OpenGL，
私有的驅動程式自帶它們的實做，
Gallium3D 則是 **Clover** State Tracker，
Intel GPU 則有另外的專案叫 Beignet。

除了 OpenCL 之外，
另外還有流行的 NVIDIA API 叫 CUDA，
但是只能用於 NVIDIA 的顯示卡並且搭配私有的驅動程式。


Direct Rendering Infrastructure
-------------------------------

DRI & DRM
++++++++++++++++++++

OpenGL 的驅動程式會作為應用程式的一部分跑在 userspace，
對於顯示卡的存取由 kernel 內的驅動程式管理，
這管理包含多個程式同時存取。
私有的驅動程式會包含私有的 kernel 驅動程式 API，
開源的驅動程式則有通用的 framework 叫 DRI （Direct Rendering Infrastructure）。

多層架構：

* 不依賴特定硬體的 userspace library （libdrm.so）
* 依賴特定硬體和驅動程式的 userspace library （libdrm_intel.so）
* kernel 模組： DRM (Direct Rendering Manager）

DRM 會把裝置顯示到 ``/dev/dri/cardX``

libdrm_xxx.so 和 DRM 間的界面有一部份會依賴特定的驅動程式


DRI Versions
++++++++++++++++++++

* DRI 1，1998
    - 第一版，實做的能力有限，如果有多個應用程式想使用 3D 硬體的話效率不佳
* DRI 2，2007
    - 解決了大部份第一版碰到的問題，為目前最廣範使用的版本
* DRI 3，2013
    - 更多細部的改進

DRM Master and Render Node
++++++++++++++++++++++++++

DRM clients 並非都同等的，
其中會有 DRM Master，


Memory Management and Buffer Sharing
++++++++++++++++++++++++++++++++++++

Kernel Mode Setting
------------------------------



參考
========================================

* `Linux Graphics Demystified <http://keyj.emphy.de/files/linuxgraphics_en.pdf>`_
