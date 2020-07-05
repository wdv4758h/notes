========================================
HTTP (Hypertext Transfer Protocol)
========================================


.. contents:: 目錄


歷史
========================================

+------+-----------+
| 年份 | HTTP 版本 |
+======+===========+
| 1991 | 0.9       |
+------+-----------+
| 1996 | 1.0       |
+------+-----------+
| 1997 | 1.1       |
+------+-----------+
| 2015 | 2.0       |
+------+-----------+



HTTP2
========================================

:RFC-7540: https://www.rfc-editor.org/rfc/rfc7540.txt
:HTTP2 explained: https://daniel.haxx.se/http2/


問題：

* 既有的 HTTP1.1 latency 過高
* 改善 TCP 實做雖有幫助，但是還是不夠
* 網頁資料量日益增加，問題逐漸加重


HTTP1.1 latency 的暫時解決方案：

* HTTP pipelining
  - 在 request 得到回應前就先排隊處理，需要更多底層支援，不是每個瀏覽器都有
* Spriting
  - 多個圖合成一個圖傳輸，客戶端端再切割成數個圖片
* Inlining
  - 把圖片直接用 base64 的形式寫在 CSS
* Concatenation
  - 把多個 JavaScript 合成一份
* Sharding
  - 把服務分散在數個不同的 host
  - HTTP 1.1 規範有限制每個 host 最大的 TCP 連線數量
  - 藉由分散在多個 host 可以達到更多連線
  - 使用 cookie-free 的圖像 host 也可以改善速度


HTTP2 的設計限制:

* 依然是原本的 HTTP 流程，底下依然使用 TCP
* URL 依然是 http:// 或 https://
* 為了漸進的轉換，HTTP2 伺服器要可以處理 HTTP1
* 減少規範內選擇性的功能，減少各實做間的差異問題
* 不再有小版號，是否相容 HTTP2 要一翻兩瞪眼，新的擴充或改動就留給 HTTP3


HTTP2 內容：

* 起源於 Google 的 SPDY 專案
    - 有實做證明這方向是可行的
    - HTTP2 基於 SPDY/3 去修改
* 銜接既有的 HTTP1.1
    - HTTP1.1 支援 ``Upgrade: header`` ，但是這會造成額外的 latency
    - 規範沒有限制一定要用 TLS，但是 Mozilla 和 Google 都表示只會實做 TLS 加密版本
    - SPDY 在 TLS 新增 NPN (Next Protocol Negotiation)，伺服器主動告知支援哪些版本，使用端選擇要用的版本
    - HTTP2 基於 NPN 做了修改，形成了 ALPN (Application Layer Protocol Negotiation)
        + NPN 由伺服器告訴使用端支援的版本，使用端回傳使用的版本
        + ALPN 由使用端告訴伺服器支援的版本，伺服器回傳使用的版本
* HTTP2 是 binary protocol （和 HTTP1 不同）
* header 壓縮
    - HTTP 是 stateless protocol，所以每個 request 都需要帶著所有需要的資訊
    - 連日益成長的 cookie 也要放在每個 request 裡
    - HTTP1.1 的 request 大小常常大於起始的 TCP window，需要完整的來回取得 ACK 後才能傳送真正的資料
    - 過去 HTTPS 和 SPDY 易受到 BREACH 和 CRIME 攻擊，HTTP2 針對這問題設計了 HPACK
* Multiplexed streams
    - 一個 HTTP2 連線可以包含多個並行的 stream
    - 數個不同的 stream 可以共享連線
* stream 優先度和相依性
    - 藉由 ``PRIORITY`` frame 可以告知伺服器連線的優先度，讓重要的內容先傳送
* server push
    - 當客戶端需要 X 時，伺服器可以連接下來可能需要的 Y 一起傳送給客戶端
    - 客戶端必須明確地告知伺服器才能使用這功能



HTTP3
========================================

:HTTP3 explained: https://daniel.haxx.se/http3-explained/


TL;DR: HTTP3 是基於 QUIC （基於 UDP） 的 HTTP2 替代，換掉本來 TCP + TLS + HTTP2 的架構


