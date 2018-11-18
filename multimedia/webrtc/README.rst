========================================
WebRTC
========================================

* `介紹 <introduction.rst>`_
* 架構介紹
* DTLS
* SRTP
* ICE
    - STUN
    - TURN
    - Trickle ICE
* 影像格式
    - VP8
    - H264
* 聲音格式
    - Opus
* 格式設定：SDP
* RTCP mux ➡ RTP 和 RTCP 用同一個 port
* RTP bundle ➡ Video/Audio RTP 用同一個 port
* RTCP mux + RTP bundle ➡ Video RTP + Video RTCP + Audio RTP + Audio RTCP 全部用同一個 port
* 傳送模型
    - Mesh
    - SFU
    - MCU
* Signaling Server (WebRTC 規範未定義細節的部份)

* 相關實做
    - libnice (ICE)
    - libwebrtc (Google WebRTC 實做)
    - `GStreamer <gstreamer-webrtc.rst>`_
    - Janus
    - Kurento
