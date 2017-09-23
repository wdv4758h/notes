========================================
RTSP
========================================


.. contents:: 目錄


RTSP 1.0 (RFC 2326) (1998)
========================================

RTSP 是 Application 層級的 Protocol，
底下要用什麼 Transport 層的 Protocol 來傳輸都可以（例如 TCP、UDP、multicast UDP），
而且 RTSP session 不能綁定到一個 Transport 層的 Protocol 上，
也就是說客戶端在同一個 RTSP session 下可能會開啟、關閉多個 Transport 連線。


* RTSP server 需要維護狀態
* RTSP server 和 client 都可以發起 requests


method：

* OPTIONS
* DESCRIBE
* ANNOUNCE
* SETUP
* PLAY
* PAUSE
* TEARDOWN
* GET_PARAMETER
* SET_PARAMETER
* REDIRECT
* RECORD


RTSP 只是控制用的 Protocol，


::

    +--------+      DESCRIBE       +--------+
    |        |-------------------->|        |
    |        |<--------------------|        |
    |        |                     |        |
    |        |      SETUP          |        |
    |        |-------------------->|        |
    |        |<--------------------|        |
    |        |                     |        |
    |        |      PLAY           |        |
    |        |-------------------->|        |
    |        |<--------------------|        |
    | Client |                     | Server |
    |        |   RTP audo/video    |        |
    |        |<--------------------|        |
    |        |                     |        |
    |        |      PAUSE          |        |
    |        |-------------------->|        |
    |        |<--------------------|        |
    |        |                     |        |
    |        |      TEARDOWN       |        |
    |        |-------------------->|        |
    |        |<--------------------|        |
    |        |                     |        |
    +--------+                     +--------+



RTSP 2.0 (RFC 7826) (2016)
========================================



RTP
========================================

基於 UDP 上的 Protocol，
用來傳送影音。



LIVE555
========================================

LIVE555 Media Server
------------------------------

openRTSP
------------------------------

RTSP client


LIVE555 Proxy Server
------------------------------



GStreamer
========================================

gst-launch-1.0 使用 ``!`` 作為 pipeline 的分隔符號


範例：

.. code-block:: sh

    $ gst-launch-1.0 fakesrc ! fakesink     # use ^C to stop
    Setting pipeline to PAUSED ...
    Pipeline is PREROLLING ...
    Pipeline is PREROLLED ...
    Setting pipeline to PLAYING ...
    New clock: GstSystemClock
    ^Chandling interrupt.
    Interrupt: Stopping pipeline ...
    Execution ended after 0:00:00.665138216
    Setting pipeline to PAUSED ...
    Setting pipeline to READY ...
    Setting pipeline to NULL ...
    Freeing pipeline ...

.. code-block:: sh

    $ gst-launch-1.0 videotestsrc ! autovideosink

.. code-block:: sh

    $ gst-launch-1.0 v4l2src ! xvimagesink

.. code-block:: sh

    $ gst-inspect-1.0


播放：

.. code-block:: sh

    # 如果碰到缺 decoder 的話，安裝 gst-libav 來接上 ffmpeg
    $ gst-launch-1.0 playbin uri=file:///test.mp4
    $ gst-launch-1.0 playbin uri=rtsp://192.168.0.100:8554/mpeg2TransportStreamFromUDPSourceTest



GStreamer RTSP Client
------------------------------

gst-plugins-good 內的 ``rtspsrc``


GStreamer RTSP Server
------------------------------

`gst-rtsp-server <https://github.com/GStreamer/gst-rtsp-server>`_
是額外的 library（不是 GStreamer plugin），
可以用來實做 RTSP server。


Python Binding
------------------------------

PyGObject (pygi)

.. code-block:: sh

  $ sudo pacman -S python-gobject



FFmpeg
========================================

FFmpeg 內建的只是 RTSP 的 muxer/demuxer，
並沒有 RTSP server，
所以如果要做 streaming 的話需要額外的 RTSP server，
FFmpeg 可以透過 ``RTSP ANNOUNCE`` 把影像打到 RTSP server 再 streaming 給其他人。

.. code-block:: sh

    $ TODO


RTSP streaming with camera:

.. code-block:: sh

    $ TODO


用 ffplay 播 RTSP 來的串流影像:

.. code-block:: sh

    $ ffplay -threads 1 rtsp://192.168.0.100:8554/oggFileTest


用 ffmpeg 推送 RTMP 串流影像：

