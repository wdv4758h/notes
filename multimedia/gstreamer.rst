========================================
GStreamer
========================================


.. contents:: 目錄


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



Python Binding
========================================

安裝：

.. code-block:: sh

    $ sudo pacman -S gst-python


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



License
========================================

LGPL



參考
========================================

* `Licensing your applications and plugins for use with GStreamer <https://gstreamer.freedesktop.org/documentation/licensing.html>`_
* `gst-instruments - Easy-to-use profiler for GStreamer <https://github.com/kirushyk/gst-instruments>`_
