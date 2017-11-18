========================================
FFmpeg
========================================


.. contents:: 目錄


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