為什麼要用 QUIC：

* 回顧 HTTP2
    - HTTP2 修了 TCP 連線過多的問題，搭配 desharding 技術可以更大幅減少需要的連線
    - HTTP2 修了 HTTP head of line blocking 問題，客戶端不再需要等第一個 request 完成才能發送下一個 request
* TCP head of line blocking
* TCP or UDP
    - 新的 Transport Protocol 難以部署，因為現有的裝置很多，新的 Transport Protocol 容易被舊有的裝置擋掉，這狀況也幾乎不可能完整克服。
    - SCTP-over-UDP 不完全符合 QUIC 的目標，所以不能直接拿來用
    - QUIC 在 UDP 之上實做類似 TCP 的掉包重傳和壅塞控制，並使用 TLS 1.3
* Protocol Ossification
* 安全
* 減少 latency
* HTTP2 在應用層做改進，HTTP3 在 Transport 層做改進


QUIC Protocol 功能：

* 基於 UDP
* 可靠性
    - QUIC 在 UDP 之上加了重傳以及壅塞控制等功能，把一些 TCP 的特色實做在 UDP 之上
* Streams
    - 分離邏輯上的 stream 和實際的連線
* 有序
    - QUIC 在同一個 stream 內保證有序的傳輸，但是不同 stream 之間就沒有這保證
* 快速的 handshakes
    - 提供 0-RTT 和 1-RTT 連線建立
* TLS 1.3
    - 使用 TLS 1.3 且不能不加密
    - TLS 1.3 有新功能可以減少 handshake，使用 TLS 1.3 可以改進 latency
    - 先前的 Google QUIC 使用的是自己客製化的加密
* Transport 與應用
    - 先前的 Google QUIC 把 Transport 和 HTTP 結合在一起，使得應用比較受限
    - IETF QUIC 把 HTTP 的部份抽開，讓 QUIC 專心處理 Transport 的事情，不再綁定 HTTP
* HTTP over QUIC
    - 成為 HTTP3
* Non-HTTP over QUIC
    - 為了讓 QUIC v1 如期完成，這部份放到 QUIC v2


QUIC 如何運作：

* 連線：
    - 使用 Connection ID 來區分
    - 透過 Connection ID 可以在不同的 IP 和網卡間切換，這在 TCP 是做不到的
* TLS：
    - 使用 TLS 1.3 且不能不加密
* Stream：
    - 輕量有序的 byte-stream
    - 兩種方向，unidirectional streams 和 bidirectional streams
* 0-RTT：
    - 客戶端如果先前有建立過連線可以把相關參數 cache 起來，在後續連線時跳過 handshake 階段
* Spin Bit：
    - 為了滿足測量 latency 的需求
    - 一些反對的聲音是這個作法會有潛在的資訊外洩
* User space 實做：
    - 目前 QUIC 的實做幾乎都在 user space
    - user space 的實做方便快速的演進
    - 目前有多種實做可以比較與競爭
    - 未來也可能把實做整合進 kernel 中
* API：
    - TCP 有定義良好的 API，在不同平台間都運作相同
    - QUIC 還沒有走到這一步，目前沒有定義良好的 API，API 要看 library 實做
    - 由於沒有標準 API，再加上 QUIC 通常被實做在 user space，在不同 library 間轉換需要比較高的成本


HTTP3 特色：

* ``https://`` URL：
    - HTTP3 依然使用既有的 HTTPS URL
    - 客戶端可以平行地嘗試用不同 HTTP 版本連入
    - 伺服器也可以建議客戶端使用比較新的版本
* ``Alt-Svc`` 初始化：
    - 當客戶端使用舊版本連入伺服器時，伺服器可以在回傳加上先前規範的 ``Alt-Svc`` Header 告知客戶端可以使用 HTTP3
* QUIC stream 與 HTTP3：
    - HTTP3 設計上要完全利用 QUIC 的特色，所以 stream 是直接利用 QUIC stream
    - HTTP2 則需要在 TCP 之上設計自己的 stream 和多工概念
