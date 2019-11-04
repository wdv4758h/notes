========================================
HTTP Streaming
========================================


.. contents:: 目錄


目標
========================================

讓客戶端可以存取 HTTP 的 API 拿到影像，
影像不一定要完整存在 HTTP 伺服器上，
可以片段地傳送給客戶端。



小技巧
========================================

可以利用 ``curl -v`` 觀察 HTTP 的 headers。


.. code-block:: sh

    curl                http://example.com/test.mp4 -v -o /dev/null
    curl --range 0-1    http://example.com/test.mp4 -v -o /dev/null
    curl --range 2-1000 http://example.com/test.mp4 -v -o /dev/null



MP4
========================================

faststart
------------------------------

為了要讓客戶端可以盡早開始播放，
MP4 最好要先處理過。


FFmpeg：

.. code-block:: sh

    ffmpeg -i input.mp4 -c copy -movflags +faststart output.mp4


Android
------------------------------

HTTP 回傳 header 範例：

::

    content-type: video/mp4
    content-length: 417378
    content-range: bytes 0-417377/417378
    accept-ranges: bytes


流程：

::

    Android: "I want to see this video"
    Server: "OK, the video size is 1234567 bytes, data will come piece by piece asap"
    Android: "got it"



iOS
------------------------------

iOS 的播放器一定要透過 HTTP header 裡的 Range request 來存取想要的資料，
其中 iOS 第一個送出的 Range request 會要 bytes 0~1 來試探並確認大小。

HTTP request header 範例：

::

    Range: bytes=0-1


HTTP 回傳 header 範例：

::

    content-type: video/mp4
    content-length: 2
    content-range: bytes 0-1/417378
    accept-ranges: bytes


流程：

::

    iOS: "show me what you got for this video"
    Server: "OK, the video size is 1234567 bytes"
    iOS: "now give me first 3000 bytes"
    Server: "here you go"
    iOS: "now give me next 3000 bytes"
    Server: "here you go"
    iOS: "now give me next 5000 bytes"
    Server: "here you go"



參考
========================================

* `Serving a .mp4 file with Flask <https://stackoverflow.com/a/54879747>`_
