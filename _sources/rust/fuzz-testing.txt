========================================
Fuzz Testing
========================================


.. contents:: 目錄


Cargo Fuzz
========================================

`Cargo Fuzz <https://github.com/rust-fuzz/cargo-fuzz>`_ 是 LLVM libFuzzer 的包裝。


安裝：

.. code-block:: sh

    $ cargo install cargo-fuzz


使用：

.. code-block:: sh

    # 初始化會建立 fuzz/ 資料夾，
    # 裡面是一個 Fuzz Testing 用的小專案，
    # 其中的 fuzz_target! 會不斷地被呼叫，
    # 裡面會傳入各種資料給 "data" 變數
    $ cargo fuzz init

    # 觀察產生出來的檔案
    $ tree fuzz/
    fuzz/
    ├── Cargo.toml
    └── fuzzers
        └── fuzzer_script_1.rs

    1 directory, 2 files

    # 新增測試 Script
    $ cargo fuzz add another_script

    $ tree fuzz/
    fuzz/
    ├── artifacts
    │   └── another_script
    ├── Cargo.toml
    ├── corpus
    │   └── another_script
    └── fuzzers
        ├── another_script.rs
        └── fuzzer_script_1.rs

    5 directories, 3 files

    # 執行測試
    $ cargo fuzz run fuzzer_script_1

    # 重新執行某個 Input
    $ cargo fuzz run fuzzer_script_1 fuzz/artifacts/fuzzer_script_1/<file mentioned in crash output>



AFL (American Fuzzy Loop)
========================================

AFL 是一套 coverage-guided fuzzing 的測試工具，
Rust 這邊有一套包裝叫 `afl.rs <https://github.com/rust-fuzz/afl.rs>`_ ，
``afl.rs`` 跟 ``cargo-fuzz`` 相比之下環境建立麻煩許多。



從原始碼編譯：

.. code-block:: sh

    $ git clone https://github.com/rust-fuzz/afl.rs
    $ cd afl.rs/afl/
    $ cargo build --release
    $ cargo install --path .

    # 嘗試呼叫
    $ cargo afl-fuzz


使用：

* 把 ``afl`` 和 ``afl-plugin`` 加入 Dependencies
* 在 ``lib.rs`` 內加入 ``#![feature(plugin)]`` 和 ``#![plugin(afl_plugin)]``
* 在 ``main.rs`` 內使用 ``afl`` 內的函式（例如 ``handle_string`` 或 ``handle_bytes`` ）並傳入要執行的 Lambda 函式



參考
========================================

Repos
------------------------------

* `libFuzzer <https://github.com/llvm-mirror/llvm/tree/master/lib/Fuzzer>`_
* `rust-fuzz <https://github.com/rust-fuzz>`_
* `afl.rs <https://github.com/rust-fuzz/afl.rs>`_ ，
* `OSS-Fuzz <https://github.com/google/oss-fuzz>`_
* `syzkaller - linux syscall fuzzer <https://github.com/google/syzkaller>`_


案例
------------------------------

* cargo-fuzz
    - `Fuzzing is magic - Or how I found a panic in Rust's regex library <https://www.nibor.org/blog/fuzzing-is-magic---or-how-i-found-a-panic-in-rusts-regex-library/>`_
    - `Cap'n Proto for Rust - cargo-fuzz findings <https://dwrensha.github.io/capnproto-rust/2017/02/27/cargo-fuzz.html>`_

* syzkaller
    - `Linux kernel: CVE-2017-6074: DCCP double-free vulnerability (local root) <http://seclists.org/oss-sec/2017/q1/471>`_
