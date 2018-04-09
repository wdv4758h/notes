========================================
GStreamer
========================================


.. contents:: 目錄


文件
========================================

* `PyGObject API Reference - Gst <https://lazka.github.io/pgi-docs/#Gst-1.0/>`_
* `GStreamer Core Reference Manual <https://gstreamer.freedesktop.org/data/doc/gstreamer/stable/gstreamer/html/>`_
* `Valadoc - Gst <https://valadoc.org/gstreamer-1.0/Gst.html>`_



Pipeline
========================================

基本介紹
------------------------------

基本流程：

::

    Source -> 中間處理 -> Sink


範例：

.. code-block:: sh

    # 以 local 的 sample.mp4 當作媒體來源
    # 把影像轉成 H264 並包在 RTP 封包裡面
    # 以 UDP 送出到指定的位置
    $ gst-launch-1.0 filesrc location=sample.mp4 ! qtdemux ! rtph264pay config-interval=1 ! udpsink host=127.0.0.1 port=5566


產生 Pipeline 流程圖
------------------------------

使用 ``GST_DEBUG_DUMP_DOT_DIR`` 來指定 DOT 描述語言的輸出資料夾。


.. code-block:: sh

    $ env GST_DEBUG_DUMP_DOT_DIR=/tmp/dot/ gst-launch-1.0 filesrc location=sample.mp4 ! qtdemux ! rtph264pay config-interval=1 ! udpsink host=127.0.0.1 port=5566


.. code-block:: sh

    $ sudo pacman -S xdot
    $ xdot /tmp/dot/0.00.00.023250085-gst-launch.PAUSED_PLAYING.dot


檢查目前系統的支援
------------------------------

.. code-block:: sh

    $ gst-inspect-1.0
    ...

    $ gst-inspect-1.0 x264
    Plugin Details:
      Name                     x264
      Description              libx264-based H264 plugins
      Filename                 /usr/lib/gstreamer-1.0/libgstx264.so
      Version                  1.12.1
      License                  GPL
      Source module            gst-plugins-ugly
      Source release date      2017-06-20
      Binary package           GStreamer Ugly Plugins (Arch Linux)
      Origin URL               http://www.archlinux.org/

      x264enc: x264enc

      1 features:
      +-- 1 elements


除錯
------------------------------

可以利用 ``GST_DEBUG`` 設定全域的資訊層級或是特定元件的資訊層級。

.. code-block:: sh

    $ env GST_DEBUG=4 gst-launch-1.0 filesrc location=sample.mp4 ! qtdemux ! rtph264pay config-interval=1 ! udpsink host=127.0.0.1 port=5566



Source
========================================

稍微列出一些常見的 Source：

* 第三方應用程式（用於利用 GStreamer 撰寫自己的程式）: appsrc
* RTSP: rtspsrc
* UDP: udpsrc


自己系統目前支援的 Source 的完整清單：

.. code-block:: sh

    $ gst-inspect-1.0 | rg src


Sink
========================================

稍微列出一些常見的 Source：

* 第三方應用程式（用於利用 GStreamer 撰寫自己的程式）: appsink
* 檔案: filesink
* UDP: udpsink


自己系統目前支援的 Sink 的完整清單：

.. code-block:: sh

    $ gst-inspect-1.0 | rg src



Binding
========================================

GObject Introspection
------------------------------

:Repo: https://github.com/GNOME/gobject-introspection


* GIR: XML 格式，用於 GObject Introspection，提供共同的結構來存取 API，這格式的設計適用於各種程式語言，利用 namespace 來區分 core、language、library 的功能
* Typelib: binary 格式的 GIR，設計原則是快、使用少量記憶體、足夠讓各個程式語言沒有原始碼的狀況下做出 binding
* 工具:
    - g-ir-scanner: 用於產生 GIR，可以爬 headers/GTK-Doc/libraries
    - g-ir-compiler: GIT 轉 Typelib
    - g-ir-generate: Typelib 轉 GIR
    - g-ir-annotation-tool: 從程式碼截出 annotation
    - g-ir-doc-tool: 從 GIR 產生 API 文件


Python
------------------------------

:Repo: https://github.com/GStreamer/gst-python

利用 `PyGObject <https://git.gnome.org/browse/pygobject/>`_ 做成的 binding，
涵蓋大部分 GStreamer 的功能。
`PyGObject 文件 <https://pygobject.readthedocs.io/en/latest/>`_ 。


