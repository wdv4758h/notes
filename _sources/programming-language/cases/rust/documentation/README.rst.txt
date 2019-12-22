========================================
文件 (Documentation)
========================================


.. contents:: 目錄


介紹
========================================

Rust 官方在一開始就有考慮好文件的事情，
所以有工具 (rustdoc) 可以自動生出良好的 API 文件，
但是如果要撰寫專案使用教學當然還是需要另外寫更多內容。

在 Rust 生態圈中，
doc.rs 會自動幫 crates.io 上的專案產生 API 文件。
而教學文件則普遍使用 mdBook 來撰寫。



官方文件
========================================

語言本身功能：

* `The Rust Programming Language <https://doc.rust-lang.org/nightly/book/>`_
    - 從入門開始的語言教學
* `Rust by Example <https://doc.rust-lang.org/rust-by-example>`_
    - 用範例學習的入門教學
* `The Rust Standard Library <https://doc.rust-lang.org/std/>`_
    - 標準函式庫的 API 文件
* `The Cargo Book <https://doc.rust-lang.org/cargo/>`_
    - 套件管理工具 Cargo 的教學
* `The Rust Reference <https://doc.rust-lang.org/nightly/reference>`_
    - 語言的設計細節
* `The Unstable Book <https://doc.rust-lang.org/nightly/unstable-book/>`_
    - 尚未穩定的功能
* `Rust FAQ <https://github.com/rust-lang/prev.rust-lang.org/blob/master/en-US/faq.md>`_
    - 舊版網站上的 FAQ 資源
* `Rust Compiler Error Index <https://doc.rust-lang.org/error-index.html>`_
    - 編譯器錯誤清單
* `The Rustonomicon <https://doc.rust-lang.org/nomicon/>`_
    - Rust 進階教學
* `Rust Bibliography <https://forge.rust-lang.org/bibliography.html>`_
    - 和 Rust 相關的論文
* `Unsafe Code Guidelines Reference <https://rust-lang.github.io/unsafe-code-guidelines/>`_
    - 撰寫 unsafe 程式碼需要注意的事情


語言應用：

* `Rust Cookbook <https://rust-lang-nursery.github.io/rust-cookbook/>`_
    - 搭配既有 Rust 生態圈的範例應用
* `Rust API Guidelines <https://rust-lang-nursery.github.io/api-guidelines/>`_
    - 撰寫套件時的 API 設計守則，從過往經驗中學習怎樣的 API 才方便、強大
* `Rust and WebAssembly <https://rustwasm.github.io/book/>`_
    - 針對把 Rust 編譯成 WebAssembly 使用的教學和調整細節
* `The Embedded Rust Book <https://rust-embedded.github.io/book/>`_
    - 針對嵌入式平台的 Rust 使用教學
* `Command Line Applications in Rust <https://rust-lang-nursery.github.io/cli-wg/>`_
    - 開發 CLI 工具的教學
* `Asynchronous Programming in Rust <https://rust-lang.github.io/async-book/>`_
    - 非同步應用的教學


官方專案開發：

* `Guide to Rustc Development <https://rust-lang.github.io/rustc-guide/>`_
    - 官方 Rust 編譯器開發教學
* `Rustc API <https://doc.rust-lang.org/nightly/nightly-rustc/rustc/>`_
    - 官方 Rust 編譯器 API 文件
* `Rust Forge <https://forge.rust-lang.org/>`_
    - Rust 官方專案開發的輔助資源



文件工具
========================================

rustdoc
------------------------------

:Repo: https://github.com/rust-lang/rust/tree/master/src/librustdoc


Rust 官方的文件系統，
會把程式碼內的 docstring 爬出來轉成 HTML，
轉出來得 API 文件會有所有的 symbol 連結，
可以方便地找到原本的定義，
也有方便的搜尋界面。

使用方式就是在專案下 ``cargo doc`` 即可。



Doc.rs
------------------------------

:Repo: https://github.com/rust-lang/docs.rs
:Site: https://docs.rs/


Rust crates 的文件集中地，
會自動去編譯出每個套件的文件，
也可以在不同版本的文件中切換。

本來是非官方工具，
但是功能廣受歡迎，
現在已經把專案移到官方組織底下。



mdBook
------------------------------

:Repo: https://github.com/rust-lang-nursery/mdBook


rustdoc 是負責 API 文件，
如果要撰寫比較像書籍的教學文件就比較不適合，
此時可以使用 mdBook，
mdBook 可以比較良好地用章節呈現內容。
