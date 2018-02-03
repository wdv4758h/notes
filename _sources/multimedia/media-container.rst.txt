========================================
Media Container
========================================


.. contents:: 目錄


RTP
========================================



AVI
========================================



WebM
========================================



WAV
========================================



QuickTime Movie
========================================



MP4 (MPEG-4 Part 14)
========================================

Fast Start
------------------------------

把 header 放在檔案最前面，以便可以馬上播放，而不用整個檔案讀完。


FFmpeg：

.. code-block:: sh

    ffmpeg -i input.mp4 -vcodec copy -acodec copy -movflags +faststart output.mp4


GStreamer：

.. code-block:: sh

    ... ! mp4mux faststart=true ! ...



MPEG-TS
========================================

:Wikipedia: https://en.wikipedia.org/wiki/MPEG_transport_stream



Ogg
========================================



參考
========================================

* `Wikipedia - Digital container format <https://en.wikipedia.org/wiki/Digital_container_format>`_
* `Wikipedia - Comparison of video container formats <https://en.wikipedia.org/wiki/Comparison_of_video_container_formats>`_