安裝：

.. code-block:: sh

    # 系統安裝
    $ sudo pacman -S gst-python

    # 用 pip 安裝
    $ pip install "git+https://git.gnome.org/browse/pygobject@3.24.1"


使用：

.. code-block:: python

    import gi

    # 在 import Gst 之前要先指定版本限制。
    gi.require_version('Gst', '1.0')

    from gi.repository import Gst

    Gst.init(None)

    # 可以使用 GST_DEBUG 環境變數來開啟除錯訊息，
    # 或是使用下面兩行：
    # Gst.debug_set_active(True)
    # Gst.debug_set_default_threshold(5)


Rust
------------------------------

:Repo: https://github.com/sdroege/gstreamer-rs
:Docs: https://sdroege.github.io/rustdoc/gstreamer/gstreamer/


利用 `GIR <https://github.com/gtk-rs/gir/>`_ 從 GStreamer 專案
提供的 GObject-Introspection API metadata 來自動產生 binding，
已經涵蓋大部分 GStreamer 的功能。

`GTK 系列 Rust binding 網站 <http://gtk-rs.org/>`_ 。



核心元件
========================================

`core elements <https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gstreamer-plugins/html/gstreamer-plugins-plugin-coreelements.html>`_


Pipeline Branch - tee
------------------------------

`tee <https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gstreamer-plugins/html/gstreamer-plugins-tee.html>`_
會從原本的 Pipeline 切出 Branch，
範例：

.. code-block:: sh

    $ gst-launch-1.0 filesrc location=song.ogg ! decodebin ! \
        tee name=t ! queue ! audioconvert ! audioresample ! autoaudiosink \
                t. ! queue ! audioconvert ! goom ! videoconvert ! autovideosink


寫到指定的 File Descriptor - fdsink
-----------------------------------

.. code-block:: sh

    $ gst-launch-1.0 -q videotestsrc pattern=ball ! video/x-raw,height=320,width=240,framerate=30/1,format=RGB ! fdsink | ffplay -f rawvideo -pixel_format rgb24 -video_size 240x320 -i -


從指定的 File Descriptor 讀入 - fdsrc
-------------------------------------

.. code-block:: sh

    $ echo "Hello GStreamer" | gst-launch-1.0 -v fdsrc ! fakesink dump=true
    Setting pipeline to PAUSED ...
    Pipeline is PREROLLING ...
    Pipeline is PREROLLED ...
    Setting pipeline to PLAYING ...
    New clock: GstSystemClock
    00000000 (0x7f9fd8004890): 48 65 6c 6c 6f 20 47 53 74 72 65 61 6d 65 72 0a  Hello GStreamer.
    Got EOS from element "pipeline0".
    Execution ended after 0:00:00.000123950
    Setting pipeline to PAUSED ...
    Setting pipeline to READY ...
    Setting pipeline to NULL ...
    Freeing pipeline ...


input-selector
------------------------------


identity
------------------------------


funnel
------------------------------



其他元件
========================================

TCP
------------------------------

* tcpserversrc
* tcpserversink
* tcpclientsrc
* tcpclientsink



顯示 plugin 被放入 blacklist 的原因
========================================



Pipeline 除錯
========================================

* [GitHub] `gst-devtools <https://github.com/GStreamer/gst-devtools>`_
* `gst-validate <https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-validate/html/gst-validate.html>`_

