========================================
FFmpeg
========================================


.. contents:: 目錄


Introduction
========================================

FFmpeg 最早是在 2000 年由 Fabrice Bellard 撰寫的多媒體資料處理的 library，
在 2004 年由 Michael Niedermayer 接手管理，
後來 Michael Niedermayer 於 2015 年 7 月 31 日宣佈辭去領導人的位置。



分裂 - Libav
========================================

Libav 是 FFmpeg 的分支，
一群 FFmpeg 開發者因為在專案維護、發展上跟 FFmpeg 領導人衝突，
在 mailing list 上爭吵了很久，
最後在 2011 年 3 月 13 日宣佈正式分支出去
(後來當時 FFmpeg 的領導人 Michael Niedermayer 依然會把 Libav 的 commit 都 merge 回 FFmpeg)。



編譯
========================================

.. code-block:: sh

    git clone -b release/3.4 https://github.com/FFmpeg/FFmpeg
    cd FFmpeg/
    # 靜態編譯，產生靜態連結的 ffmpeg
    ./configure \
        --disable-debug \
        --enable-stripping \
        --disable-shared \
        --extra-ldexeflags="-static" \
        --pkg-config-flags="--static" \
        --disable-encoders \
        --disable-filters \
        --disable-decoders \
        --disable-muxers \
        --disable-demuxers \
        --disable-bsfs \
        --disable-parsers \
        --disable-ffplay \
        --disable-ffserver \
        --disable-ffprobe \
        --enable-encoder=libx264 \
        --enable-encoder=libx264rgb \
        --enable-encoder=aac \
        --enable-decoder=h264 \
        --enable-decoder=aac \
        --enable-muxer=mp4 \
        --enable-muxer=h264 \
        --enable-demuxer=h264 \
        --enable-parser=h264
    make -j



使用範例
========================================


.. code-block:: sh

    $ ffmpeg -i input.mp4 -strict experimental -vcodec libx264 output.mp4


使用 VAAPI：

.. code-block:: sh

    # 檢查 VAAPI H264 decode 支援
    $ vainfo | rg H264 | rg VAEntrypointVLD
    # 檢查 VAAPI H264 encode 支援
    $ vainfo | rg H264 | rg VAEntrypointEncSlice

.. code-block:: sh

    $ ffmpeg -vaapi_device /dev/dri/renderD128 \
        -i input.flv -vf 'format=nv12,hwupload' \
        -c:v h264_vaapi out.mp4

.. code-block:: sh

    $ ffmpeg -vaapi_device /dev/dri/renderD128 \
        -i input.flv -vf 'format=nv12,hwupload' \
        -c:a copy -c:v h264_vaapi \
        -profile:v 100 -level 51 -bf 10 -crf 28 \
        out.mp4



參考
========================================

* `Wikipedia - FFmpeg <https://en.wikipedia.org/wiki/FFmpeg>`_
* `Wikipedia - Libav <https://en.wikipedia.org/wiki/Libav>`_
* `Arch Wiki - FFmpeg <https://wiki.archlinux.org/index.php/FFmpeg>`_
* [GitHub] `FFmpeg <https://github.com/FFmpeg/FFmpeg>`_
* `[2015][FFmpeg-devel] FFmpegs future and resigning as leader <http://ffmpeg.org/pipermail/ffmpeg-devel/2015-July/176489.html>`_
* `FFmpeg - H.264 Video Encoding Guide <https://trac.ffmpeg.org/wiki/Encode/H.264>`_
* `FFmpeg - VAAPI <https://trac.ffmpeg.org/wiki/Hardware/VAAPI>`_
* `libav - VAAPI <https://wiki.libav.org/Hardware/vaapi>`_

* `CRF Guide (Constant Rate Factor in x264 and x265) <http://slhck.info/video/2017/02/24/crf-guide.html>`_
* `Understanding Rate Control Modes (x264, x265, vpx) <http://slhck.info/video/2017/03/01/rate-control.html>`_
* `FFmpeg VBR Settings <http://slhck.info/video/2017/02/24/vbr-settings.html>`_
* `FFmpeg and x264 Encoding Guide <http://www.mpabo.com/2014/12/14/ffmpeg-and-x264-encoding-guide/>`_
