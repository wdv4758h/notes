========================================
Rust & Android
========================================


.. contents:: 目錄


環境設定
========================================

.. code-block:: sh

    # 安裝 aarch64-linux-android 支援
    rustup target add aarch64-linux-android

    # 安裝 Android NDK
    wget https://dl.google.com/android/repository/android-ndk-r17b-linux-x86_64.zip
    unzip android-ndk-r17b-linux-x86_64.zip

    # 設定 standalone toolchain
    ./android-ndk-r17b/build/tools/make-standalone-toolchain.sh \
        --arch=arm64 \
        --platform=android-28 \
        --toolchain=aarch64-linux-android-4.9 \
        --install-dir=android-28-toolchain

    # 用 rustc 編譯簡單的 Rust 程式測試
    rustc --target aarch64-linux-android \
      -C linker="android-28-toolchain/bin/clang" \
      test.rs

    # 用 cargo 編譯專案測試
    cargo rustc --target aarch64-linux-android -- \
      -C linker="android-28-toolchain/bin/clang"

    # 用 cargo 編譯專案釋出
    cargo rustc --release --target aarch64-linux-android -- \
      -C linker="android-28-toolchain/bin/clang" \

    # 更多優化
    cargo rustc --release --target aarch64-linux-android -- \
      -C linker="android-28-toolchain/bin/clang" \
      -C link-arg="-s" \
      -C lto


專案實測後正常：

* ripgrep
* fd



建立 C 程式碼的 Android cross compile
========================================

Cargo.toml:

.. code-block:: toml

    [package]
    name = "example"
    version = "0.1.0"

    [dependencies]

    [build-dependencies]
    cc = { version = "1.0", features = ["parallel"] }


build.rs:

.. code-block:: rust

    extern crate cc;

    fn main() {
        cc::Build::new()
            .file("foo.c")
            .compile("libfoo.a");
    }


foo.c:

.. code-block:: c

    #include <stdio.h>

    void func() {
        printf("hello in C\n");
    }


src/main.rs:

.. code-block:: rust

    extern {
        fn func();
    }

    fn main() {
        unsafe { func() };
    }


編譯：

.. code-block:: sh

    export AR="/home/dv/PKGBUILDs/android/android-28-toolchain/bin/aarch64-linux-android-ar"
    env cargo rustc --release --target aarch64-linux-android -- \
      -C linker="android-28-toolchain/bin/clang" \
      -C link-arg="-s" \
      -C lto