.. code-block:: sh

    $ git clone https://github.com/GStreamer/gst-devtools
    $ cd gst-devtools
    $ meson . build
    $ cd build
    $ ninja

    $ validate/tools/gst-validate-1.0 playbin file:///path/to/a/video.mkv
    Starting pipeline
    Pipeline started
         issue : EOS events that are part of the same pipeline 'operation' should have the same seqnum
                 Detected on <matroskademux0:video_0>
                 Detected on <multiqueue0:sink_0>
                 Detected on <matroskademux0:audio_0>
                 Detected on <multiqueue0:sink_1>
                 Detected on <multiqueue0:src_1>
                 Detected on <ac3parse0:sink>
                 Detected on <ac3parse0:src>
                 Detected on <capsfilter2:sink>
                 Detected on <capsfilter2:src>
                 Detected on <a52dec0:sink>
                 Detected on <a52dec0:src>
                 Detected on <inputselector1:sink_0>
                 Detected on <inputselector1:src>
                 Detected on <audiotee:sink>
                 Detected on <audiotee:src_0>
                 Detected on <streamsynchronizer0:sink_1>
                 Detected on <multiqueue0:src_0>
                 Detected on <h264parse0:sink>
                 Detected on <h264parse0:src>
                 Detected on <capsfilter0:sink>
                 Detected on <capsfilter0:src>
                 Detected on <vaapidecode0:sink>
                 Detected on <vaapidecode0:src>
                 Detected on <vaapi-queue:sink>
                 Detected on <vaapi-queue:src>
                 Detected on <capsfilter1:sink>
                 Detected on <capsfilter1:src>
                 Detected on <vaapipostproc0:sink>
                 Detected on <vaapipostproc0:src>
                 Detected on <inputselector0:sink_0>
                 Detected on <inputselector0:src>
                 Detected on <streamsynchronizer0:sink_0>
                 Detected on <streamsynchronizer0:src_0>
                 Detected on <vdconv:sink>
                 Detected on <vdconv:src>
                 Detected on <deinterlace:sink>
                 Detected on <streamsynchronizer0:src_1>
                 Detected on <deinterlace:src>
                 Detected on <aqueue:sink>
                 Detected on <vqueue:sink>
                 Detected on <aqueue:src>
                 Detected on <conv:sink>
                 Detected on <conv:src>
                 Detected on <resample:sink>
                 Detected on <resample:src>
                 Detected on <pulsesink2:sink>
                 Detected on <vqueue:src>
                 Detected on <conv:sink>
                 Detected on <conv:src>
                 Detected on <scale:sink>
                 Detected on <scale:src>
                 Detected on <vaapisink0:sink>
                 Description : when events/messages are created from another event/message, they should have their seqnums set to the original event/message seqnum

       warning : received the same caps twice
                 Detected on <h264parse0:sink>
                 Detected on <ac3parse0:sink>
                 Detected on <a52dec0:sink>

    Issues found: 2

    =======> Test PASSED (Return value: 0)

    $ validate/tools/gst-validate-1.0 audiotestsrc ! input-selector ! capsfilter name=capsfilter caps=video/x-raw ! fakesink
    Starting pipeline
    Pipeline started
       warning : EOS received without segment event before
                 Detected on <audiotestsrc0:src>
                 Detected on <inputselector0:sink_0>
                 Detected on <inputselector0:src>
                 Detected on <capsfilter:sink>
                 Detected on <capsfilter:src>
                 Description : A segment event should always be sent before data flow EOS being some kind of data flow, there is no exception in that regard

      critical : a NOT NEGOTIATED message has been posted on the bus.
                 Detected on <pipeline0>
                 Details : Error message posted by: audiotestsrc0
                          Caps negotiation failed starting from pad 'capsfilter:sink' as the QUERY_CAPS returned EMPTY caps for the following possible reasons:
                             -> Downstream caps struct 0 name 'video/x-raw' differs from filter caps struct 0 name 'audio/x-raw'. The exact reason could not be determined but here is the gathered information:
                          - capsfilter:sink last query caps filter: audio/x-raw, format=(string){ S16LE, S16BE, U16LE, U16BE, S24_32LE, S24_32BE, U24_32LE, U24_32BE, S32LE, S32BE, U32LE, U32BE, S24LE, S24BE, U24LE, U24BE, S20LE, S20BE, U20LE, U20BE, S18LE, S18BE, U18LE, U18BE, F32LE, F32BE, F64LE, F64BE, S8, U8 }, layout=(string)interleaved, rate=(int)[ 1, 2147483647 ], channels=(int)[ 1, 2147483647 ]
                          - capsfilter:sink possible caps (as returned by a query on it without filter): video/x-raw

                 dotfile : no dotfile produced as GST_DEBUG_DUMP_DOT_DIR is not set.
                 backtrace :
                   gst_debug_get_stack_trace (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b56683c05)
                   gst_validate_report_new (/home/dv/zone/gst-devtools/build/validate/gst/validate/libgstvalidate-1.0.so.0.1202.0:0x7f3b56974df0)
                   gst_validate_report_valist (/home/dv/zone/gst-devtools/build/validate/gst/validate/libgstvalidate-1.0.so.0.1202.0:0x7f3b5696559d)
                   gst_validate_report (/home/dv/zone/gst-devtools/build/validate/gst/validate/libgstvalidate-1.0.so.0.1202.0:0x7f3b56965ab6)
                   _bus_handler (/home/dv/zone/gst-devtools/build/validate/gst/validate/libgstvalidate-1.0.so.0.1202.0:0x7f3b56969021)
                   ffi_call_unix64 (/usr/lib/libffi.so.6.0.4:0x7f3b543711c4)
                   ffi_call (/usr/lib/libffi.so.6.0.4:0x7f3b54370c26)
                   g_cclosure_marshal_generic (/usr/lib/libgobject-2.0.so.0.5200.3:0x7f3b563d86a5)
                   g_closure_invoke (/usr/lib/libgobject-2.0.so.0.5200.3:0x7f3b563d7ea9)
                   ?? (/usr/lib/libgobject-2.0.so.0.5200.3:0x7f3b563ea4aa)
                   g_signal_emit_valist (/usr/lib/libgobject-2.0.so.0.5200.3:0x7f3b563f2c81)
                   g_signal_emit (/usr/lib/libgobject-2.0.so.0.5200.3:0x7f3b563f369b)
                   gst_bus_sync_signal_handler (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5665c964)
                   gst_bus_post (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5665cc4a)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b56672bd8)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5664e6da)
                   gst_element_post_message (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b56675a2c)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5664ea27)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5669c4ee)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5664c094)
                   gst_bus_post (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5665cc20)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b56672bd8)
                   gst_element_post_message (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b56675a2c)
                   gst_element_message_full_with_details (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b5667610c)
                   ?? (/usr/lib/libgstbase-1.0.so.0.1202.0:0x7f3b5310c047)
                   ?? (/usr/lib/libgstreamer-1.0.so.0.1202.0:0x7f3b566c407f)
                   ?? (/usr/lib/libglib-2.0.so.0.5200.3:0x7f3b561274ac)
                   ?? (/usr/lib/libglib-2.0.so.0.5200.3:0x7f3b56126ae1)
                   start_thread (/usr/lib/libpthread-2.25.so:0x7f3b54de9045)
                   __clone (/usr/lib/libc-2.25.so:0x7f3b55a61f0b)




    ==== Got criticals. Return value set to 18 ====
         Critical error Error message posted by: audiotestsrc0
     Caps negotiation failed starting from pad 'capsfilter:sink' as the QUERY_CAPS returned EMPTY caps for the following possible reasons:
        -> Downstream caps struct 0 name 'video/x-raw' differs from filter caps struct 0 name 'audio/x-raw'. The exact reason could not be determined but here is the gathered information:
     - capsfilter:sink last query caps filter: audio/x-raw, format=(string){ S16LE, S16BE, U16LE, U16BE, S24_32LE, S24_32BE, U24_32LE, U24_32BE, S32LE, S32BE, U32LE, U32BE, S24LE, S24BE, U24LE, U24BE, S20LE, S20BE, U20LE, U20BE, S18LE, S18BE, U18LE, U18BE, F32LE, F32BE, F64LE, F64BE, S8, U8 }, layout=(string)interleaved, rate=(int)[ 1, 2147483647 ], channels=(int)[ 1, 2147483647 ]
     - capsfilter:sink possible caps (as returned by a query on it without filter): video/x-raw


    Issues found: 2
    Returning 18 as errors were found

    =======> Test FAILED (Return value: 18)




