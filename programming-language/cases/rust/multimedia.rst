========================================
多媒體 (Multimedia)
========================================


.. contents:: 目錄


介紹
========================================

Rust 目前在這塊資源還不多，
但是可以觀察以下數個組織的後續發展：

* `rust-av <https://github.com/rust-av>`_
* `RustAudio <https://github.com/RustAudio>`_


分類：

* Video
    - Theora
    - VP8
    - VP9
    - H264
    - H265
    - `AV1 <https://github.com/xiph/rav1e>`_
* Audio
    - PCM
    - MP3
    - AAC
    - Speex
    - `Vorbis <https://github.com/RustAudio/lewton>`_
    - Opus
    - `FLAC <https://github.com/ruuda/claxon>`_
* Container
    - `WAV <https://github.com/ruuda/hound>`_
    - MPEG4
    - Matroska
    - WebM
    - MPEG-TS
    - `Ogg <https://github.com/RustAudio/ogg>`_


可能作法：

* 接 FFmpeg/Liba
* `接 GStreamer <https://github.com/sdroege/gstreamer-rs>`_
* 重新用 Rust 實做


期望：

* 有 trait 可以把各種 Video/Audio decode/encode 抽象化
    - 例如 `audrey <https://github.com/RustAudio/audrey>`_
* 有 trait 可以把各種 Container 抽象化
