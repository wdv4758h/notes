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


列出所有支援
------------------------------

.. code-block:: sh

    $ ffmpeg -formats
    $ ffmpeg -encoders
    $ ffmpeg -decoders
    $ ffmpeg -demuxers
    $ ffmpeg -muxers
    $ ffmpeg -devices


轉檔
------------------------------

.. code-block:: sh

    ffmpeg -i input.mkv out.mp4


擷取出指定數量的 Frames
------------------------------

.. code-block:: sh

    # 1000 frames
    ffmpeg -i input.mkv -vframes 1000 -c copy out.mkv


指定 Codec
------------------------------

.. code-block:: sh

    $ ffmpeg -i input.mp4 -strict experimental -vcodec libx264 output.mp4


用 VAAPI
------------------------------

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



FFmpeg 4.0
========================================

移除 ``ffserver``
------------------------------

因為程式碼在重構、清理，
``ffserver`` 使用太多內部的 API 導致重構障礙，
以及 ``ffserver`` 本身設計造成大大小小的使用困難，
目前正在使用新的 API 重新設計看如何補上 ``ffserver`` 的功能。

::

    After thorough deliberation, we're announcing that we're about to drop the ffserver program from the project starting with the next release. ffserver has been a problematic program to maintain due to its use of internal APIs, which complicated the recent cleanups to the libavformat library, and block further cleanups and improvements which are desired by API users and will be easier to maintain. Furthermore the program has been hard for users to deploy and run due to reliability issues, lack of knowledgable people to help and confusing configuration file syntax. Current users and members of the community are invited to write a replacement program to fill the same niche that ffserver did using the new APIs and to contact us so we may point users to test and contribute to its development.



參考
========================================

* `Wikipedia - FFmpeg <https://en.wikipedia.org/wiki/FFmpeg>`_
* `Wikipedia - Libav <https://en.wikipedia.org/wiki/Libav>`_
* `Arch Wiki - FFmpeg <https://wiki.archlinux.org/index.php/FFmpeg>`_
* `FFmpeg Static Builds <https://johnvansickle.com/ffmpeg/>`_
* [GitHub] `FFmpeg <https://github.com/FFmpeg/FFmpeg>`_
* `[2015][FFmpeg-devel] FFmpegs future and resigning as leader <http://ffmpeg.org/pipermail/ffmpeg-devel/2015-July/176489.html>`_
* `FFmpeg - H.264 Video Encoding Guide <https://trac.ffmpeg.org/wiki/Encode/H.264>`_
* `FFmpeg - VAAPI <https://trac.ffmpeg.org/wiki/Hardware/VAAPI>`_
* `libav - VAAPI <https://wiki.libav.org/Hardware/vaapi>`_

* `CRF Guide (Constant Rate Factor in x264 and x265) <http://slhck.info/video/2017/02/24/crf-guide.html>`_
* `Understanding Rate Control Modes (x264, x265, vpx) <http://slhck.info/video/2017/03/01/rate-control.html>`_
* `FFmpeg VBR Settings <http://slhck.info/video/2017/02/24/vbr-settings.html>`_
* `FFmpeg and x264 Encoding Guide <http://www.mpabo.com/2014/12/14/ffmpeg-and-x264-encoding-guide/>`_
