========================================
Unsafe
========================================


.. contents:: 目錄


介紹
========================================

Unsafe 是 Rust 中告知編譯器「相信我」的關鍵字，
使用後編譯器就會解除對該 block 的記憶體處理限制，
但是程式設計師自己就要負起管理好記憶體的責任，
否則 Rust 設計上想要避免的眾多類型記憶體問題就可能會發生。

.. code-block:: rust

    unsafe {
        // some code here
    }



參考
========================================

* `Unsafe Rust - The Rust Programming Language <https://doc.rust-lang.org/book/second-edition/ch19-01-unsafe-rust.html>`_
* `The Dark Arts of Advanced and Unsafe Rust Programming <https://doc.rust-lang.org/nomicon/>`_
* `The End of Unsafety - The Past, Present and Future of The Rust Programming Language <https://brson.github.io/the-end-of-unsafety/>`_
