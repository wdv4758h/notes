:title: Linux Video Hardware Acceleration
:slug: linux-video-acceleration
:date: 2015-03-22 12:28
:modified: 2015-03-22 12:28
:category: Linux
:tags: VDPAU, VAAPI
:author: wdv4758h
:summary:

tl;dr; VDPAU 和 VA-API 是 Unix-like 上 Video Decode 的硬體加速 API

VA-API (Video Acceleration API) 是 Intel 在 2007 年提出的一套 royalty-free API，
實作在 ``libVA`` 以 MIT license 釋出。
目的是讓其他程式可以使用 Video 硬體加速。

VDPAU (Video Decode and Presentation API for Unix) 是 NVIDIA 在 2009 年提出的另一套 royalty-free API，
實作放在 ``libvdpau`` 以 MIT license 釋出 (一開始是做給 NVIDIA 自己的 GPU 用的)。

mesa 在 0.8 版加入了 VDPAU 的支援，以後只要是利用 Gallium3D 的顯卡驅動就可以獲得 VDPAU 的支援。

XvBA (X-Video Bitstream Acceleration) 則是 AMD 後來提的令一套 API ...

VDPAU 也可以當作 VA-API 的 backend (libva-vdpau-driver)，
VA-API 也可以當作 VDPAU 的 backend (libvdpau-va-gl)，
他們有一部份是重疊的。

.. table::
    :class: table table-bordered

    +---------+--------+--------------------+---------+
    | Company | Name   | First Release Year | License |
    +=========+========+====================+=========+
    | Intel   | VA-API | 2007               | MIT     |
    +---------+--------+--------------------+---------+
    | NVIDIA  | VDPAU  | 2009               | MIT     |
    +---------+--------+--------------------+---------+
    | AMD     | XvBA   |                    |         |
    +---------+--------+--------------------+---------+

vdpau
========================================

* Intel : libvdpau-va-gl
* AMD : mesa-vdpau
* NVIDIA : mesa-vdpau

.. code-block:: sh

    # Intel
    $ sudo pacman -S libvdpau-va-gl

可以裝 ``vdpauinfo`` 這個 package 來知道目前這台機器上的 GPU 支援的 features

.. code-block:: sh

    # 裝 vdpauinfo 來看相關資訊
    $ sudo pacman -S vdpauinfo

    # 跑 vdpauinfo 來取得訊息
    # 但是在我筆電上 (Intel i5-3210M, HD Graphics 4000) 會出現找不到 shared object 的錯誤
    # 感覺算是 bug
    $ vdpauinfo
    display: :0   screen: 0
    Failed to open VDPAU backend libvdpau_i965.so: cannot open shared object file: No such file or directory
    Error creating VDPAU device: 1

    # 用 VDPAU_DRIVER 這個環境變數來指定 driver 後就正常了
    $ env VDPAU_DRIVER=va_gl vdpauinfo
    display: :0   screen: 0
    [VS] Software VDPAU backend library initialized
    libva info: VA-API version 0.37.0
    libva info: va_getDriverName() returns 0
    libva info: Trying to open /usr/lib/dri/i965_drv_video.so
    libva info: Found init function __vaDriverInit_0_37
    libva info: va_openDriver() returns 0
    API version: 1
    Information string: OpenGL/VAAPI/libswscale backend for VDPAU

    Video surface:

    name   width height types
    -------------------------------------------
    420     1920  1080  NV12 YV12 UYVY YUYV Y8U8V8A8 V8U8Y8A8
    422     1920  1080  NV12 YV12 UYVY YUYV Y8U8V8A8 V8U8Y8A8
    444     1920  1080  NV12 YV12 UYVY YUYV Y8U8V8A8 V8U8Y8A8

    Decoder capabilities:

    name                        level macbs width height
    ----------------------------------------------------
    MPEG1                          --- not supported ---
    MPEG2_SIMPLE                   --- not supported ---
    MPEG2_MAIN                     --- not supported ---
    H264_BASELINE                  51 16384  2048  2048
    H264_MAIN                      51 16384  2048  2048
    H264_HIGH                      51 16384  2048  2048
    VC1_SIMPLE                     --- not supported ---
    VC1_MAIN                       --- not supported ---
    VC1_ADVANCED                   --- not supported ---
    MPEG4_PART2_SP                 --- not supported ---
    MPEG4_PART2_ASP                --- not supported ---
    DIVX4_QMOBILE                  --- not supported ---
    DIVX4_MOBILE                   --- not supported ---
    DIVX4_HOME_THEATER             --- not supported ---
    DIVX4_HD_1080P                 --- not supported ---
    DIVX5_QMOBILE                  --- not supported ---
    DIVX5_MOBILE                   --- not supported ---
    DIVX5_HOME_THEATER             --- not supported ---
    DIVX5_HD_1080P                 --- not supported ---
    H264_CONSTRAINED_BASELINE      --- not supported ---
    H264_EXTENDED                  --- not supported ---
    H264_PROGRESSIVE_HIGH          --- not supported ---
    H264_CONSTRAINED_HIGH          --- not supported ---
    H264_HIGH_444_PREDICTIVE       --- not supported ---

    Output surface:

    name              width height nat types
    ----------------------------------------------------
    B8G8R8A8            53    53    y
    R8G8B8A8             0     0    y
    R10G10B10A2          0     0    y
    B10G10R10A2          0     0    y
    A8                   0     0    y

    Bitmap surface:

    name              width height
    ------------------------------
    B8G8R8A8          8192  8192
    R8G8B8A8          8192  8192
    R10G10B10A2       8192  8192
    B10G10R10A2       8192  8192
    A8                8192  8192

    Video mixer:

    feature name                    sup
    ------------------------------------
    DEINTERLACE_TEMPORAL             -
    DEINTERLACE_TEMPORAL_SPATIAL     -
    INVERSE_TELECINE                 -
    NOISE_REDUCTION                  -
    SHARPNESS                        -
    LUMA_KEY                         -
    HIGH QUALITY SCALING - L1        -
    HIGH QUALITY SCALING - L2        -
    HIGH QUALITY SCALING - L3        -
    HIGH QUALITY SCALING - L4        -
    HIGH QUALITY SCALING - L5        -
    HIGH QUALITY SCALING - L6        -
    HIGH QUALITY SCALING - L7        -
    HIGH QUALITY SCALING - L8        -
    HIGH QUALITY SCALING - L9        -

    parameter name                  sup      min      max
    -----------------------------------------------------
    VIDEO_SURFACE_WIDTH              -
    VIDEO_SURFACE_HEIGHT             -
    CHROMA_TYPE                      -
    LAYERS                           -

    attribute name                  sup      min      max
    -----------------------------------------------------
    BACKGROUND_COLOR                 -
    CSC_MATRIX                       -
    NOISE_REDUCTION_LEVEL            -
    SHARPNESS_LEVEL                  -
    LUMA_KEY_MIN_LUMA                -
    LUMA_KEY_MAX_LUMA                -

