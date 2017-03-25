========================================
Asynchronous
========================================


.. contents:: 目錄


Futures
========================================

Future （有時又被稱為 Promise）是 Asynchronous 程式中很常見的一個概念，
作為一個中間人來檢查或使用 Asynchronous 產生的值，
而 Rust 當中也有叫做
`Futures <https://github.com/alexcrichton/futures-rs>`_
的 Library 專門負責這件事。

在這個 Library 中，
Futures 是任何實做了 ``Future`` trait 的型別，
trait 內包含許多方便使用的函式。



Mio
========================================

`Mio <https://github.com/carllerche/mio>`_ （Metal IO）
是 OS 的 I/O event 的抽象化，
抽象化系統的層例如 epoll、kqueue 等 API，
提供統一的操作界面。


Tokio
========================================

Tokio 是基於 ``futures`` 和 ``mio`` 的 Asynchronous I/O Framework，
藉由底層的 Libraries 要在上面建立更完整更貼近應用程式的功能，
例如 SOCKS5 Proxy Server、HTTP Client、HTTP Server。



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

* `Wikipedia - Futures and Promises <https://en.wikipedia.org/wiki/Futures_and_promises>`_
