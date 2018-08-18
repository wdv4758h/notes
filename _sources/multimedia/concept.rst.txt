========================================
基本概念
========================================


.. contents:: 目錄


介紹
========================================

Video
------------------------------

Video，影像，也就是眼睛所看到的東西，
如果把多張連貫的圖片以一定的頻率更換，
人類的眼睛就會有物體移動的錯覺，
也就是說「Video 就是把圖片（Frame）以某種頻率（Rate）在替換」。


Audio
------------------------------

Audio，聲音，也就是耳朵所聽到的，
其實也就是經由空氣或其他物質傳送的振動（波）。
在數位音訊系統中，麥克風會把聲音轉成類比的電子訊號，
接著 ADC（Analog to Digital）把類比轉成數位訊號，
此類比轉數位的過程通常使用 PCM（Pulse-Code Modulation）。


Codec
------------------------------

Codec 負責的是把未經壓縮過的原始數位資料壓縮成相對較小的形式，
或者是反方向地解壓縮回來，
實做可能是電子電路或是軟體。

既然是壓縮那就會討論到資訊理論中的 Entropy，
也就是要衡量如何在比較小的資料量中承載同樣的資訊量。
根據不同的壓縮演算法、優化方向，
也就會發展出不同的 Codec，
又或者是同個 Codec 裡的不同 Profile。


Container
------------------------------

Container 負責的是把多個 Video 或 Audio 整合在一起，
並且提供同步（Synchronization）或其他 metadata 資訊。



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
