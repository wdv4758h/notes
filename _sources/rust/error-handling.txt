========================================
錯誤處理 (Error Handling)
========================================


.. contents:: 目錄


panic!
========================================

在碰到不預期的值狀況而無法處理，
我們可以使用 ``panic!`` 來進行 unwind，
同時程式也會直接離開（除非有自己寫額外的處理）。


.. code-block:: rust

    fn guess(n: i32) -> bool {
        if n < 1 || n > 10 {
            panic!("Invalid number: {}", n);
        }
        n == 5
    }

    fn main() {
        guess(11);
    }



Option
========================================

``Option`` 是 Rust 對資料的包裝，
代表可能有東西或是沒東西，
藉由這個包裝可以讓使用者注意到有例外狀況發生要進行處理，
簡單的方式就是直接呼叫 ``unwrap`` 打開不處理（碰到沒東西就爆炸），
但是還有其他很多處理方式。


``Option`` 的實做：

.. code-block:: rust

    enum Option<T> {
        None,
        Some(T),
    }


部份處理用函式：

* unwrap：直接不處理，假設都有東西，沒東西就給他直接爆炸
* unwrap_or：沒東西就使用另外一個值
* unwrap_or_else：沒東西就呼叫後面的函式取得一個值
* unwrap_or_default：沒東西就使用該型別的預設值
* expect：類似 unwrap，但是加入客製化訊息
* map：對內部的東西進行操作，產生另外一個 Option
* map_or：對內部的東西進行操作，沒東西就用另外一個值來操作，產生新的值
* map_or_else：對內部的東西進行操作，沒東西就呼叫後面的函式取得一個值來操作，產生新的值
* and：對兩個 Option 內部的資料進行 and 操作
* and_then：用 Option 內部的資料來呼叫函式，如果資料是空的就不呼叫
* or：對兩個 Option 內部的資料進行 or 操作
* or_else：呼叫函式來取得值，如果 Option 內有資料的話就不呼叫



Result
========================================

``Result`` 比起 ``Option`` 又更進一步儲存錯誤訊息，
把資料分成 ``Ok`` 和 ``Err`` 。
處理用的函式跟 ``Option`` 差不多，
但是有一些額外針對 ``Err`` 的處理。


``Result`` 的實做：

.. code-block:: rust

    pub enum Result<T, E> {
        Ok(T),
        Err(E),
    }



try! & ?
========================================

``?`` operator 是後來加入的操作，
功能等同於先前的 ``try!`` macro，
功用是回傳 ``Ok`` 內的值或是提早離開把 ``Err`` 傳出去。


``try!`` 的實做：

.. code-block:: rust

    #[macro_export]
    #[stable(feature = "rust1", since = "1.0.0")]
    macro_rules! try {
        ($expr:expr) => (match $expr {
            $crate::result::Result::Ok(val) => val,
            $crate::result::Result::Err(err) => {
                return $crate::result::Result::Err($crate::convert::From::from(err))
            }
        })
    }



error_chain
========================================

對於錯誤處理方面，
直接用字串做錯誤訊息對於 Application 來說就已經夠好了，
但是對於要設計 API 開出去給其他人用的話，
就需要客製的錯誤型別，
來提供更明確地訊息和 context。

`error_chain <https://github.com/brson/error-chain>`_
就是個輔助建立錯誤處理的 library，
可以串連多個錯誤訊息，
並控制處理錯誤的行為（例如輸出 backtrace），
還可以方便地在不同錯誤型別中轉換。


範例一 - 最簡單的程式碼生成
------------------------------

簡單的範例程式碼：

.. code-block:: rust

    error_chain! {}

會生成：

.. code-block:: rust

    pub enum ErrorKind {
        Msg(String),
    }

    pub struct Error(pub ErrorKind, _);

    type Result<T> = Result<T, Error>;

    pub trait ResultExt<T, E> {
        fn chain_err<F, EK>(self, callback: F) -> Result<T, Error>
            where F: FnOnce() -> EK, EK: Into<ErrorKind>;
    }

* ErrorKind：錯誤的種類，為一個 ``enum``
* Error：錯誤的型別，儲存錯誤用，為含有一些 ``error_chain`` 內部資訊的 struct（例如 backtrace）
* Result：簡單的 Result 包裝，內含 Error
* ResultExt：用於跟 ``error_chain`` 互動的 trait，內含 ``chain_err``


範例二 - 客製化錯誤
------------------------------

加入客製化的錯誤型別：

.. code-block:: rust

    error_chain! {
        links {
            Inner(inner::Error, inner::ErrorKind) #[doc = "Link to another `ErrorChain`."];
        }
        foreign_links {
            Io(::std::io::Error) #[doc = "Link to a `std::error::Error` type."];
        }
        errors {
            #[doc = "A custom error kind."]
            Custom
        }
    }


其中：

* ``links`` 是用來連結兩個 ``error_chain`` 產生的錯誤型別，
* ``foreign_links`` 是用來連結非 ``error_chain`` 產生的錯誤型別，
* ``errors`` 則是用來自己定義新的錯誤型別。


這段程式碼會生成：

.. code-block:: rust

    // 由於有定義新的錯誤，所以 ErrorKind 的內容有增加
    pub enum ErrorKind {
        Msg(String),
        Inner(ErrorKind), // inner::ErrorKind
        Io(Error),        // std::io::Error
        Custom,
    }

    // Error 定義方式不變，但是所引用的 ErrorKind 是我們擴充過的
    pub struct Error(pub ErrorKind, _);

    // Result 定義方式也不變，但是所引用的 Error 是我們擴充過的
    type Result<T> = Result<T, Error>;

    // ResultExt 也不變
    pub trait ResultExt<T, E> {
        fn chain_err<F, EK>(self, callback: F) -> Result<T, Error>
            where F: FnOnce() -> EK, EK: Into<ErrorKind>;
    }


範例三 - 客製化錯誤輸出
------------------------------

.. code-block:: rust

    #[macro_use]
    extern crate error_chain;

    mod errors {
        error_chain! { }
    }

    use errors::*;

    fn run() -> Result<()> {
        use std::fs::File;

        File::open("not_exisit")
             .chain_err(|| "unable to open 'not_exisit' file")?;

        Ok(())
    }

    fn main() {
        // $ RUST_BACKTRACE=1 cargo run
        // error: unable to open 'not_exisit' file
        // caused by: No such file or directory (os error 2)
        // backtrace: stack backtrace:
        //     ...

        if let Err(ref e) = run() {
            println!("error: {}", e);

            for e in e.iter().skip(1) {
                println!("caused by: {}", e);
            }

            // The backtrace is not always generated. Try to run this example
            // with `RUST_BACKTRACE=1`.
            if let Some(backtrace) = e.backtrace() {
                println!("backtrace: {:?}", backtrace);
            }

            ::std::process::exit(1);
        }
    }



參考
========================================

* `Rust RFC #0243 Trait-based Exception Handling <https://github.com/rust-lang/rfcs/blob/master/text/0243-trait-based-exception-handling.md>`_
