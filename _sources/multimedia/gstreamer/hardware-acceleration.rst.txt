============================================
GStreamer & 硬體加速 (Hardware Acceleration)
============================================


.. contents:: 目錄


介紹
========================================

參考：
`硬體加速 (Hardware Acceleration) </multimedia/hardware-acceleration.rst>`_


目前大約有九種影像解碼的硬體加速 API：

* VAAPI
* VDPAU
* OpenMAX
* OVD
* DCE
* Android MediaCodec
* Apple VideoTool Box Framework
* Video4Linux
* NVENC/NVDEC



GStreamer & VA-API
========================================

在 ``gstreamer-vaapi`` 裡



GStreamer & VDPAU
========================================

在 ``gst-plugins-bad`` 的 ``vdpau`` 裡



GStreamer & OpenMAX
========================================

在 ``gst-omx`` 裡



GStreamer & OVD
========================================



GStreamer & DCE
========================================



GStreamer & Android MediaCodec
========================================

在 ``gst-plugins-bad`` 的 ``androidmedia`` 裡



GStreamer & Apple VideoTool Box Framework
=========================================

在 ``gst-plugins-bad`` 的 ``applemedia`` 裡，
分別是 ``vtenc`` 和 ``vedec``



GStreamer & V4L2
========================================

在 ``gst-plugins-good`` 的 ``v4l2`` 裡



GStreamer & NVDEC/NVENC
========================================

在 ``gst-plugins-bad`` 的 ``nvenc`` 和 ``nvdec`` 裡
