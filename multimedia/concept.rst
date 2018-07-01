========================================
基本概念
========================================


.. contents:: 目錄


介紹
========================================

Video
------------------------------

Audio
------------------------------

Codec
------------------------------

Container
------------------------------



FFmpeg
========================================



Common Video Operations
========================================

Transcoding
------------------------------

Transcoding 指的是把 Audio/Video 從一個 **codec** 轉到另一個 codec 的過程。


例如：

.. code-block:: sh

    ffmpeg -i bunny_1080p_60fps.mp4 -c:v libx265  bunny_1080p_60fps_h265.mp4


Transmuxing
------------------------------

Transmuxing 指的是從一個 **container** 轉到另一個 container 的過程。


例如：

.. code-block:: sh

    ffmpeg -i bunny_1080p_60fps.mp4 -c copy bunny_1080p_60fps.webm


Transrating
------------------------------

Transrating 指的是從一個 **bit rate** 轉到另一個 bit rate 的過程，
常常會跟 Transsizing 一起使用。


例如：

.. code-block:: sh

    ffmpeg -i bunny_1080p_60fps.mp4 \
      -minrate 964K -maxrate 3856K -bufsize 2000K \
      bunny_1080p_60fps_tranrating_964_3856.mp4


Transsizing
------------------------------

Transsizing 指的是從一個 **resolution** 轉到另一個 resolution 的過程，
也就是改變解析度，
常常會跟 Transrating 一起使用。


例如：

.. code-block:: sh

    ffmpeg -i bunny_1080p_60fps.mp4 \
      -vf scale=480:-1 \
      bunny_1080p_60fps_transsizing_480.mp4


Adaptive Streaming
------------------------------

Adaptive Streaming 指的是指製造出多種 resolution、bit rates，
並且把多媒體分割成多個小塊資料，
以 HTTP 的形式傳送。
藉此可以提供有彈性的多媒體來源，
同時支援低階產品和高階產品，
容易 scale 和 deploy，
但是會增加一點 latency。


例如：

.. code-block:: sh

    ##############################
    # adaptive WebM using DASH
    ##############################

    # video streams
    $ ffmpeg -i bunny_1080p_60fps.mp4 \
        -c:v libvpx-vp9 -s 160x90 -b:v 250k \
        -keyint_min 150 -g 150 -an -f webm -dash 1 \
        video_160x90_250k.webm

    $ ffmpeg -i bunny_1080p_60fps.mp4 \
        -c:v libvpx-vp9 -s 320x180 -b:v 500k \
        -keyint_min 150 -g 150 -an -f webm -dash 1 \
        video_320x180_500k.webm

    $ ffmpeg -i bunny_1080p_60fps.mp4 \
        -c:v libvpx-vp9 -s 640x360 -b:v 750k \
        -keyint_min 150 -g 150 -an -f webm -dash 1 \
        video_640x360_750k.webm

    $ ffmpeg -i bunny_1080p_60fps.mp4 \
        -c:v libvpx-vp9 -s 640x360 -b:v 1000k \
        -keyint_min 150 -g 150 -an -f webm -dash 1 \
        video_640x360_1000k.webm

    $ ffmpeg -i bunny_1080p_60fps.mp4 \
        -c:v libvpx-vp9 -s 1280x720 -b:v 1500k \
        -keyint_min 150 -g 150 -an -f webm -dash 1 \
        video_1280x720_1500k.webm

    # audio streams
    $ ffmpeg -i bunny_1080p_60fps.mp4 \
        -c:a libvorbis -b:a 128k -vn -f webm -dash 1 \
        audio_128k.webm

    # the DASH manifest
    $ ffmpeg \
        -f webm_dash_manifest -i video_160x90_250k.webm \
        -f webm_dash_manifest -i video_320x180_500k.webm \
        -f webm_dash_manifest -i video_640x360_750k.webm \
        -f webm_dash_manifest -i video_640x360_1000k.webm \
        -f webm_dash_manifest -i video_1280x720_500k.webm \
        -f webm_dash_manifest -i audio_128k.webm \
        -c copy -map 0 -map 1 -map 2 -map 3 -map 4 -map 5 \
        -f webm_dash_manifest \
        -adaptation_sets "id=0,streams=0,1,2,3,4 id=1,streams=5" \
        manifest.mpd



參考
========================================

* [GitHub] `Learn FFmpeg libav the Hard Way <https://github.com/leandromoreira/ffmpeg-libav-tutorial>`_
