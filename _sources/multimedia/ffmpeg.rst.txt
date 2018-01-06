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


參考
========================================

* `Wikipedia - FFmpeg <https://en.wikipedia.org/wiki/FFmpeg>`_
* `Wikipedia - Libav <https://en.wikipedia.org/wiki/Libav>`_
* `Arch Wiki - FFmpeg <https://wiki.archlinux.org/index.php/FFmpeg>`_
* [GitHub] `FFmpeg <https://github.com/FFmpeg/FFmpeg>`_
* `[2015][FFmpeg-devel] FFmpegs future and resigning as leader <http://ffmpeg.org/pipermail/ffmpeg-devel/2015-July/176489.html>`_
