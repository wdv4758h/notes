========================================
Rust 程式碼範例
========================================


.. contents:: 目錄


Counter By HashMap
========================================

HashMap 內 key/value 的型別可以交給 Rust 編譯器來推斷，
利用 ``or_insert`` 可以在碰到沒有見過的 key 時插入預設值。

.. code-block:: rust

    let mut counter = HashMap::new();
    for key in data {
        *counter.entry(key).or_insert(0) += 1;
    }