.. code-block:: sh

    $ ffmpeg -re -i myfile -f flv rtmp://myserver/live/mystream



VLC
========================================

Play:

.. code-block:: python

    player=vlc.MediaPlayer('rtsp://:8554/output.h264')
    player.play()


Snapshot:

.. code-block:: python

    while True:
        time.sleep(1)
        player.video_take_snapshot(0, '.snapshot.tmp.png', 0, 0)


VLC + Computer Vision:

.. code-block:: python

    TODO



RTSP + UDP Hole Punching
========================================



Latency
========================================



tcpdump
========================================



測試用 RTSP Client
========================================

.. code-block:: sh

    $ gst-launch-1.0 playbin uri=rtsp://192.168.0.100:8554/test.ogg

    # Establish a connection to an RTSP server and send the raw RTP packets to a fakesink
    $ gst-launch-1.0 rtspsrc location=rtsp://192.168.0.100:8554/test.ogg ! fakesink

    # 只播影像，不處理聲音
    $ gst-launch-1.0 rtspsrc location=rtsp://192.168.0.100:8554/test.ogg ! decodebin ! autovideosink


.. code-block:: sh

    $ vlc rtsp://192.168.0.100:8554/test.ogg


.. code-block:: sh

    $ ffplay -threads 1 rtsp://192.168.0.100:8554/test.ogg


.. code-block:: sh

    $ mplayer rtsp://192.168.0.100:8554/test.ogg


.. code-block:: sh

    # LIVE555
    # 會吐出溝通過程，並把串流影音儲存成檔案
    $ ./openRTSP rtsp://192.168.0.100:8554/test.ogg



測試用 RTSP Server
========================================

.. code-block:: sh

    # LIVE555
    $ ./live555MediaServer
    LIVE555 Media Server
            version 0.89 (LIVE555 Streaming Media library version 2017.01.26).
    Play streams from this server using the URL
            rtsp://192.168.0.100:8554/<filename>
    where <filename> is a file present in the current directory.
    Each file's type is inferred from its name suffix:
            ".264" => a H.264 Video Elementary Stream file
            ".265" => a H.265 Video Elementary Stream file
            ".aac" => an AAC Audio (ADTS format) file
            ".ac3" => an AC-3 Audio file
            ".amr" => an AMR Audio file
            ".dv" => a DV Video file
            ".m4e" => a MPEG-4 Video Elementary Stream file
            ".mkv" => a Matroska audio+video+(optional)subtitles file
            ".mp3" => a MPEG-1 or 2 Audio file
            ".mpg" => a MPEG-1 or 2 Program Stream (audio+video) file
            ".ogg" or ".ogv" or ".opus" => an Ogg audio and/or video file
            ".ts" => a MPEG Transport Stream file
                    (a ".tsx" index file - if present - provides server 'trick play' support)
            ".vob" => a VOB (MPEG-2 video with AC-3 audio) file
            ".wav" => a WAV Audio file
            ".webm" => a WebM audio(Vorbis)+video(VP8) file
    See http://www.live555.com/mediaServer/ for additional documentation.
    (We use port 8000 for optional RTSP-over-HTTP tunneling, or for HTTP live streaming (for indexed Transport Stream files only).)




參考
========================================

* `RFC 2326 - Real Time Streaming Protocol (RTSP) <https://tools.ietf.org/html/rfc2326>`_
* `RFC 7826 - Real-Time Streaming Protocol Version 2.0 <https://tools.ietf.org/html/rfc7826>`_
* `Wikipedia - Real Time Streaming Protocol <https://en.wikipedia.org/wiki/Real_Time_Streaming_Protocol>`_
* `Wikipedia - Real-time Transport Protocol <https://en.wikipedia.org/wiki/Real-time_Transport_Protocol>`_
* `Wikipedia - LIVE555 <https://en.wikipedia.org/wiki/LIVE555>`_
* `GStreamer - RTP and RTSP support <https://gstreamer.freedesktop.org/documentation/rtp.html>`_
* `GStreamer - rtspsrc <https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-good-plugins/html/gst-plugins-good-plugins-rtspsrc.html>`_
* `GStreamer - Porting 0.10 applications to 1.0 <https://gstreamer.freedesktop.org/documentation/application-development/appendix/porting-1.0.html>`_
* `GStreamer Python Binding <https://cgit.freedesktop.org/gstreamer/gst-python>`_
* `FFmpeg - rtsp <https://www.ffmpeg.org/ffmpeg-protocols.html#rtsp>`_
