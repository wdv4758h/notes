========================================
Asynchronous I/O
========================================


.. contents:: 目錄


簡介
========================================

Asynchronous I/O 對於現今的網路程式設計非常重要，
也是處理 I/O 相關問題的效能關鍵。

目前常見的程式語言 Asynchronous I/O 實做模式有三種：

* async/await
    - C#
    - JavaScript
    - Python
* implicit concurrent runtime (green-threading)
    - CSP (communicating sequential processes)
        + Go
    - Actor model
        + Erlang
* Monadic transformations on lazily evaluated code
    - do notation
        + Haskell


Rust 選擇的是 async/await 的模式，
藉此來跟 type system 中的 ownership 和 borrowing 整合，
此作法也可以把實做完全放在 library 中，
不用像 green-threading 模式深入地把實做綁進語言核心設計。



如何實做 Asynchronous I/O
========================================

第一層：作業系統 API - epoll/kqueue/...
---------------------------------------

現代作業系統有提供效能比早期 select/poll 好的 API，
例如：

* Linux: epoll
* FreeBSD: kqueue


藉由這些 API 可以達到效能極佳的 Asynchronous I/O，
而根據不同作業系統會有不同的 API。
撰寫應用程式時，可以選擇直接使用系統 API，
或者是對各系統 API 包裝後的 library，
也就是下一層要提到的內容。


第二層：抽象化包裝 - Mio
------------------------------

如先前所說，
系統 API 會根據平台不同而有差異，
因此有數個 library 實做了抽象化，
例如 libev、libevent、libuv、Gio、Boost.Asio 等等。

在 Rust 生態圈內主要是 `Mio <https://github.com/carllerche/mio>`_
在負責系統 Asynchronous I/O 的抽象化，
支援諸如 Linux/OS X/Windows/FreeBSD 等平台，
並且盡可能地不增加效能損失，
讓使用 mio 抽象化的效能跟直接使用系統 API 一樣。



第二層：高階 API - Tokio
------------------------------

.. image:: /images/rust/tokio-stack.png


`Tokio <https://github.com/tokio-rs/>`_
是基於 ``futures`` 和 ``mio`` 的 Asynchronous I/O Framework，
藉由底層的 libraries 在上面建立更完整更貼近應用程式的功能，
提供更多方便的包裝，
例如 SOCKS5 Proxy Server、HTTP Client、HTTP Server。



Futures
========================================

Future （有時又被稱為 Promise）是 Asynchronous 程式中很常見的一個概念，
作為一個中間人來檢查或使用 Asynchronous 產生的值，
而 Rust 當中也有叫做
`Futures <https://github.com/rust-lang-nursery/futures-rs>`_
的 Library 專門負責這件事。

在這個 Library 中，
Futures 是任何實做了 ``Future`` trait 的型別，
trait 內包含許多方便使用的函式。



範例
========================================

Futures 簡單範例
------------------------------

先假設我們有以下的程式碼：

.. code-block:: rust

    const BIG_PRIME: u64 = 15485867;

    // checks whether a number is prime, slowly
    fn is_prime(num: u64) -> bool {
        for i in 2..num {
            if num % i == 0 { return false }
        }
        true
    }


一般的同步版本：

.. code-block:: rust

    // Synchronous version
    fn main() {
        if is_prime(BIG_PRIME) {
            println!("Prime");
        } else {
            println!("Not prime");
        }
    }


利用 Futures 的非同步版本（使用 threads），
不等結果就結束：

.. code-block:: rust

    extern crate futures;
    extern crate futures_cpupool;

    use futures::Future;
    use futures_cpupool::CpuPool;

    fn main() {
        // set up a thread pool
        let pool = CpuPool::new_num_cpus();

        // spawn our computation, getting back a *future* of the answer
        let prime_future = pool.spawn_fn(|| {
            let prime = is_prime(BIG_PRIME);

            // For reasons we'll see later, we need to return a Result here
            let res: Result<bool, ()> = Ok(prime);
            res
        });

        println!("Created the future");
    }


利用 Futures 的非同步版本（等待結果）：

.. code-block:: rust

    extern crate futures;
    extern crate futures_cpupool;

    use futures::Future;
    use futures_cpupool::CpuPool;

    fn main() {
        // set up a thread pool
        let pool = CpuPool::new_num_cpus();

        // spawn our computation, getting back a *future* of the answer
        let prime_future = pool.spawn_fn(|| {
            let prime = is_prime(BIG_PRIME);

            // For reasons we'll see later, we need to return a Result here
            let res: Result<bool, ()> = Ok(prime);
            res
        });

        println!("Created the future");

        // unwrap here since we know the result is Ok
        if prime_future.wait().unwrap() {
            println!("Prime");
        } else {
            println!("Not prime");
        }
    }


Futures + Tokio Timer
------------------------------

在時間內沒結果就不等了。

.. code-block:: rust

    extern crate futures;
    extern crate futures_cpupool;
    extern crate tokio_timer;

    use std::time::Duration;

    use futures::Future;
    use futures_cpupool::CpuPool;
    use tokio_timer::Timer;

    fn main() {
        let pool = CpuPool::new_num_cpus();
        let timer = Timer::default();

        // a future that resolves to Err after a timeout
        let timeout = timer.sleep(Duration::from_millis(750))
            .then(|_| Err(()));

        // a future that resolves to Ok with the primality result
        let prime = pool.spawn_fn(|| {
            Ok(is_prime(BIG_PRIME))
        });

        // a future that resolves to one of the above values -- whichever
        // completes first!
        let winner = timeout.select(prime).map(|(win, _)| win);

        // now block until we have a winner, then print what happened
        match winner.wait() {
            Ok(true) => println!("Prime"),
            Ok(false) => println!("Not prime"),
            Err(_) => println!("Timed out"),
        }
    }


Tokio: Echo Server
------------------------------


Tokio: Database
------------------------------


參考
========================================

* `Wikipedia - Asynchronous I/O <https://en.wikipedia.org/wiki/Asynchronous_I/O>`_
* `Wikipedia - Futures and Promises <https://en.wikipedia.org/wiki/Futures_and_promises>`_
* `Improving GStreamer performance on a high number of network streams by sharing threads between elements with Rust’s tokio crate <https://coaxion.net/blog/2018/04/improving-gstreamer-performance-on-a-high-number-of-network-streams-by-sharing-threads-between-elements-with-rusts-tokio-crate/>`_
* `Tokio internals: Understanding Rust's asynchronous I_O framework from the bottom up <https://cafbit.com/post/tokio_internals/>`_
