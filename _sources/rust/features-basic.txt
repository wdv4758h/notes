========================================
Rust's Features
========================================

* 靜態型別
* 型別推斷
* 預設是 immutable，用 ``mut`` 關鍵字指定 mutable
* Ownership
* 除了少數是 statement 外 (如 ``let`` 和 ``;``)，其他都是 expression
    - Expressions return a value, and statements do not.
    - 重新 assign 也是 expression (回傳 unit type)
    - 結尾加上 ``;`` 會把 expression 轉成 statement，並丟棄回傳的值，回傳 unit type
    - unit type 是特別而且不常使用的 data type，用 ``()`` 表示
