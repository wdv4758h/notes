========================================
Rust 相關文章
========================================


*這邊還需要大幅整理*

----


.. contents:: 目錄


TL;DR
========================================

* CLI args parsing  ➡ ``clap``
* Serialization     ➡ ``serde`` + XXX format
* Asynchronous      ➡ ``tokio``
* Regex             ➡ ``regex``
* Logging           ➡ ``log`` + XXX
* Config            ➡ ``config``
* HTTP              ➡ ``hyper``
* Python <-> Rust   ➡ ``pyo3``
* Bits Tuning       ➡ ``packed_struct``
* Template Engine   ➡ ``askama``
* Builder Pattern   ➡ ``derive_builder``
* Static Variable   ➡ ``lazy_static``
* Random            ➡ ``rand``
* Faker             ➡ ``fake``
* Syntex Highlight  ➡ ``syntect``
* Temporary Folder  ➡ ``tempdir``
* String Similarity ➡ ``strsim``
* mmap file I/O     ➡ ``memmap``
* N dimention array ➡ ``ndarray``
* Vulkan            ➡ ``vulkano``
* Database          ➡ ``r2d2`` + ``diesel``
* Float to string   ➡ ``ryu``
* Date and Time     ➡ ``chrono``
* 範例 ➡ `Rust Cookbook <https://rust-lang-nursery.github.io/rust-cookbook/>`_



語言核心功能
========================================

* `Pattern Matching <lang-design/pattern-matching.rst>`_
* `錯誤處理 (Error Handling) <lang-design/error-handling.rst>`_
* `Iterator <lang-design/iterator.rst>`_
* `Tagged Unions (Sum Type) <lang-design/tagged-unions.rst>`_
* `Macro <lang-design/macro.rst>`_
* `Unsafe <lang-design/unsafe.rst>`_



生態圈
========================================

* `Regular Expression <usage/regex.rst>`_
    - regex
    - fancy-regex
* `Serialization <usage/serialization.rst>`_
    - serde
* `Logging <usage/logging.rst>`_
    - log
* `Security <usage/security.rst>`_
    - ring
    - webpki
    - rustls
    - quinn
* `Asynchronous I/O  <usage/asynchronous.rst>`_
    - futures
    - mio
    - tokio
    - actix
* `Error Handling <lang-design/error-handling.rst>`_
    - Option/Result
    - Box<Error>
    - failure
* `Multimedia <usage/multimedia.rst>`_
* `資料庫 (Database) <usage/database.rst>`_



Unstable
========================================

* `CTFE (Compile Time Function Execution) <lang-design/compile-time-function-execution.rst>`_



Working Groups
========================================

* `CLI working group <https://github.com/rust-lang-nursery/cli-wg>`_
* `Rust + WebAssembly <https://github.com/rustwasm>`_
* `Runtimes working group <https://github.com/rust-hosted-langs/runtimes-WG/>`_
* `Embedded devices Working Group <https://github.com/rust-lang-nursery/embedded-wg>`_
* `Rust Verification working group <https://github.com/rust-lang-nursery/wg-verification>`_
* `Portability Working Group <https://github.com/rust-lang-nursery/portability-wg>`_
* `Ecosystem Working Group <https://github.com/rust-lang-nursery/ecosystem-wg>`_
* `Networking Working Group <https://github.com/rust-lang-nursery/net-wg>`_
* `codegen working group <https://github.com/nox/wg-codegen>`_



練習
========================================

* NTP client



內部實做
========================================

* `RFCs <rfcs/>`_
* `編譯器 (Compiler) <rust-compiler/>`_
* `MIR (Mid-level Intermediate Representation) <rust-compiler/mir.rst>`_
* `Standard Library 程式碼研讀 <std/>`_






列表
========================================

一般使用：

* `Testing <usage/testing.rst>`_
* `Fuzz Testing <usage/fuzz-testing.rst>`_
* `Benchmark <usage/benchmark.rst>`_
* `套件處理 - Cargo <official-tools/cargo.rst>`_
* `Linking <lang-design/linking.rst>`_
* `文件 (Documentation) <documentation/>`_
* `網路相關 (Network) <usage/network.rst>`_
* `開發相關工具 (Development Tools) <usage/development-tools.rst>`_
* `Graphic <usage/graphc.rst>`_
* `GUI <usage/gui.rst>`_
* `Syntax Highlighting <usage/syntax-highlighting.rst>`_
* `圖像處理 <usage/image-manipulation.rst>`_
* `機器學習 <usage/machine-learning.rst>`_
* `Microcontroller <usage/microcontroller.rst>`_


Edition：

* `Rust 2015 <edition/edition-2015.rst>`_
* `Rust 2018 <edition/edition-2018.rst>`_


其他：

* `文章閱讀 <learning-resource/articles.rst>`_
* `Tips <usage/tips.rst>`_
* `生態圈 <usage/ecosystem.rst>`_
* `Servo <usage/servo.rst>`_
* `runtime reflection - "Any" type trait <lang-design/any.rst>`_
* `Rust to asm.js <usage/asmjs.rst>`_
* `Misc <usage/misc.rst>`_
* `Videos <learning-resource/videos.rst>`_
* `FAQ <documentation/faq.rst>`_
* `Design Pattern <usage/design-pattern.rst>`_
* `相關書籍 <learning-resource/books.rst>`_
* `從 C 轉譯成 Rust <usage/c-to-rust.rst>`_
* `特性簡表 <usage/features-basic.rst>`_
* `撰寫 Kernel <usage/kernel.rst>`_
* `讓 Parity 可以在 FreeBSD 上編譯的紀錄 <usage/make-parity-work-on-freebsd.rst>`_
* `Monomorphization <usage/monomorphization.rst>`_
* `Object Safety <usage/object-safety.rst>`_
* `效能觀察 <usage/performance.rst>`_
* `設定 Vim 的 Rust 開發環境 <usage/rust-vim-plugin.rst>`_
* `Type System <lang-design/type-system.rst>`_
* `常見縮寫 <documentation/abbreviation.rst>`_
* `相關資源 <learning-resource/resource.rst>`_
