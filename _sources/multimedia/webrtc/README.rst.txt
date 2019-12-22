========================================
WebRTC
========================================


WebRTC 是網頁的即時通訊協定，
支援點對點（P2P）傳輸，
目標是提供豐富、高品質的 RTP 應用程式。

基本上
WebRTC = SDP + ICE + 任何 Signaling 機制，
SDP 用來描述多媒體的內容（有幾個影像和音訊、加密方式、額外屬性等等），
ICE 用來列出客戶間可能的溝通路徑（點對點、防火牆打洞、外部轉送等等），
Signaling 則是在客戶間建立起連線前的傳輸機制
（把 SDP 和 ICE 傳給對方的方式，可以透過 WebSocket、純 TCP、MQTT 等任何方式）。


.. image:: https://webrtcglossary.com/wp-content/uploads/2014/09/WebRTC-stack.png


* 多媒體格式
    - 影像格式
        + VP8
        + VP9
        + H264
    - 聲音格式
        + Opus

* P2P 連線建立
    - 連線路徑
        + 同個網路：直接對連
        + 不同網路，但可以透過防火牆打洞：STUN
        + 不同網路，且防火牆打洞不通，外部轉送：TURN
    - 路徑描述
        + 一次把所有可能路徑找完：ICE
        + 找到一個可能路徑就傳給對方試：Trickle ICE

* Signaling
    - 溝通模型
        + Peer A: 建立 Offer SDP
        + Peer A: Offer SDP 透過選定的溝通方式傳給 Peer B
        + Peer B: 接收 Peer A 的 Offer SDP
        + Peer B: 建立 Answer SDP
        + Peer B: Answer SDP 透過選定的溝通方式傳給 Peer A
        + Peer A: 可能的路徑 A1 (Trickle ICE) 透過選定的溝通方式傳給 Peer B
        + Peer B: 可能的路徑 B1 (Trickle ICE) 透過選定的溝通方式傳給 Peer A
        + Peer A: 可能的路徑 A2 (Trickle ICE) 透過選定的溝通方式傳給 Peer B
        + Peer B: 可能的路徑 B2 (Trickle ICE) 透過選定的溝通方式傳給 Peer A
        + Peer A: 可能的路徑 A# (Trickle ICE) 透過選定的溝通方式傳給 Peer B
        + Peer B: 可能的路徑 B# (Trickle ICE) 透過選定的溝通方式傳給 Peer A
        + Peer A/B: 路徑 Ax 和 By 可以通，雙方的連線建立
    - 溝通協定（WebRTC 規範沒有指定，可以自行根據需求選用）
        + HTTP
        + WebSocket
        + SIP
        + ...

* 加密方式
    - DTLS

* 連線所使用的協定
    - 負責傳輸多媒體的 RTCPeerConnection 底下是用 SRTP
        + 因為加密的部份使用 DTLS 建立，因此稱為 DTLS-SRTP
    - 負責傳輸任意資料的 DataChannel 底下是用 SCTP
        + SCTP over DTLS
        + 未來有可能使用 QUIC 代替 SCTP

* 連線加速
    - 減少需要建立的連線數量
        + RTCP mux ➡ RTP 和 RTCP 用同一個 port
        + RTP bundle ➡ Video/Audio RTP 用同一個 port
        + RTCP mux + RTP bundle ➡ Video RTP + Video RTCP + Audio RTP + Audio RTCP 全部用同一個 port

* 多使用者的傳送模型
    - Mesh：網狀，每個參與者都傳送資料給其他所有參與者
        + 優點：不需要額外伺服器處理串流
        + 缺點：參與者多的時候連線量大、下載量大、上傳量大
        + 假設有 N 個參與者在使用 conference room，每個參與者都需要傳輸 M 大小的資料
        + 每個參與者需要建 N-1 個連線
        + 每個參與者下載需要 M * (N-1)
        + 每個參與者上傳需要 M * (N-1)
        + 整個網路需要 C(N, 2) 個連線，例如 C(5, 2) = 10
        + 整個網路的傳輸需要 M * (N-1) * N
    - SFU：參與者都把資訊交給伺服器，伺服器把影像直接轉送給其他參與者
        + Selective Forwarding Unit
        + 優點：在參與者多的情況下，上傳量不會跟著成長。雖然需要額外伺服器，但是伺服器需求不大，只要複製串流轉送
        + 缺點：參與者多的時候連線量大、下載大
        + 假設有 N 個參與者在使用 conference room，每個參與者都需要傳輸 M 大小的資料
        + 每個參與者需要建 N 個連線
        + 每個參與者下載需要 M * (N-1)
        + 每個參與者上傳需要 M
        + 整個網路需要 N * N 個連線
        + 整個網路的傳輸需要 M * N * N
    - MCU：參與者都把資訊交給伺服器，伺服器把所有影像混合後交給每個參與者
        + Multipoint Control Unit
        + 優點：在參與者多的情況下，連線量、上傳量、下載量不會跟著成長
        + 缺點：伺服器需求量較大，需要混合所有串流再轉送
        + 假設有 N 個參與者在使用 conference room，每個參與者都需要傳輸 M 大小的資料
        + 每個參與者需要建 1 個連線
        + 每個參與者下載需要 M
        + 每個參與者上傳需要 M
        + 整個網路需要 N 個連線
        + 整個網路的傳輸需要 2 * N * M

* 掉封包的處理
    - Concealment
        + 把問題隱藏掉，例如解碼器經過處理後讓使用者沒有掉資料的感覺
    - Retransmission
        + 叫對方重傳資料，但是這對於即時串流來說通常效果不好，因為資料有效性可能已經過了
    - FEC (Forward Error Correction)
        + 來源端在傳送時直接多傳幾次，提升傳送成功率

* 相關實做
    - libnice (ICE)
    - libwebrtc (Google WebRTC 實做)
    - `GStreamer <gstreamer-webrtc.rst>`_
    - Janus
    - Kurento
    - Python aiortc



* 文章
    - [2018] `How Discord Handles Two and Half Million Concurrent Voice Users using WebRTC <https://blog.discordapp.com/how-discord-handles-two-and-half-million-concurrent-voice-users-using-webrtc-ce01c3187429>`_
