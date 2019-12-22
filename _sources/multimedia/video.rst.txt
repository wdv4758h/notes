========================================
Video
========================================


.. contents:: 目錄


簡表
========================================

* Audio
    - Lossy Compression
        + MP3
        + WMA
        + Vorbis
        + Opus
        + AAC
        + AC-3
        + DTS
    - No Compression
        + PCM
        + LPCM
    - Lossless Compression
        + FLAC
        + ALAC
        + MLP/Dolby TrueHD
        + DTS-HD

* Video
    - MPEG-1
    - MPEG-2
    - MPEG-4 (A)SP
    - H.264/MPEG-4 AVC
    - H.265/HEVC
    - VC-1/WMV
    - Real Video
    - Theora
    - Microsoft MPEG4 V2
    - VP8
    - VP9
    - MVC
    - AV1

* Subtitle
    - MicroDVD
    - MPEG-4 Timed Text
    - MPSub
    - SAMI
    - SubRip
    - SSA (SubStation Alpha)
    - SubViewer
    - Universal Subtitle Format
    - VobSub
    - XSUB



MJPEG (Motion JPEG)
========================================



VP8
========================================


Encoder 實做：

* `libvpx <https://github.com/webmproject/libvpx/>`_


Decoder 實做：

* `libvpx <https://github.com/webmproject/libvpx/>`_



VP9
========================================

Encoder 實做：

* `libvpx <https://github.com/webmproject/libvpx/>`_
* `SVT-VP9 Encoder (Scalable Video Technology for VP9 Encoder) <https://github.com/OpenVisualCloud/SVT-VP9>`_
    - by Intel


Decoder 實做：

* `libvpx <https://github.com/webmproject/libvpx/>`_


文章：

* `The world’s fastest VP9 decoder: ffvp9 <https://blogs.gnome.org/rbultje/2014/02/22/the-worlds-fastest-vp9-decoder-ffvp9/>`_
* `The world’s best VP9 encoder: Eve <https://blogs.gnome.org/rbultje/2016/05/02/the-worlds-best-vp9-encoder-eve-2/>`_
* `EVE for VP9 -  Maximize the Capabilities of VP9 for Your Video Streaming <https://www.twoorioles.com/eve-for-vp9/>`_



H264 (AVC)
========================================

Encoder 實做：

* `OpenH264 <https://github.com/cisco/openh264>`_
    - by Cisco
* `x264 <https://code.videolan.org/videolan/x264>`_
    - by VLC


Decoder 實做：

* `OpenH264 <https://github.com/cisco/openh264>`_
    - by Cisco



H265 (HEVC)
========================================

Encoder 實做：

* `SVT-HEVC Encoder (Scalable Video Technology for HEVC Encoder) <https://github.com/OpenVisualCloud/SVT-HEVC>`_
    - by Intel
* `x265 <http://x265.org/>`_
* `libde265 <https://www.libde265.org/>`_


Decoder 實做：

* `libde265 <https://www.libde265.org/>`_
* `openHEVC <https://github.com/OpenHEVC/openHEVC>`_
    - decoder extracted from FFmpeg



Thor
========================================



Theora
========================================



Daala
========================================



AV1
========================================

由 AOMedia （Alliance for Open Media）開發的開放影像編碼格式，
AOMedia 的成員包含
Amazon、AMD、ARM、Cisco、Google、Intel、IBM、Microsoft、Mozilla、Netflix、NVIDIA 等等。


Encoder 實做：

* `AOM (Alliance for Open Media) <https://aomedia.googlesource.com/aom>`_
* `SVT-AV1 Encoder (Scalable Video Technology for AV1 Encoder) <https://github.com/OpenVisualCloud/SVT-AV1>`_
    - by Intel
* `rav1e - the fastest and safest AV1 encoder <https://github.com/xiph/rav1e>`_
    - 基本上是由 Mozilla 的人在開發
    - 用 Rust 撰寫，並且專注於提供比 libaom 更好的效能


Decoder 實做：

* `AOM (Alliance for Open Media) <https://aomedia.googlesource.com/aom>`_
* `dav1d - new AV1 cross-platform Decoder <https://code.videolan.org/videolan/dav1d>`_
    - by VLC


硬體支援：

* `Allegro - AL-E210, Encoder, 4K 30fps <http://www.allegrodvt.com/products/silicon-ips/al-e210/>`_
* Amphion - CS8142, Decoder, 4k 60fps
* Dwango, Encoder, 720p 30fps


文章；

* `Wkipiedia - AV1 <https://en.wikipedia.org/wiki/AV1>`_
* `next generation video: Introducing AV1 <https://people.xiph.org/~xiphmont/demo/av1/demo1.shtml>`_
* (2018/01/30) `AV1 Beats VP9 and HEVC on Quality, if You've Got Time, says Moscow State - Streaming Media Magazine <http://www.streamingmedia.com/Articles/News/Online-Video-News/AV1-Beats-VP9-and-HEVC-on-Quality-if-Youve-Got-Time-says-Moscow-State-122945.aspx>`_
    - AV1 目前的壓縮品質比 VP9 和 HEVC 還好，但是執行速度還有待提升
* (2018/04/10) `AV1 beats x264 and libvpx-vp9 in practical use case <https://code.fb.com/video-engineering/av1-beats-x264-and-libvpx-vp9-in-practical-use-case/>`_
* `AV1 Ecosystem Update: May 2019 <https://www.singhkays.com/blog/av1-ecosystem-update-may-2019/>`_




參考
========================================

* `Wikipedia - Alliance for Open Media <https://en.wikipedia.org/wiki/Alliance_for_Open_Media>`_
* `Wikipedia - AOMedia Video 1 <https://en.wikipedia.org/wiki/AOMedia_Video_1>`_
* [GitHub] `Digital Video Introduction <https://github.com/leandromoreira/digital_video_introduction>`_
* [GitHub] `Learn FFmpeg libav the Hard Way <https://github.com/leandromoreira/ffmpeg-libav-tutorial>`_