硬體加速 (Hardware Acceleration)
========================================

VA-API
------------------------------

VA-API 是一套開源的 Library 和 API 定義（由 Intel 主推的），
提供一個抽象層來使用硬體處理影像，
硬體廠商可以為這套 API 實做自己的硬體支援。

* `freedesktop.org - VAAPI <https://www.freedesktop.org/wiki/Software/vaapi/>`_
* `Wikipedia - Video Acceleration API <https://en.wikipedia.org/wiki/Video_Acceleration_API>`_
* `Gentoo Wiki - VAAPI <https://wiki.gentoo.org/wiki/VAAPI>`_
* `Arch Wiki - Hardware video acceleration <https://wiki.archlinux.org/index.php/Hardware_video_acceleration>`_
* [GitHub] `gstreamer-vaapi <https://github.com/GStreamer/gstreamer-vaapi>`_


.. code-block:: sh

    $ sudo pacman -S libva libva-utils
    $ sudo pacman -S libva-intel-driver   # for Intel
    $ vainfo
    libva info: VA-API version 0.40.0
    libva info: va_getDriverName() returns 0
    libva info: Trying to open /usr/lib/dri/i965_drv_video.so
    libva info: Found init function __vaDriverInit_0_40
    libva info: va_openDriver() returns 0
    vainfo: VA-API version: 0.40 (libva )
    vainfo: Driver version: Intel i965 driver for Intel(R) Skylake - 1.8.2
    vainfo: Supported profile and entrypoints
          VAProfileMPEG2Simple            :	VAEntrypointVLD
          VAProfileMPEG2Simple            :	VAEntrypointEncSlice
          VAProfileMPEG2Main              :	VAEntrypointVLD
          VAProfileMPEG2Main              :	VAEntrypointEncSlice
          VAProfileH264ConstrainedBaseline:	VAEntrypointVLD
          VAProfileH264ConstrainedBaseline:	VAEntrypointEncSlice
          VAProfileH264ConstrainedBaseline:	VAEntrypointEncSliceLP
          VAProfileH264Main               :	VAEntrypointVLD
          VAProfileH264Main               :	VAEntrypointEncSlice
          VAProfileH264Main               :	VAEntrypointEncSliceLP
          VAProfileH264High               :	VAEntrypointVLD
          VAProfileH264High               :	VAEntrypointEncSlice
          VAProfileH264High               :	VAEntrypointEncSliceLP
          VAProfileH264MultiviewHigh      :	VAEntrypointVLD
          VAProfileH264MultiviewHigh      :	VAEntrypointEncSlice
          VAProfileH264StereoHigh         :	VAEntrypointVLD
          VAProfileH264StereoHigh         :	VAEntrypointEncSlice
          VAProfileVC1Simple              :	VAEntrypointVLD
          VAProfileVC1Main                :	VAEntrypointVLD
          VAProfileVC1Advanced            :	VAEntrypointVLD
          VAProfileNone                   :	VAEntrypointVideoProc
          VAProfileJPEGBaseline           :	VAEntrypointVLD
          VAProfileJPEGBaseline           :	VAEntrypointEncPicture
          VAProfileVP8Version0_3          :	VAEntrypointVLD
          VAProfileVP8Version0_3          :	VAEntrypointEncSlice
          VAProfileHEVCMain               :	VAEntrypointVLD
          VAProfileHEVCMain               :	VAEntrypointEncSlice


