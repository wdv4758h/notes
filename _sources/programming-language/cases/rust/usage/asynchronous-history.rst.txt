========================================
Asynchronous History
========================================


.. contents:: 目錄


QCon 2019 - Rust's Journey to Async/Await
=========================================

:Video: https://www.infoq.com/presentations/rust-2019/


名詞解釋：

* Parallel: 同時做很多事情
* Concurrent: 做很多事情，但不同時
* Asynchronous: 用來描述程式語言的特性，該特性幫助達到 Parallelism 或 Concurrency
* Task: 通用的用詞，描述 Parallel 或 Concurrent 系統中的某些運算

----

Cooperative v.s. Preemptive Multitasking：

* Cooperative Multitasking
    - 每個 Task 自己決定是不是要把運算資源讓給其他 Tasks
* Preemptive Multitasking
    - 系統決定是不是要把運算資源讓給其他 Tasks

----

Native v.s. Green Threads：

* Native Threads
    - 1:1 threading
    - 由作業系統提供
    - 優點
        + 作業系統的一部分，作業系統會處理排程
        + 相對直白好懂
    - 缺點
        + 預設的狀況可能比較沈重（建立的成本）
        + 能夠建立的數量比較受限
* Green Threads
    - M:N threading
    - 由程式語言提供
    - 優點
        + 不是作業系統的一部分
        + runtime 自己處理排程
        + 相對輕量化（建立的成本）
        + 能夠建立非常大量的 Green Threads
    - 缺點
        + stack 的成長可能會造成問題
        + 呼叫 C 程式時有額外的成本

----

Synchronous/Asynchronous & Blocking/Non-blocking：

+--------------+----------------------------+--------------------+
|              | Synchronous                | Asynchronous       |
+==============+============================+====================+
| Blocking     | old-school implementations | doesn't make sense |
+--------------+----------------------------+--------------------+
| Non-blocking | Erlang, Go, Ruby           | Node.js, Python    |
+--------------+----------------------------+--------------------+


Synchronous Non-blocking：

* 用 Synchronous 的風格撰寫程式碼，但是程式語言會自動處理好讓程式 non-blocking
* 程式碼看起來像是 blocking，但其實不會
* 祕密在於 runtime 是 non-blocking 的
* 程式碼仍然維持易懂，但是又可以 non-blocking 取得的效能提升
* Rust 以前的 Green Threads 就是這種設計

----

問題：「一個不讓你直接使用作業系統 threads 的系統程式語言！？」

A "systems programming language" that doesn't let you use the system threads!?


Rust 本來只提供 Green Threads，
後來也提供 Native Threads 讓人自己選，
底下透過 librustrt 這個 runtime 來處理。
但是發現這兩種同時存在並互動的話有非常多的問題，
尤其是在 Rust 的語言設計之下更加複雜，
為了把 Native Threads 和 Green Threads 抽象化，
必須加入一些 bookkeeping 的資料，
然而這些資料讓 Green Threads 變得不那麼輕量，
最後 Green Threads 變成了比較差版本的 Native Threads。

於是Rust 決定在 1.0 釋出前移除 Green Threads 和 librustrt 這個 runtime，
只提供大家最熟知、最穩定、最安全的 Native Threads，
讓 1.0 版本小而穩。

2015 年 5 月，釋出 Rust 1.0 版。

隨著 Rust 的成長，
大家有了許多網路服務的需求，
但是 Rust 的 I/O model 並不能達到 Rust 該有的高效能，
因為 Native Threads 搭配 I/O 不是最佳組合。

----

CPU bounds v.s. I/O bounds：

* CPU bounds
    - 系統忙著運算，只要提升運算效能就能增加程式效能
* I/O bounds
    - 系統忙著 I/O，提升運算效能不太能增加程式效能
    - 例如：在等網路傳輸、硬碟讀寫

----

* C10K
* Apache
    - pre-fork
    - worker
* Nginx
    - Event Loop

----

使用 Green Threads 來處理 I/O bounds： Erlang, Go

然而 Green Threads 對於 Rust 有一個很大的問題，
那就是呼叫 C 程式的成本很高。
這對於 Go 來說不是很重要，因為 Go 嘗試要把所有東西都用 Go 實做。
這對於 Erlang 來說也不是很重要，因為大部分使用 Erlang 的狀況不太會要求 C 等級的運算速度。
但是 Rust 是設計來做系統程式設計語言，
在呼叫 C 程式有額外成本會是個重大的問題，
因為這年頭撰寫系統程式很難不碰到 C 程式碼（光是底下作業系統就有了）。

----

問題：「一個呼叫 C 程式有額外成本的系統程式語言！？」

A "system programming language" that has overhead when calling into C code!?


幸運的，
Rust 除了 Green Threads 以外還有其他選擇，
那就是 Event Loop。

要做到 Evented I/O 就需要 non-blocking APIs，
為了讓事情變得 Asynchronous。
我們可能會註冊事件和 callback，
但是隨著事件的複雜度上升，
很容易造成 callback hell，
深度也越來越深。


* Promise：提供 API 來串事件和 callback，讓整份程式碼變得比較扁平
* Futures：像似 Promises，跟 Promises 有相同的想法，但是有不同的 API，在這之上可以加語法糖 async/await 來輔助
    - 例如 Scala
    - 參考："Your Server as a Function"

