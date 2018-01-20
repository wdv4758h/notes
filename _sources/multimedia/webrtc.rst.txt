========================================
WebRTC
========================================


.. contents:: 目錄


架構
========================================

:URL: https://webrtc.org/architecture/


ICE
------------------------------

* lite mode
* full mode


Bundle
------------------------------

* bundle
		- 所有 media 都會經由一條 DTLS handshake 建起的連線傳輸
* non-bundle
		- media 會經由不同條 DTLS handshake 建起的連線傳輸


DTLS-SRTP
------------------------------

DTLS-SRTP 是 WebRTC 中交換金鑰的方式，
使用 DTLS 來交換接下來要使用在 SRTP 中的金鑰。

在發展初期是使用 SDES-SRTP，
但是因為安全問題被強烈禁止。

WebRTC 的實做一定要支援使用 RTP/SAVPF profile (RTP/SAVPF 基於 RTP/SAVP)，
影音傳輸一定要用 SRTP 傳輸，
純 RTP 被規範明確禁止。

交換金鑰的方式：

* SDES
* MIKEY
* ZRTP: 使用 Diffie-Hellman
* DTLS-SRTP



* `WebRTC MUST implement DTLS-SRTP but… MUST NOT implement SDES ? <https://webrtchacks.com/webrtc-must-implement-dtls-srtp-but-must-not-implement-sdes/>`_


WebRTC SDP
------------------------------

* `Anatomy of a WebRTC SDP <https://webrtchacks.com/sdp-anatomy/>`_



OpenWebRTC
========================================

:Repo: https://github.com/EricssonResearch/openwebrtc



Janus - WebRTC gateway
========================================

:Repo: https://github.com/meetecho/janus-gateway
:License: GPLv3/Commercial

C 寫的

把各式的東西包裝成 WebRTC 的形式，
讓一般瀏覽器可以連線來溝通。


* `Tutorial: writing a Janus video call plugin in Lua <http://www.meetecho.com/blog/tutorial-writing-a-janus-video-call-plugin-in-lua/>`_
* [2017] `Asynchronous event/state notifications in the Janus WebRTC server <https://archive.fosdem.org/2017/schedule/event/janus/attachments/slides/1430/export/events/attachments/janus/slides/1430/fosdem2017_janusevents_presentation.pdf>`_
* [2015] `Performance analysis of the Janus WebRTC gateway <https://www.iris.unina.it/retrieve/handle/11588/657296/89201/a4-amirante.pdf>`_



Kurento
========================================

:Repo: https://github.com/Kurento/kurento-media-server
:License: Apache License v2

C++ 寫的



Jitsi
========================================

:Repo: https://github.com/jitsi/jitsi

Java 寫的



Licode
========================================

:Repo: https://github.com/lynckia/licode
:License: MIT



參考
========================================

* `WebRTC 1.0: Real-time Communication Between Browsers <https://www.w3.org/TR/webrtc/>`_
* `AppRTC - WebRTC demo <https://github.com/webrtc/apprtc>`_
* `WebRTC Experiments & Demos <https://github.com/muaz-khan/WebRTC-Experiment/>`_
* `WebRTC 相關縮寫名詞簡介 <https://blog.mozilla.com.tw/posts/3261/webrtc-相關縮寫名詞簡介>`_
* `The RTP bleed Bug <https://www.rtpbleed.com/>`_
* `A Study of WebRTC Security <https://webrtc-security.github.io/>`_
* `Browser APIs and Protocols: WebRTC - High Performance Browser Networking (O'Reilly) <https://hpbn.co/webrtc/>`_
* `WebRTC in the real world: STUN, TURN and signaling <https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/>`_
* `Signaling and video calling - Web APIs | MDN <https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Signaling_and_video_calling>`_
* `Getting Started with WebRTC - HTML5 Rocks <https://www.html5rocks.com/en/tutorials/webrtc/basics/>`_
* `RFC 5245 - Interactive Connectivity Establishment (ICE): A Protocol for Network Address Translator (NAT) Traversal for Offer/Answer Protocols <https://tools.ietf.org/html/rfc5245>`_

* [GitHub] `Generic library for real-time communications with async IO support <https://github.com/creytiv/re>`_
