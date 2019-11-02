========================================
GStreamer Talks
========================================


.. contents:: 目錄


GStreamer Conference 2019 - GStreamer State of the Union
========================================================

:Speaker: Tim-Philipp Mülle
:Video: https://gstconf.ubicast.tv/videos/gstreamer-state-of-the-union_81677/


* 已經釋出的 GStreamer 1.16
    - WebRTC 改善（Data Channel、BUNDLE、多個 TURN servers）
    - AV1 支援
    - 硬體支援改進
    - video aggregator
    - 瀏覽器來源（基於 WebKit，可以把網頁當成 video stream）
    - GstTranscoder
    - Latency 改善（payloaders, depayloaders, parsers, decoders, encoders）
    - AVTP
    - RIST（Reliable Internet Stream Transport）
    - RTP 支援改善
    - MPEG-TS muxing 改善
    - Vulkan 支援改善
    - HDR (High Dynamic Range) video
* 規劃 GStreamer 1.18
* 遷移到 GitLab
* Build System 從 Autotools 改成 Meson
* 文件系統從 gtk-doc 改成 hotdoc



GStreamer Conference 2019 - The First Stable libcamera Release: A Call for Public API Review
============================================================================================

:Video: https://gstconf.ubicast.tv/videos/the-first-stable-libcamera-release-a-call-for-public-api-review/
:Site: https://libcamera.org


把相機的操控抽象化，
各廠商仍然可以保留自己不想公開的部份，
但是不同廠商可以透過 libcamera 共用同樣的界面。



GStreamer Conference 2019 - Revisiting RTP Jitter Buffer Timers
===============================================================

:Video: https://gstconf.ubicast.tv/videos/revisiting-rtp-jitter-buffer-timers/



GStreamer Conference 2019 - Introduction to Validateflow
========================================================

:Video: https://gstconf.ubicast.tv/videos/introduction-to-validateflow/


GStreamer Conference 2019 - Karapulse - Writing a Karaoke Application in Rust
=============================================================================

:Video: https://gstconf.ubicast.tv/videos/karapulse-writing-a-karaoke-application-in-rust/



GStreamer Conference 2019 - 20 Years of GStreamer
=================================================

:Speaker: Wim Taymans (wtay)



GStreamer Conference 2018 - GStreamer State of the Union
========================================================

:Video: https://gstconf.ubicast.tv/videos/gstreamer-state-of-the-union_42782/


已經釋出的 GStreamer 1.14:

* WebRTC
* AV1 codec
* V4L2 improvement
* SRT (Secure Reliable Transport)
* FEC (Forward Error Correction)
* RTSP 2.0
* ONVIF audio backchannel support
* playbin3 gapless playback and pre-buffering
* QuickTime muxer prefill recording
* rtpjitterbuffer fast-start mode
* NVDEC
* Adaptive DASH trick playback
* ipcpipeline
* C# binding update


準備在 GStreamer 1.16 釋出的:

* core optimization to improve latency and speed
* WebRTC improvement
* interlaced video improvement
* closed caption support
* WebM DRM support
* FFmpeg 4.0 upgrade
* RTSP server improvement
* Intel media SDK improvement
* plugins improvement, so modules can move from -bad to -good/-base/core


未來:

* neural network integration
* scaleable streamings in decodebin3/playbin3
* performance improvement


其他:

* Meson build system
* move to GitLab
* Rust support


更多可能的改善:

* easier for simple server, e.g. souphttpserversink, rtspserversink
* stream API
* Windows/iOS/Android
* more tracers
* SDI-over-IP
* ONVIF RTSP extensions
* OpenCV intergration
* VR
* official modern forum
* nightly builds



GStreamer Conference 2018 - GstInference: A GStreamer Deep Learning Framework
=============================================================================

:Video: https://gstconf.ubicast.tv/videos/gstinference-a-gstreamer-deep-learning-framework/
:Wiki: https://developer.ridgerun.com/wiki/index.php?title=GstInference



GStreamer Conference 2018 - nnstreamer: Neural Networks as GStreamer Filters
============================================================================

:Video: https://gstconf.ubicast.tv/videos/nnstreamer-neural-networks-as-gstreamer-filters/
:Repo: https://github.com/nnsuite/nnstreamer



GStreamer Conference 2018 - Bringing Deep Neural Networks to GStreamer
======================================================================

:Video: https://gstconf.ubicast.tv/videos/bringing-deep-neural-networks-to-gstreamer/



GStreamer Conference 2018 - Streams and collections: we're not done yet!
========================================================================

:Video: https://gstconf.ubicast.tv/videos/streams-and-collections-were-not-done-yet/



GStreamer Conference 2018 - Profiling GStreamer applications with HawkTracer and tracing subsystem
==================================================================================================

:Video: https://gstconf.ubicast.tv/videos/profiling-gstreamer-applications-with-hawktracer-and-tracing-subsystem/



GStreamer Conference 2018 - Android camera source 2 - a continuation story
==========================================================================

:Video: https://gstconf.ubicast.tv/videos/android-camera-source-2-a-continuation-story/



GStreamer Conference 2018 - Trust but verify. Our road to robust multimedia and graphics stack verification (aka Multimedia testing on the budget for everyone)
===============================================================================================================================================================

:Video: https://gstconf.ubicast.tv/videos/trust-but-verify-our-road-to-robust-multimedia-and-graphics-stack-verification-aka-multimedia-testing-on-the-budget-for-everyone/



GStreamer Conference 2018 - Discovering Video4Linux CODECs
==========================================================

:Video: https://gstconf.ubicast.tv/videos/discovering-video4linux-codecs/



GStreamer Conference 2018 - What's new with GStreamer & Rust
============================================================

:Video: https://gstconf.ubicast.tv/videos/whats-new-with-gstreamer-rust/



GStreamer Conference 2018 - Experiences with gstreamer/webrtc
=============================================================

:Video: https://gstconf.ubicast.tv/videos/experiences-with-gstreamer-webrtc/



GStreamer Conference 2018 - GStreamer CI for embedded platforms
===============================================================

:Video: https://gstconf.ubicast.tv/videos/gstreamer-ci-for-embedded-platforms/



GStreamer Conference 2018 - Lightning talks
===========================================

:Video: https://gstconf.ubicast.tv/videos/lightning-talks_54780/
