========================================
Cross Language LTO
========================================


.. contents:: 目錄


介紹
========================================

Cross Language LTO 意思是可以
把 Rust、C、C++ 等不同語言的程式碼
在編譯過程中一起優化，
Rust 函式可以 inline 到 C++ 的程式中，
C++ 函式也可以 inline 到 Rust 程式碼中，
語言的優化界線被淡化。



參考
========================================

* `Rust - Implement cross-language ThinLTO <https://github.com/rust-lang/rust/issues/49879>`_
* `Firefox - Perform ThinLTO across C++/Rust language boundaries <https://bugzilla.mozilla.org/show_bug.cgi?id=1486042>`_
