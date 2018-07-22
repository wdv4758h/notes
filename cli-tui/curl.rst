========================================
curl
========================================


.. contents:: 目錄


範例
========================================

檢查支援：

.. code-block:: sh

    $ curl --version
    curl 7.59.0 (x86_64-pc-linux-gnu) libcurl/7.59.0 OpenSSL/1.1.0h zlib/1.2.11 libidn2/2.0.4 libpsl/0.20.1 (+libidn2/2.0.4) nghttp2/1.31.0
    Release-Date: 2018-03-14
    Protocols: dict file ftp ftps gopher http https imap imaps pop3 pop3s rtsp smb smbs smtp smtps telnet tftp
    Features: AsynchDNS IDN IPv6 Largefile GSS-API Kerberos SPNEGO NTLM NTLM_WB SSL libz TLS-SRP HTTP2 UnixSockets HTTPS-proxy PSL


下載到指定檔案：

.. code-block:: sh

    curl http://example.com -o filename


下載、處理重導向、處理續傳：

.. code-block:: sh

    curl -O -L -C - http://example.com/filename


送出 JSON：

.. code-block:: sh

    curl -d '{"name":"bob"}' -H 'Content-Type: application/json' http://example.com/users/1234


POST：

.. code-block:: sh

    curl -d 'name=bob' http://example.com/form


測試 websocket：

.. code-block:: sh

    curl --include \
         --no-buffer \
         --header "Connection: Upgrade" \
         --header "Upgrade: websocket" \
         --header "Host: example.com:80" \
         --header "Origin: http://example.com:80" \
         --header "Sec-WebSocket-Key: SGVsbG8sIHdvcmxkIQ==" \
         --header "Sec-WebSocket-Version: 13" \
         http://example.com:80/
