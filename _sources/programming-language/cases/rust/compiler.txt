========================================
Rust 編譯器
========================================


.. contents:: 目錄


編譯「編譯器」
========================================

.. code-block:: sh

    # 抓程式碼
    $ git clone https://github.com/rust-lang/rust/
    $ cd rust/

    # see "^opt" in configure
    #
    # compiler-docs     "build compiler documentation"
    # rustbuild         "use the rust and cargo based build system"
    # local-rust        "use an installed rustc rather than downloading a snapshot"
    # vendor            "enable usage of vendored Rust crates
    # clang             "prefer clang to gcc for building the runtime"
    #
    $ ./configure --enable-local-rust --enable-clang --enable-vendor --enable-rustbuild --enable-compiler-docs --enable-optimize

    # 編譯到 Stage 1：
    $ make rustc-stage1
    $ ./build/x86_64-unknown-linux-gnu/stage1/bin/rustc --version

    # 編譯到 Stage 2：
    $ make rustc-stage2
    $ ./build/x86_64-unknown-linux-gnu/stage2/bin/rustc --version

    # 產生文件：
    $ make doc
    $ cd ./build/x86_64-unknown-linux-gnu/doc/
    $ python -m http.server


* `Rust internal compiler documentation <https://manishearth.github.io/rust-internals-docs/rustc/>`_



平台 Porting 範例
========================================

* `IBM s390x <https://github.com/rust-lang/rust/pull/36369>`_
* `Haiku OS <https://github.com/rust-lang/rust/pull/36727>`_



Parser
========================================

Rust 有用 ANTLR 做 parser 驗證：

* https://github.com/rust-lang/rust/tree/master/src/grammar
* https://github.com/antlr
* https://github.com/rust-lang/rust/blob/master/src/doc/grammar.md



編譯器效能追蹤
========================================

* `rustc performance data <http://perf.rust-lang.org/>`_
* `Some benchmarks for testing rustc performance <https://github.com/rust-lang-nursery/rustc-benchmarks>`_



參考
========================================

* `Helping with the Rust Errors <http://www.jonathanturner.org/2016/08/helping-out-with-rust-errors.html>`_
* `Error code list which need to be updated to new format #35233 <https://github.com/rust-lang/rust/issues/35233>`_
* `Rust Internals - New error format <https://internals.rust-lang.org/t/new-error-format/3438/>`_