libva
========================================

.. code-block:: sh

    $ sudo pacman -S libva
    $ vainfo    # 看硬體解碼支援哪些格式
    libva info: VA-API version 0.37.0
    libva info: va_getDriverName() returns 0
    libva info: Trying to open /usr/lib/dri/i965_drv_video.so
    libva info: Found init function __vaDriverInit_0_37
    libva info: va_openDriver() returns 0
    vainfo: VA-API version: 0.37 (libva 1.5.0)
    vainfo: Driver version: Intel i965 driver for Intel(R) Ivybridge Mobile - 1.5.0
    vainfo: Supported profile and entrypoints
          VAProfileMPEG2Simple            :	VAEntrypointVLD
          VAProfileMPEG2Simple            :	VAEntrypointEncSlice
          VAProfileMPEG2Main              :	VAEntrypointVLD
          VAProfileMPEG2Main              :	VAEntrypointEncSlice
          VAProfileH264ConstrainedBaseline:	VAEntrypointVLD
          VAProfileH264ConstrainedBaseline:	VAEntrypointEncSlice
          VAProfileH264Main               :	VAEntrypointVLD
          VAProfileH264Main               :	VAEntrypointEncSlice
          VAProfileH264High               :	VAEntrypointVLD
          VAProfileH264High               :	VAEntrypointEncSlice
          VAProfileH264StereoHigh         :	VAEntrypointVLD
          VAProfileVC1Simple              :	VAEntrypointVLD
          VAProfileVC1Main                :	VAEntrypointVLD
          VAProfileVC1Advanced            :	VAEntrypointVLD
          VAProfileNone                   :	VAEntrypointVideoProc
          VAProfileJPEGBaseline           :	VAEntrypointVLD

Chromium
========================================

原來現在從 package 裡裝到的 chromium 都是沒有開 VAAPI 支援的，
目前好像只有 `在 ChromeOS 上會開啟 <https://code.google.com/p/chromium/codesearch#chromium/src/content/common/gpu/media/gpu_video_decode_accelerator.cc&sq=package:chromium&type=cs&l=343&rcl=1426535742>`_

.. image:: /images/vdpau/chromium-vaapi.png
    :alt: Chromium

如果在 chromium 裡面開影片的話會看到 console 上有段資訊 (寫著 "**HW video decode acceleration not available.**") :

::

    [5100:5100:0322/052925:ERROR:gpu_video_decode_accelerator.cc(272)] Not implemented reached in void content::GpuVideoDecodeAccelerator::Initialize(media::VideoCodecProfile, IPC::Message*)HW video decode acceleration not available.

官方也寫了 `unsupport <https://code.google.com/p/chromium/wiki/LinuxHWVideoDecode>`_ ...

.. image:: /images/vdpau/chromium-vaapi-linux.png
    :alt: Chromium VAAPI on Linux

另外可以在 chromium 裡的 ``chrome://gpu`` 看到一些 features 的支援狀況 (但是 video 的 hardware decode acceleration 實際上還是沒開啟 ...)

.. image:: /images/vdpau/chromium-gpu.png
    :alt: Chromium GPU

Reference
========================================

* `Arch Wiki - VDPAU <https://wiki.archlinux.org/index.php/VDPAU>`_
* `Arch Wiki - VA-API <https://wiki.archlinux.org/index.php/VA-API>`_
* `Wikipedia - VDPAU <https://en.wikipedia.org/wiki/VDPAU>`_
* `Wikipedia - Video Acceleration API <https://en.wikipedia.org/wiki/Video_Acceleration_API>`_
* `Wikipedia - X-Video Bitstream Acceleration <http://en.wikipedia.org/wiki/X-Video_Bitstream_Acceleration>`_
* `freedesktop.org - vaapi <http://www.freedesktop.org/wiki/Software/vaapi/>`_
* `freedesktop.org - VDPAU <http://www.freedesktop.org/wiki/Software/VDPAU/>`_
* `Linux Graphics - VAAPI <https://01.org/linuxgraphics/community/vaapi>`_
