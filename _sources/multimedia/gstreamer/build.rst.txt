========================================
GStreamer 編譯 (GStreamer Build)
========================================


.. contents:: 目錄


一般平台編譯
========================================

以前都要靠 Autotools，
現在有基於 Meson 的 `gst-build <https://github.com/GStreamer/gst-build>`_ ，
gst-build 可以控制要編譯哪些專案，
必要時也會自動抓其他相依 library 進來編譯，
跟以前的編譯流程比起來方便很多。


Cross Compile
========================================
