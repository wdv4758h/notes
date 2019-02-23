========================================
Rust Cross Compilation
========================================


* `LLVM Triple 認識 <https://llvm.org/doxygen/classllvm_1_1Triple.html>`_
    - 官方 Rust 實做是基於 LLVM，所以在選擇要編譯的平台時會需要指定相關的名稱
    - 規則： ``<arch>[<sub_arch>]-<vendor>-<os>-<env>[<object_format>]``
    - 範例：
        + ``x86_64-unknown-linux-gnu``
        + ``thumbv7neon-linux-androideabi``
        + ``thumbv7neon-unknown-linux-gnueabihf``
            * arch = thumb
            * sub_arch = v7neon
            * vendor = unknown
            * os = linux
            * env = gnu
            * object_format = eabihf

* 基本 Cross Compilation 工具準備
    - ``rustup``
    - `cross <https://github.com/rust-embedded/cross>`_

* 特定平台
    - x86_64
    - ARM
    - RISC-V
    - WebAssembly

* 進階
    - 如何為 Rust 新增 Cross Compilation 平台支援
    - no_std

* `Rust Embedded <https://github.com/rust-embedded>`_
