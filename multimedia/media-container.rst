========================================
Media Container
========================================


.. contents:: 目錄


簡表
========================================

* Audio
    - Lossy Compression
        + MP3
        + WMA
        + Vorbis
        + Opus
        + AAC
        + AC-3
        + DTS
    - No Compression
        + PCM
        + LPCM
    - Lossless Compression
        + FLAC
        + ALAC
        + MLP/Dolby TrueHD
        + DTS-HD

* Video
    - MPEG-1
    - MPEG-2
    - MPEG-4 (A)SP
    - H.264/MPEG-4 AVC
    - H.265/HEVC
    - VC-1/WMV
    - Real Video
    - Theora
    - Microsoft MPEG4 V2
    - VP8
    - VP9
    - MVC
    - AV1

* Subtitle
    - MicroDVD
    - MPEG-4 Timed Text
    - MPSub
    - SAMI
    - SubRip
    - SSA (SubStation Alpha)
    - SubViewer
    - Universal Subtitle Format
    - VobSub
    - XSUB



介紹
========================================

* AVI
* Matroska
* MP4
* MXF
* Ogg
* QuickTime



RTP
========================================



AVI
========================================



WebM
========================================

Matroska 的子集合，
保證影像一定使用 VP8 或 VP9，
保證聲音一定使用 Vorbis 或 Opus。



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



Matroska
========================================

* `FOSDEM 2018 - Matroska Low-Latency streaming - Why Matroska is (always) Better <https://fosdem.org/2018/schedule/event/om_matroska/>`_
* `Matroska Streaming <https://matroska.org/technical/streaming/index.html<Paste>`_
* `Wikipedia - Matroska <https://en.wikipedia.org/wiki/Matroska>`_
* `101 things you never knew you could do with Matroska <http://mod16.org/hurfdurf/?p=8>`_
* `Rust Matroska muxer/demux <https://github.com/rust-av/matroska>`_
* EBML (Extensible Binary Meta Language)
    - `The EBML specification <https://github.com/Matroska-Org/ebml-specification>`_
    - `IETF Datatracker - EBML <https://datatracker.ietf.org/doc/html/draft-ietf-cellar-ebml-04>`_
    - binary equivalent to XML
* Matroska Specification
    - `Matroska Specification <https://github.com/Matroska-Org/matroska-specification>`_
    - `IETF Datatracker - Matroska <https://datatracker.ietf.org/doc/draft-lhomme-cellar-matroska/>`_



參考
========================================

* `Wikipedia - Digital container format <https://en.wikipedia.org/wiki/Digital_container_format>`_
* `Wikipedia - Comparison of video container formats <https://en.wikipedia.org/wiki/Comparison_of_video_container_formats>`_