----

Rust Futures 0.1：

.. code-block:: rust

    trait Future {
        type Item;
        type Error;

        fn poll(&mut self) -> Poll<Self::Item, Self::Error>;
    }


JavaScript Promises v.s. Rust Futures：

* JavaScript Promises
    - JavaScript Promises 深入地做進 JavaScript
    - JavaScript 具有 runtime
    - Promises 在建立時就會自動開始執行
    - 簡單，但是有些壞處，例如會有很多記憶體分配

* Rust Futures
    - 並沒有深入地做進 Rust
    - Rust 沒有 runtime
    - 一定要把 Futures 送進 Executors 才會開始執行
    - Futures 並不會做任何處理（惰性）直到 "poll" 函式被 Executors 呼叫
    - 使用上稍微更複雜，但是非常有效率
    - 每個 Task 的建立只會有一次計算好大小的記憶體分配
    - 可以編成狀態機
    - 在編譯時期就可以知道需要分配多少記憶體，執行時不需要讓 stack 成長或縮減（Green Threads 的話就會）

----

為了知道 Rust Future 0.1 夠不夠好，
於是開始在這之上建立各式各樣的東西。


Future 0.2：

.. code-block:: rust

    trait Future {
        type Item;
        type Error;

        fn poll(&mut self, cx: task::Context) -> Poll<Self::Item, Self::Error>;
    }


Future 0.2 跟 Future 0.1 的差異：

* 沒有隱性 context
* 不需要 Thread Local Storage
    - Future 0.1 會用 Thread Local Storage 來做一些 bookkeeping
    - 但是這代表系統需要支援 Thread Local Storage，如果要用來撰寫 bare metal 的程式會有問題

----

async/await

讓 Asynchronous 程式碼長得像 Synchronous 程式碼，
但是透過關鍵字 await 來處理 Asynchronous 的狀況。

採用案例：C#、Python、JavaScript

對於 Rust 來說，
因為沒有 GC 的關係，
async/await 的支援顯得比其他程式語言更重要。

對於 JavaScript 來說可能只是方便，
但對於 Rust 來說，是用來幫助編譯器需要了解物件的記憶體使用。
Rust 不能像 JavaScript 一樣隨心所欲地製造物件，
編譯器會做記憶體操作的檢查，
然而在使用 callback chaining 的時候，
borrow checker 並不了解這類 Asynchronous 程式碼，
所以無法正確地追蹤記憶體使用。
根本原因在於程式碼在建立和執行的限制並不一樣，
建立 Futures 時的狀況和後續丟到 Executors 執行時有極大的差異，
要讓編譯器在沒有 async/await 輔助的狀況下確保記憶體操作安全很困難，
程式碼會變得過度複雜，根本不能被實際採用。

然而 async/await 的支援可以教 borrow checker 這些限制，
讓編譯器理解 Asynchronous 程式碼，
並大幅降低 Rust 在這應用下的複雜度。

----

Rust Future 0.3：並不是所有 Futures 都會有 Erorr

``std::future`` :

.. code-block:: rust

    pub trait Future {
        type Output;

        fn poll(self: Pin<&mut Self>, cx: &mut Context) -> Poll<Self::Output>;
    }


* 其中的 **Pin** 就是 async/await 如何教 borrow checker 理解的關鍵。
* 如果你的 Future 可能會有錯誤，那可以把 ``Output`` 設成 ``Result<T, E>``

----

Rust 的 async/await 該用怎樣的語法？


* 在設計語法時要考慮特殊狀況
* 而 Rust 當中有很多特殊狀況


C#, JavaScript, Python:

.. code-block:: python

    await value


Rust 已經有 ``?`` 來做錯誤處理，
這要如何跟 async/await 一起運作？


案例一：

::

    await value?        // 撰寫這個時

    (await value)?      // 通常想要這個
    await (value?)      // 但是語法看起來比較像這個


案例二：

::

    (await (await value)?)


為了語法吵了非常久，
有人甚至提出了倒過來的問號 ``¿`` 。

為了讓這重要功能早點做進 Rust，
還是要趕快決定語法，
最後決定了 ``.await`` 和 ``.await?``


.. code-block:: rust

    // no errors
    future.await

    // with errors
    future.await?


----

Rust 的 async/await 可以在 WebAssembly 中使用，
甚至可以在 Rust Future 和 JavaScript Promise 間轉換！

----

Rust 的 async/await 終於在 2019 年要進入 MVP 了，
目前在 beta channel，
預計會在 Rust 1.39 釋出。

* [2019/09/30] `Async-await hits beta! <https://blog.rust-lang.org/2019/09/30/Async-await-hits-beta.html>`_

----

經驗：

* 一個好的 I/O 系統實做要花很多年！
* 不同程式語言有不同的限制

----

個人總結：

* 在沒有 GC 的狀況下維持 memory safety -> 編譯器檢查
* 系統程式語言 -> 呼叫 C 程式不能有額外成本 -> non-blocking 不能使用 green threads
* non-blocking 採用 event loop -> asynchronous -> future & callback -> 編譯器對記憶體檢查炸裂 -> 程式碼變太複雜 -> 用 async/await 教編譯器理解