VDPAU
------------------------------


Intel Media SDK
------------------------------


OMX
------------------------------

:Repo: https://github.com/GStreamer/gst-omx



開發小技巧
========================================

檢查是否可以收到串流
------------------------------

.. code-block:: sh

    gst-launch-1.0 udpsrc port=9327 ! fakesink dump=true


檢查串流內的格式
------------------------------

.. code-block:: sh

    gst-launch-1.0 -v rtspsrc location=rtsp://.../ ! fakesink


檢查 log，尋找 "media=(string)audio" 和 "media=(string)video" 的 caps，
套用到另外要用的 pipeline 裡：

.. code-block:: sh

    gst-launch-1.0 udpsrc port=9327 ! capsfilter caps="application/x-rtp, media=(string)audio, payload=(int)96, clock-rate=(int)12000, encoding-name=(string)MPEG4-GENERIC, encoding-params=(string)2, profile-level-id=(string)1, mode=(string)AAC-hbr, sizelength=(string)13, indexlength=(string)3, indexdeltalength=(string)3, config=(string)1490, a-sdplang=(string)en, ssrc=(uint)430961011, clock-base=(uint)0, seqnum-base=(uint)1, npt-start=(guint64)0, npt-stop=(guint64)596480000000, play-speed=(double)1, play-scale=(double)1" ! rtpmp4gdepay ! decodebin ! autoaudiosink


