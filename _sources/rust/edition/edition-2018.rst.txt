========================================
Rust Edition 2018 - Productivity
========================================


.. contents:: 目錄


3.7 - Data Types
========================================

3.7.1 - struct 初始化簡便改進
------------------------------

如果變數名稱跟 struct 欄位一樣的話可以簡化：

.. code-block:: rust

    struct Point {
        x: i32,
        y: i32,
    }

    let x = 5;
    let y = 6;

    // old
    let p = Point {
        x: x,
        y: y,
    };

    // new
    let p = Point {
        x,
        y,
    };



3.15 - Platforms and target support
========================================

3.15.5 - 用 musl 產生完全靜態的執行檔
-------------------------------------


.. code-block:: rust

    rustup target add x86_64-unknown-linux-musl
    cargo build --target x86_64-unknown-linux-musl
