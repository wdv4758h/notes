========================================
文件 (Documentation)
========================================


.. contents:: 目錄


介紹
========================================

Rust 官方在一開始就有考慮好文件的事情，
所以有工具可以自動生出良好的 API 文件，
但是如果要使用專案教學當然還是需要自行撰寫。



rustdoc
========================================

:Repo: https://github.com/rust-lang/rust/tree/master/src/librustdoc


Rust 官方的文件系統，
會把程式碼內的 docstring 爬出來轉成 HTML，
轉出來得 API 文件會有所有的 symbol 連結，
可以方便地找到原本的定義，
也有方便的搜尋界面。

使用方式就是在專案下 ``cargo doc`` 即可。



Doc.rs
========================================

:Repo: https://github.com/onur/docs.rs
:Site: https://docs.rs/


Rust crates 的文件集中地，
會自動去編譯出每個套件的文件，
也可以在不同版本的文件中切換。



mdBook
========================================

:Repo: https://github.com/rust-lang-nursery/mdBook


rustdoc 是負責 API 文件，
如果要撰寫比較像書籍的教學文件就比較不適合，
此時可以使用 mdBook，
mdBook 可以比較良好地用章節呈現內容。