.. code-block:: sh

    gst-launch-1.0 udpsrc port=9327 ! capsfilter caps="application/x-rtp, media=(string)audio, payload=(int)96, clock-rate=(int)12000, encoding-name=(string)MPEG4-GENERIC, encoding-params=(string)2, profile-level-id=(string)1, mode=(string)AAC-hbr, sizelength=(string)13, indexlength=(string)3, indexdeltalength=(string)3, config=(string)1490, a-sdplang=(string)en, ssrc=(uint)430961011, clock-base=(uint)0, seqnum-base=(uint)1, npt-start=(guint64)0, npt-stop=(guint64)596480000000, play-speed=(double)1, play-scale=(double)1" ! rtpmp4gdepay ! aacparse ! faad ! autoaudiosink


.. code-block:: sh

    gst-launch-1.0 udpsrc port=9527 ! capsfilter caps='application/x-rtp, media=(string)video, payload=(int)97, clock-rate=(int)90000, encoding-name=(string)H264, packetization-mode=(string)1, profile-level-id=(string)42C01E, sprop-parameter-sets=(string)"Z0LAHtkDxWhAAAADAEAAAAwDxYuS\,aMuMsg\=\=", a-framesize=(string)240-160, a-sdplang=(string)en, a-cliprect=(string)"0\,0\,160\,240", a-framerate=(string)24.0, ssrc=(uint)1423328209, clock-base=(uint)0, seqnum-base=(uint)1, npt-start=(guint64)0, npt-stop=(guint64)596480000000, play-speed=(double)1, play-scale=(double)1' ! rtph264depay ! h264parse ! avdec_h264 ! autovideosink



範例
========================================

RTSP to WebM with HTML video tag
--------------------------------

.. code-block:: sh

    gst-launch-1.0 \
        webmmux name=webm ! tcpserversink host=127.0.0.1 port=8080 \
        rtspsrc location=rtsp://.../ ! \
        decodebin name=dmux \
        dmux. ! videoconvert ! vp8enc ! webm.video_0


.. code-block:: sh

    gst-launch-1.0 \
        webmmux name=webm ! tcpserversink host=127.0.0.1 port=8080 \
        rtspsrc location=rtsp://.../ ! \
        decodebin name=dmux \
        dmux. ! audioconvert ! vorbisenc ! webm.audio_0


.. code-block:: sh

    gst-launch-1.0 \
        webmmux name=webm ! tcpserversink host=127.0.0.1 port=8081 \
        uridecodebin uri=rtsp://.../ name=dmux \
        dmux. ! videoconvert ! vp8enc ! queue ! webm.video_0 \
        dmux. ! audioconvert ! audiorate ! vorbisenc ! queue ! webm.audio_0


HTML 範例：

.. code-block:: html

    <video width=640 height=480 autoplay>
     <source src="http://localhost:8081">
    </video>



Benchmark & Profiling
========================================



Term
========================================

* source
* sink
* pad
* bin
* pipeline



設計重點
========================================

Pipeline



Write Plugin
========================================

* `Writing GStreamer plugins and elements in Rust <https://coaxion.net/blog/2016/05/writing-gstreamer-plugins-and-elements-in-rust/>`_
* `Writing GStreamer Elements in Rust (Part 2) - Don’t panic, we have better assertions now <https://coaxion.net/blog/2016/09/writing-gstreamer-elements-in-rust-part-2-dont-panic-we-have-better-assertions-now-and-other-updates/>`_
* `Writing GStreamer Elements in Rust (Part 3) - Parsing data from untrusted sources like it’s 2016 <https://coaxion.net/blog/2016/11/writing-gstreamer-elements-in-rust-part-3-parsing-data-from-untrusted-sources-like-its-2016/>`_
* `Writing GStreamer Elements in Rust (Part 4) - Logging, COWs and Plugins <https://coaxion.net/blog/2017/03/writing-gstreamer-elements-in-rust-part-4-logging-cows-and-plugins/>`_



Real-Time Streaming
========================================

* rtspsrc
    - ``latency=0``
    - ``timeout=0``
    - ``drop-on-latency=true``
    - https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-good-plugins/html/gst-plugins-good-plugins-rtspsrc.html

* x264enc
    - ``tune=zerolatency``
    - ``speed-preset=superfast``

* gstrtpjitterbuffer
    - ``drop-on-latency=false``
    - ``latency=500``

* appsink
    - ``drop=true``
    - ``max-buffers=1``
    - https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-base-plugins/html/gst-plugins-base-plugins-appsink.html

* udpsrc
    - ``reuse=true``
    - ``retrieve-sender-address=false``
    - https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-good-plugins/html/gst-plugins-good-plugins-udpsrc.html



