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
  - 多個圖合成一個圖傳輸，使用者端再切割成數個圖片
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
    - 當使用者需要 X 時，伺服器可以連接下來可能需要的 Y 一起傳送給使用者
    - 使用者必須明確地告知伺服器才能使用這功能



參考
========================================

* `Wikipedia - HTTP <https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol>`_
* `Wikipedia - ALPN (Application-Layer Protocol Negotiation) <https://en.wikipedia.org/wiki/Application-Layer_Protocol_Negotiation>`_
* `HTTP2 explained <https://daniel.haxx.se/http2/>`_
* `HTTP3 explained <https://daniel.haxx.se/http3/>`_
* `simple HTTP/2 server <https://github.com/googlechrome/simplehttp2server>`_
* `Is TLS Fast Yet? <https://istlsfastyet.com/>`_
* `nghttp2 - HTTP/2 C Library and tools <https://github.com/nghttp2/nghttp2>`_
