:title: Rust 的一些紀錄
:slug: some-rust
:date: 2015-05-14 21:57
:modified: 2015-05-24 21:57
:category: Rust
:tags:
:author: wdv4758h
:summary:

.. contents::

最近又心血來潮翻了一點 Rust，
目前版本還在 1.0 beta (現在已經正式 release 啦~)，
但是有許多東西已經差不多定型了，
開始紀錄一下狀況 XD

* 待研究列表
    - traits
    - format! 實作
    - macro
    - Ownership
        * Box
    - Lifetime
    - static variable
    - dylib, rlib, and staticlib
    - coroutine

----

* `[GitHub] awesome-rust <https://github.com/kud1ing/awesome-rust>`_
* `Reddit - Rust <http://www.reddit.com/r/rust/>`_

[Ｏ] Big Number 支援？
========================================

有！

* `Rust - Module num::bigint <http://doc.rust-lang.org/num/num/bigint/>`_
* `pidigits benchmark | Computer Language Benchmarks Game <http://benchmarksgame.alioth.debian.org/u64/performance.php?test=pidigits>`_
* `The Fastest BigInt In The West <http://www.wilfred.me.uk/blog/2014/10/20/the-fastest-bigint-in-the-west/>`_



[Ｏ] First-class function 支援？
========================================

有！

.. table::
    :class: table table-bordered

    +----------------------------------+---------------------------------------------------+---------------------+
    | Higher-order functions           | Non-local variables                               |                     |
    +------------------------+---------+------------------+---------------------+----------+ Partial application |
    | Arguments              | Results | Nested functions | Anonymous functions | Closures |                     |
    +========================+=========+==================+=====================+==========+=====================+
    | Yes                    | Yes     | Yes              | Yes                 | Yes      | No                  |
    +------------------------+---------+------------------+---------------------+----------+---------------------+

* `Wikipedia - Firsr-class function <http://en.wikipedia.org/wiki/First-class_function>`_



[Ｏ] map / reduce / filter 之類的東西？
========================================

有！在 iterator

* `Rust - Trait std::iter::Iterator <http://doc.rust-lang.org/std/iter/trait.Iterator.html>`_

.. code-block:: rust

    let a = [1, 2];

    // get a new iterator with map
    let it = a.iter().map(|&x| 2 * x);

    // get a new iterator with filter
    let it = a.iter().filter(|&x| *x > 1);

    // use fold (reduce) to get summation
    let a = [1, 2, 3, 4, 5];
    let value = a.iter().fold(0, |acc, &item| acc + item);



[Ｏ] Option type (maybe type) ?
===============================

有！

(目前理解) Maybe monad 裡面可能是該有的值或是 Nothing，
這樣包起來可以提醒你 handle 好意外狀況。
在 Rust 裡這樣的 type 叫作 ``Option`` ，
``Option`` 可以用來表示 function 可能會 fail，
實際存的資料長這樣 :

.. code-block:: rust

    pub enum Option<T> {
        None,
        Some(T),
    }

其中可以看到除了預期的型態之外，多加了一個 None 為可能的回傳，
當處理出問題就回傳 ``None`` ，
適用於簡單的狀況。
但是如果狀況比較複雜，
想要知道為什麼會 fail 的時候，
可以使用 ``Result`` ，
實際存的資料長這樣 :

.. code-block:: rust

    enum Result<T, E> {
       Ok(T),
       Err(E)
    }

可以看到正常狀況下會回傳 ``Ok(T)`` ，失敗的話會回傳 ``Err(E)`` ，
跟前面的 ``Option`` 相比多了 error 狀況可以檢查。

* `Option Monads in Rust <http://hoverbear.org/2014/08/12/option-monads-in-rust/>`_
* `Error Handling in Rust <http://blog.burntsushi.net/rust-error-handling/>`_
* `On Error Handling in Rust <http://lucumr.pocoo.org/2014/10/16/on-error-handling/>`_
* `Rust - Error Handling <https://doc.rust-lang.org/book/error-handling.html>`_
* `Using The Option Type Effectively <http://blog.8thlight.com/uku-taht/2015/04/29/using-the-option-type-effectively.html>`_
* `The Option Type <http://blog.8thlight.com/dave-torre/2015/03/11/the-option-type.html>`_
* `Wikipedia - Option type <http://en.wikipedia.org/wiki/Option_type>`_

[Ｏ] OOP (object-oriented programming)？
========================================

(研讀中 XD)

* `Abstraction without overhead: traits in Rust <http://blog.rust-lang.org/2015/05/11/traits.html>`_
* `[2013] The Rise of the Gang of Four with Rust <https://joshldavis.com/2013/06/16/the-rise-of-the-gang-of-four-with-rust/>`_
* `Go and Rust — objects without class <https://lwn.net/Articles/548560/>`_
* `Rust Book - Traits <https://doc.rust-lang.org/book/traits.html>`_
* `Rust Book - Traits Objects <https://doc.rust-lang.org/book/trait-objects.html>`_
* `rust-guidelines - traits/objects <https://github.com/rust-lang/rust-guidelines/blob/master/features/traits/objects.md>`_
* `Wikipedia - Trait (computer programming) <http://en.wikipedia.org/wiki/Trait_%28computer_programming%29>`_

