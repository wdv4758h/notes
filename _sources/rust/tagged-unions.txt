========================================
Tagged Unions (Sum Type)
========================================


.. contents:: 目錄


介紹
========================================

**Enum type** ，是把所有可能的名稱列舉出來，
例如：

.. code-block:: rust

    // Rust

    enum Animal {
        Cat,
        Fish,
    }


**Union type** ，是同一份資料可以用不同的方式解讀，
例如：

.. code-block:: c

    // C

    union Data {
        unsigned int legs:  // 解讀一
        double fins;        // 解讀二
    }


**Tagged Union**，
在 Type Theory 中會被歸類在 **Sum Type** ，
結合了 **Enum type** 和 **Union type** 的能力，
例如：

.. code-block:: rust

    // Rust

    enum Animal {
        Cat { weight: f32, legs: usize },
        Fish { weight: f32, fins: usize },
    }


Rust 可以藉由 ``enum`` 來實做出 **Option type** （類似 Haskell 的 Maybe monad）：

.. code-block:: rust

    // Rust

    enum Option<T> {
        Some(T),
        None,
    }


也可以實做 **Result type** ：

.. code-block:: rust

    // Rust
    enum Result<T, E> {
       Ok(T),
       Err(E),
    }


參考
========================================

* `A quick tour of Rust’s Type System Part 1: Sum Types (a.k.a. Tagged Unions) <https://tonyarcieri.com/a-quick-tour-of-rusts-type-system-part-1-sum-types-a-k-a-tagged-unions>`_
* `Wikipedia - Enumerated type <https://en.wikipedia.org/wiki/Enumerated_type>`_
* `Wikipedia - Union type <https://en.wikipedia.org/wiki/Union_type>`_
* `Wikipedia - Tagged union <https://en.wikipedia.org/wiki/Tagged_union>`_
* `Wikipedia - Type theory <https://en.wikipedia.org/wiki/Type_theory>`_
* `Wikipedia - Product type <https://en.wikipedia.org/wiki/Product_type>`_
* `Wikipedia - Quotient type <https://en.wikipedia.org/wiki/Quotient_type>`_
* `Wikipedia - Option type <https://en.wikipedia.org/wiki/Option_type>`_
* `Wikipedia - Result type <https://en.wikipedia.org/wiki/Result_type>`_
