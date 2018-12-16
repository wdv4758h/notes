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

* `Pattern Matching <pattern-matching.rst>`_
* `錯誤處理 (Error Handling) <error-handling.rst>`_
* `Iterator <iterator.rst>`_
* `Tagged Unions (Sum Type) <tagged-unions.rst>`_
* `Macro <macro.rst>`_
* `Unsafe <unsafe.rst>`_



生態圈
========================================

* `Regular Expression <regex.rst>`_
    - regex
    - fancy-regex
* `Serialization <serialization.rst>`_
    - serde
* `Logging <logging.rst>`_
    - log
* `Security <security.rst>`_
    - ring
    - webpki
    - rustls
    - quinn
* `Asynchronous I/O  <asynchronous.rst>`_
    - futures
    - mio
    - tokio
    - actix
* `Error Handling <error-handling.rst>`_
    - Option/Result
    - Box<Error>
    - failure
* `Multimedia <multimedia.rst>`_
* `資料庫 (Database) <database.rst>`_



Unstable
========================================

* `CTFE (Compile Time Function Execution) <compile-time-function-execution.rst>`_



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

* `RFCs <rfcs.rst>`_
* `編譯器 (Compiler) <compiler.rst>`_
* `MIR (Mid-level Intermediate Representation) <mir.rst>`_
* `Standard Library 程式碼研讀 <std.rst>`_



列表
========================================

一般使用：

* `Testing <testing.rst>`_
* `Fuzz Testing <fuzz-testing.rst>`_
* `Benchmark <benchmark.rst>`_
* `套件處理 - Cargo <cargo.rst>`_
* `Linking <linking.rst>`_
* `文件 (Documentation) <documentation.rst>`_
* `網路相關 (Network) <network.rst>`_
* `開發相關工具 (Development Tools) <development-tools.rst>`_
* `Graphic <graphc.rst>`_
* `GUI <gui.rst>`_
* `Syntax Highlighting <syntax-highlighting.rst>`_
* `圖像處理 <image-manipulation.rst>`_
* `機器學習 <machine-learning.rst>`_
* `Microcontroller <microcontroller.rst>`_


Edition：

* `Rust 2015 <edition-2015.rst>`_
* `Rust 2018 <edition-2018.rst>`_


其他：

* `文章閱讀 <articles.rst>`_
* `Tips <tips.rst>`_
* `生態圈 <ecosystem.rst>`_
* `Servo <servo.rst>`_
* `runtime reflection - "Any" type trait <any.rst>`_
* `Rust to asm.js <asmjs.rst>`_
* `Make Parity work on FreeBSD <make-parity-work-on-freebsd.rst>`_
* `Misc <misc.rst>`_
* `Videos <videos.rst>`_
* `FAQ <faq.rst>`_
* `Design Pattern <design-pattern.rst>`_
* `相關書籍 <books.rst>`_
* `從 C 轉譯成 Rust <c-to-rust.rst>`_
* `特性簡表 <features-basic.rst>`_
* `撰寫 Kernel <kernel.rst>`_
* `讓 Parity 可以在 FreeBSD 上編譯的紀錄 <make-parity-work-on-freebsd.rst>`_
* `Monomorphization <monomorphization.rst>`_
* `Object Safety <object-safety.rst>`_
* `效能觀察 <performance.rst>`_
* `設定 Vim 的 Rust 開發環境 <rust-vim-plugin.rst>`_
* `Type System <type-system.rst>`_
* `常見縮寫 <abbreviation.rst>`_
* `相關資源 <resource.rst>`_