[Ｏ] Type Inference
========================================

[Ｏ] 高度的 Memory Control？
========================================

* `Guaranteeing Memory Safety in Rust <http://www.slideshare.net/nikomatsakis/guaranteeing-memory-safety-in-rust-39042975>`_

[－] REPL？
========================================

官方目前沒有提供，
但是有專案正在進行中

* `[GitHub] rusti <https://github.com/murarth/rusti>`_

[？] 預設提供的 Sort Algorithm 是啥？
========================================

.. code-block:: rust

    let mut v = [-5, 4, 1, -3, 2];
    v.sort();

目前看 ``src/libcollections/slice.rs`` 裡面的 ``sort_by`` 是去 call ``merge_sort``

.. table::
    :class: table table-bordered

    +--------------+------------+
    | Worst Case   | O(n log n) |
    +--------------+------------+
    | Average Case | O(n log n) |
    +--------------+------------+
    | Best Case    | O(n log n) |
    +--------------+------------+
    | Space        | O(2 n)     |
    +--------------+------------+
    | Stable       | Yes        |
    +--------------+------------+

* `Rust - Primitive Type slice - sort_by <https://doc.rust-lang.org/std/primitive.slice.html#method.sort_by>`_

[Ｏ] Regular Expression 支援？
========================================

官方有實作，也有文件，不過放在另外一個 package

* `[GitHub] rust-lang/regex <https://github.com/rust-lang/regex>`_
* `Rust - Crate regex <http://doc.rust-lang.org/regex/regex/>`_

[Ｏ] FFI (Foreign Function Interface)？
========================================

* `Rust Once, Run Everywhere <http://blog.rust-lang.org/2015/04/24/Rust-Once-Run-Everywhere.html>`_
* `Rust Book - Foreign Function Interface <https://doc.rust-lang.org/book/ffi.html>`_
* `Rust - Module std::ffi <https://doc.rust-lang.org/std/ffi/>`_
* `Rust - Crate libc <http://doc.rust-lang.org/libc/libc/>`_
* `[GitHub] rust-lang/libc <https://github.com/rust-lang/libc>`_
* `[GitHub] rust-ffi-examples - FFI examples written in Rust <https://github.com/alexcrichton/rust-ffi-examples>`_

[Ｏ] Import third party library？
========================================

[Ｏ] Native Threading Support？
========================================

(Native Threads) 目前是 1:1 的 thread，每個 user thread 都會對應到一個 kernel thread

* `Rust - Module std::thread <https://doc.rust-lang.org/std/thread/>`_
* `Rust Book - Concurrency <https://doc.rust-lang.org/book/concurrency.html>`_
* `Fearless Concurrency with Rust <http://blog.rust-lang.org/2015/04/10/Fearless-Concurrency.html>`_

[Ｘ] Garbage Collection？
========================================

[Ｏ] Format String？
========================================

使用 macro ``format!``

.. code-block:: rust

    format!("the value is {}", 123)

* `Rust - Module std::fmt <https://doc.rust-lang.org/std/fmt/>`_

[Ｏ] Ownership？
========================================

* `Rust ownership, the hard way <http://chrismorgan.info/blog/rust-ownership-the-hard-way.html>`_
* `[GitHub] Rust RFCs - 0599 - Default Object Bound <https://github.com/rust-lang/rfcs/blob/master/text/0599-default-object-bound.md>`_
* `[2013] Using the Pointer Ownership Model to Secure Memory Management in C and C++ <http://blog.sei.cmu.edu/post.cfm/using-the-pointer-ownership-model-to-secure-memory-management-in-c-and-c>`_
    - 不錯的 Memory Management 相關背景知識解說
* `CERT C Coding Standard <https://www.securecoding.cert.org/confluence/display/c/CERT+C+Coding+Standard>`_



Third Party
=============================================

Django-like project？
------------------------------

還在發展中，漸漸有一些 web framework 出現。

* `Introducing Teepee: the next step for rust-http <http://chrismorgan.info/blog/introducing-teepee.html>`_

上面那篇的作者有寫過 Django，後來跳出來用 Rust 想做另一套自己想要的 web framework，
但是 Rust 在當時還沒有強大的 HTTP library 可以用，
所以寫了 rust-http，後來對 Rust 更熟悉以及有了 rust-http 的經驗後，
決定重設計一個 library 並增加更多支援，這 library 被取名為 ``Teepee`` 。

現在出現的 framework 有 :

* `Iron <http://ironframework.io/>`_
* `nickel.rs <http://nickel.rs/>`_

----

* `Are there any Rust projects that have similar goals to Django (i.e. full-featured web framework)? If not, want to start one? <http://www.reddit.com/r/rust/comments/2myght/are_there_any_rust_projects_that_have_similar/>`_



Game Engine？
------------------------------

* http://www.piston.rs/


Template Engine？
------------------------------