* HTTP3 優先權：
    - 功能類似 HTTP2
    - stream 權重設定在 1 ~ 256
* HTTP3 Server Push：
    - 功能類似 HTTP2 的 Server Push，但是用不同機制
    - 當客戶端需要 X 時，伺服器可以連接下來可能需要的 Y 一起傳送給客戶端
    - 在 HTTP2 客戶端必須明確地告知伺服器才能使用這功能，而 HTTP3 則又加了推送數量可以讓客戶端設定
    - 就算客戶端沒有說要用這功能，伺服器也可以發訊息建議客戶端設定
    - 這功能一直都有爭議，雖然少了一半的來回時間，但是伺服器端不太能知道資料要不要推送過去
* HTTP3 vs HTTP2：
    - 相同
        + 支援 stream，HTTP2 在 HTTP 層處理 stream，HTTP3 則在 QUIC 處理 stream
        + 支援 Server Push
        + 具有 Header 壓縮，QPACK 和 HPACK 的設計類似，但是 QPACK 支援非順序的 stream
        + 支援多工，可以在一個連線上支援多個 stream
        + streame 具有優先權
    - 不同
        + HTTP3 的資料通常比較早送到，受益於 QUIC 的 0-RTT handshakes，TCP Fast Open 和 TLS 則比較常碰到問題
        + HTTP3 handshake 速度比較快
        + HTTP3 一定要加密，HTTP2 沒有這強制性（雖然實做幾乎都強制加密）
        + HTTP2 可以在 TLS handshake 時利用 ALPN 擴充來溝通，而 HTTP3 則需要 ``Alt-Svc:`` header 回傳給客戶端


常見問題：

* UDP 在 kernel 中比 TCP 慢 ➡ TCP 一直以來受到比較多關注，優化的比較成熟，UDP 狀況會逐漸變好
* QUIC 需要比較多 CPU ➡ TCP 和 TLS 優化比較多，甚至有硬體輔助，QUIC 的狀況會逐漸變好


QUIC 和 HTTP3 規範：

* QUIC 的屬性
* QUIC - 基於 UDP 的多工且安全的 Transport
* QUIC 掉包偵測與壅塞控制
* TLS 與 QUIC
* 基於 QUIC 的 HTTP
* QPACK - HTTP over QUIC 的 Header 壓縮


QUIC v2 （為了讓 HTTP3 和 QUIC v1 可以如期完成而沒加入的功能）：

* FEC (Forward Error Correction)
    - 傳送端傳送多餘的資料，接收端從收到的資料中選擇沒有明顯錯誤的資料使用
    - 這功能還在討論中，還需實驗證明成效與所需的額外成本
* Multipath
    - Transport 自己可以選擇多種網路路線，藉此提升資源利用率與備援
    - SCTP 和現代的 TCP 已經有這功能的支援
* 不可靠的資料傳輸
    - 提供設定來支援不可靠得資料傳輸，取代原本 UDP 類型的應用
* 非 HTTP 的應用
    - DNS over QUIC



參考
========================================

* `Wikipedia - HTTP <https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol>`_
* `Wikipedia - ALPN (Application-Layer Protocol Negotiation) <https://en.wikipedia.org/wiki/Application-Layer_Protocol_Negotiation>`_
* `Wikipedia - QUIC <https://en.wikipedia.org/wiki/QUIC>`_
* `HTTP2 explained <https://daniel.haxx.se/http2/>`_
* `HTTP3 explained <https://daniel.haxx.se/http3-explained/>`_
* `simple HTTP/2 server <https://github.com/googlechrome/simplehttp2server>`_
* `Is TLS Fast Yet? <https://istlsfastyet.com/>`_
* `nghttp2 - HTTP/2 C Library and tools <https://github.com/nghttp2/nghttp2>`_
* `A Detailed Look at RFC 8446 (a.k.a. TLS 1.3) <https://blog.cloudflare.com/rfc-8446-aka-tls-1-3/>`_
