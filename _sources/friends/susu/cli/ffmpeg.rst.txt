ffmpeg is a video and audio converter, with encoder/decoder/muxer/demuxer ... in it.

::
    :alt: Demo diagram

     _______              ______________
    |       |            |              |
    | input |  demuxer   | encoded data |   decoder
    | file  | ---------> | packets      | -----+
    |_______|            |______________|      |
                                               v
                                           _________
                                          |         |
                                          | decoded |
                                          | frames  |
                                          |_________|
     ________             ______________       |
    |        |           |              |      |
    | output | <-------- | encoded data | <----+
    | file   |   muxer   | packets      |   encoder
    |________|           |______________|

ffmpeg basic command

::
    ffmpeg [global option] {[input_file_options] -i input_file} {[output_file_option] output_file}

ffmpeg 會自動偵測 input_file 的 format (估計跟 file 的原理一樣), 以及檢查 output_file 的附檔名,
決定 converter 的 input 跟 output format, 可以用 ``-f fmt (input/output)`` 強行指定.

example usage::
    ffmpeg -i input.mp4 -codec:a libmp3lame -qscale:a 2 input.mp3

- global option
- input_file_options
- output_file_option
  - codec:a libmp3lame
  - qscale:a 2
- input format: ``file input.mp4``
- output format: mp3 (input.mp3 的副檔名)

其中 codec 代表 encoder/decoder(專有名詞), codec:a 代表 audio(音樂)的 encoder,
libmp3lame 是一套名為 lame 的 mp3 encoder, 因為 ffmpeg 本身不含 mp3 encoder, 所以透過 lame 來 encode mp3.

qscale 是使用 VBR encoding, 2 代表品質 (0 ~ 9, 越小越好), 詳見 ffmpeg MP3 encoding quide.


ffmpeg concat audio
-------------------
``ffmpeg -f concat -i <list_file> -c copy <output_file>``
list_file format::

    file '01.mp3'
    file '02.mp3'
    ...

https://trac.ffmpeg.org/wiki/Concatenate

reference
---------
ffmpeg user manual: http://ffmpeg.org/ffmpeg.html
ffmpeg MP3 encoding guide: https://trac.ffmpeg.org/wiki/Encode/MP3
ffmpeg windows build: http://ffmpeg.zeranoe.com/builds/

cut video: http://stackoverflow.com/questions/18444194/cutting-the-videos-based-on-start-and-end-time-using-ffmpeg

Issue
-----
- [14.04] Ubuntu use ffmpeg forked: libav(avconv)
- [14.04] Ubuntu's libmp3lame (mp3 encoder): libavcodec-extra-53

Other video tools
-----------------
1. openshot: video editor, GUI and video emulation interface.

