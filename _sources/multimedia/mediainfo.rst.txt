========================================
MediaInfo
========================================


.. contents:: 目錄


介紹
========================================

:Repo: https://github.com/MediaArea/MediaInfo


MediaInfo 是一個可以用來讀取多媒體檔案資訊的指令。



安裝與使用
========================================

安裝：

.. code-block:: sh

    sudo pacman -S mediainfo


使用：

.. code-block:: sh

    $ mediainfo test.mp4
    General
    Complete name                            : test.mp4
    Format                                   : MPEG-4
    Format profile                           : Base Media
    Codec ID                                 : isom (isom/iso2/avc1/mp41)
    File size                                : 7.46 MiB
    Duration                                 : 2 min 35 s
    Overall bit rate                         : 403 kb/s
    Writing application                      : Lavf57.83.100

    Video
    ID                                       : 1
    Format                                   : AVC
    Format/Info                              : Advanced Video Codec
    Format profile                           : High@L3.1
    Format settings                          : CABAC / 4 Ref Frames
    Format settings, CABAC                   : Yes
    Format settings, ReFrames                : 4 frames
    Codec ID                                 : avc1
    Codec ID/Info                            : Advanced Video Coding
    Duration                                 : 2 min 35 s
    Bit rate                                 : 266 kb/s
    Width                                    : 960 pixels
    Height                                   : 540 pixels
    Display aspect ratio                     : 16:9
    Frame rate mode                          : Constant
    Frame rate                               : 30.000 FPS
    Color space                              : YUV
    Chroma subsampling                       : 4:2:0
    Bit depth                                : 8 bits
    Scan type                                : Progressive
    Bits/(Pixel*Frame)                       : 0.017
    Stream size                              : 4.93 MiB (66%)
    Writing library                          : x264 core 152 r2854 e9a5903
    Encoding settings                        : cabac=1 / ref=1 / deblock=1:0:0 / analyse=0x3:0x113 / me=hex / subme=2 / psy=1 / psy_rd=1.00:0.00 / mixed_ref=0 / me_range=16 / chroma_me=1 / trellis=0 / 8x8dct=1 / cqm=0 / deadzone=21,11 / fast_pskip=1 / chroma_qp_offset=0 / threads=6 / lookahead_threads=2 / sliced_threads=0 / nr=0 / decimate=1 / interlaced=0 / bluray_compat=0 / constrained_intra=0 / bframes=3 / b_pyramid=2 / b_adapt=1 / b_bias=0 / direct=1 / weightb=1 / open_gop=0 / weightp=1 / keyint=250 / keyint_min=25 / scenecut=40 / intra_refresh=0 / rc_lookahead=10 / rc=crf / mbtree=1 / crf=19.0 / qcomp=0.60 / qpmin=0 / qpmax=69 / qpstep=4 / ip_ratio=1.40 / aq=1:1.00

    Audio
    ID                                       : 2
    Format                                   : AAC
    Format/Info                              : Advanced Audio Codec
    Format profile                           : LC
    Codec ID                                 : mp4a-40-2
    Duration                                 : 2 min 35 s
    Bit rate mode                            : Constant
    Bit rate                                 : 128 kb/s
    Channel(s)                               : 2 channels
    Channel positions                        : Front: L R
    Sampling rate                            : 44.1 kHz
    Frame rate                               : 43.066 FPS (1024 SPF)
    Compression mode                         : Lossy
    Stream size                              : 2.37 MiB (32%)
    Title                                    : simple_aac_recording
    Default                                  : Yes
    Alternate group                          : 1
