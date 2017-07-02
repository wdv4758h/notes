===========
shadowsocks
===========
shadowsocks 是個 socks5 proxy，非常容易架設


Server Deployment
------------------
1.  安裝: ``pip install shadowsocks``

    + shadowsocks 需要 libcrypto，若 Server 為 Windows 需要另外安裝 openssl

      * openssl 有 32/64 bit 的差異，請注意要和 Python 的版本相同

2.  執行: ``ssserver -p 443 -k your-password -m aes-256-cfb``

    + 背景執行

      * ``sudo ssserver -d start --user nobody`` 可在背景執行
      * ``sudo ssserver -d stop`` 關閉


Client
-------
至 `https://shadowsocks.org/en/download/clients.html`_ 下載安裝所需的 Client

新增好伺服器後，到系統的 Proxy 設定頁面作進一步設定


Windows
`````````
「網際網路 - 內容」>「連線」>「LAN 設定」>「Proxy 伺服器」

IP 輸入 ``127.0.0.1`` ，Port 輸入 Client 設定的值，預設應該是 ``1080``


Mac OS X
``````````
先在 shadowsocks 的 Menu 中選擇「Global Mode」

「系統偏好設定」>「網路」>「進階」>「代理伺服器」>「SOCKS 代理伺服器」

IP 輸入 ``127.0.0.1`` ，Port 輸入 ``1080``

Mac OS X 的 shadowsocks Client 可能沒有更改 Local Port 的功能


iOS
`````
shadowsocks-iOS 內建網頁瀏覽器，設定好以後可以直接上網

iOS 本身不支援 SOCKS Protocol，需透過 HTTP Proxy 將流量導往 shadowsocks-iOS，再由它透過 SOCKS Protocol 送出流量

「Settings」>「Wi-Fi」>「HTTP Proxy」>「Auto」

URL 輸入 ``http://127.0.0.1:8090/proxy.pac``

由於 iOS 的限制，在沒有越獄的狀況下，shadowsocks-iOS 運作大約 10 分鐘就會被系統停止