Cheatsheet
========================================

Check Receiving
------------------------------

用 ``fakesink dump=true`` 會把收到的資料以十六進位的方式輸出

.. code-block:: sh

    # 從 RTSP
    gst-launch-1.0 rtspsrc location=rtsp://... ! fakesink dump=true


Play Directly
------------------------------

.. code-block:: sh

    # 從攝影機
    gst-launch-1.0 v4l2src ! autovideosink

    # 從 RTSP
    gst-launch-1.0 rtspsrc location=rtsp://... ! decodebin ! autovideosink


    # 透過 playbin
    gst-launch-1.0 playbin uri=file:///path/to/video
    gst-launch-1.0 playbin uri=rtsp://...


Record
------------------------------

注意 ``-e``

.. code-block:: sh

    # 從攝影機
    gst-launch-1.0 -e v4l2src ! x264enc ! mp4mux ! filesink location=/tmp/sample.mp4

    # 從 RTSP
    gst-launch-1.0 -e rtspsrc location=rtsp://... ! decodebin ! x264enc ! mp4mux ! filesink location=/tmp/sample.mp4

    # 從 RTP
    gst-launch-1.0 -e udpsrc address=0.0.0.0 port=5566 ! application/x-rtp,media=video,payload=96,encoding-name=H264 ! rtph264depay ! decodebin ! x264enc ! mp4mux ! filesink location=/tmp/sample.mp4


Restart Pipeline in Application
========================================

先把 pipeline 的狀態設成 ``NULL`` ，
接著再設成 ``PLAYING`` ，
這樣就能把整個 pipeline 重啟。

.. code-block:: python

    pipeline.set_state(Gst.State.NULL)
    pipeline.set_state(Gst.State.PLAYING)



License
========================================

LGPL



GStreamer 0.10 -> 1.x
========================================

https://gstreamer.freedesktop.org/documentation/application-development/appendix/porting-1-0.html



GStreamer 1.14
========================================

* [2018][FOSDEM] `What's new in GStreamer <https://fosdem.org/2018/schedule/event/om_gstreamer/attachments/slides/2647/export/events/attachments/om_gstreamer/slides/2647/Tim_Muller___Whats_New_in_GStreamer___FOSDEM_2018.pdf>`_
    - AV1 支援，AV1 目前還在發展階段，效能還不夠好，但是已經可以嘗試
    - IPC pipeline，讓 pipeline 可以開在多個 process，且可以互相溝通
    - 支援使用 ring buffer 做 debug log
    - leak tracer 改進
    - latency tracer 改進
    - hlssink2
    - RTSP 2.0 支援
    - mp3 相關功能因為專利過期而將從 gst-plugins-ugly 移到 gst-plugins-good
    - OpenGL 支援從 gst-plugins-bad 移到 gst-plugins-base
    - WebRTC 支援
    - Meson build system 支援



參考
========================================

* `Licensing your applications and plugins for use with GStreamer <https://gstreamer.freedesktop.org/documentation/licensing.html>`_
* `gst-instruments - Easy-to-use profiler for GStreamer <https://github.com/kirushyk/gst-instruments>`_
* `GStreamer - core elements <https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gstreamer-plugins/html/gstreamer-plugins-plugin-coreelements.html#plugin-coreelements>`_
* `GStreamer Conference <https://gstreamer.freedesktop.org/conference/>`-
    - * `GStreamer Conference 2017 <https://gstconf.ubicast.tv/channels/#gstreamer-conference-2017>`_
* `Arch Wiki - GStreamer <https://wiki.archlinux.org/index.php/GStreamer>`_


Talks:

* `Sebastian Dröge & Luis de Bethencourt - GStreamer & Rust – A perfect match <https://www.youtube.com/watch?v=W_mnFFqpMpQ>`_


Articles:

* `GStreamer to Gain the First RTSP 2.0 Implementation! <https://blogs.s-osg.org/gstreamer-to-gain-the-first-rtsp-2-0-implementation/>`_
* `How to Test GStreamer Pipelines with gst-validate Scenarios <https://blogs.s-osg.org/creating-scenarios-gst-validate/>`_
* `Herostratus’ legacy - tag: gstreamer <https://blogs.igalia.com/vjaquez/tag/gstreamer/>`_
