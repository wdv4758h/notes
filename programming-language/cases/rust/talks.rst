========================================
Talks
========================================


.. contents:: 目錄


RustConf 2017 - Opening Keynote: Make Productivity a Core Value of Rust
=======================================================================

:Video: https://www.youtube.com/watch?v=COrl851gMTY


Rust 團隊的發展更新，
介紹當初 2017 的規劃，
目前 impl period 的狀況、
語言發展（NLL、impl Trait、const generic、async 等等）、
Libz Blitz 的目標和狀況，
對於 Rust 近期發展和未來走向有很好的說明。



Rust Fest 2017 - Pascal Hertleif - Writing Idiomatic Libraries in Rust
======================================================================

:Video: https://www.youtube.com/watch?v=0zOg8_B71gE
:Slide: https://killercup.github.io/rustfest-idiomatic-libs/index.html#/

非常好的演講，
介紹如何撰寫易於使用的 Rust library，
點出有哪些注意事項和方便的使用方法。


相關資源：

* `Elegant Library APIs in Rust <https://deterministic.space/elegant-apis-in-rust.html>`_
* `Rust API guidelines <https://github.com/rust-lang-nursery/api-guidelines>`_


良好的 library：

* 易於使用
    - 容易上手
    - 容易正確地使用
    - 既有彈性又有良好的效能
* 易於維護
    - 共用的資料結構，讓程式碼容易理解
    - 對新貢獻者友善
    - 良好的測試


::

    Working in libraries instead of executables, and focusing on the consumer of your API, helps you write better code. — Andrew Hobden


容易的開始：

* doc tests：良好的文件 == 良好的測試
    - 從使用者的角度撰寫
    - 把不需要的資訊用 # 藏起來
    - 把干擾使用者理解的前處理程式碼放到別的檔案，使用引入的方式 ``# include!("src/doctest_helper.rs");``
* 專案結構遵從 Cargo 的慣例
    - src/libs
    - src/main.rs
    - src/bin/{name}.rs
    - tests/
    - examples/
    - benches/
* 取得更多編譯錯誤
    - ``#![deny(warnings, missing_docs)]``
    - 使用 Clippy
* 保持小而美的 API 界面
    - 使用者需要學習更少的東西
    - 開發者更易於維護
    - 更少的機會造成不向下相容


::

    Make illegal states unrepresentable — Haskell mantra

::

    The safest program is the program that doesn't compile — ancient Rust proverb

    Manish Goregaokar
    https://twitter.com/ManishEarth/status/843248038139195397


* 避免使用 Stringly Typed APIs
    - Rust 有 enum 可以用，定義清楚支援的選項，不要把界面都用字串選擇
    - 避免： ``fn print(color: &str, text: &str) {}``
    - 改成： ``enum Color { Red, Green, Blue }`` ``fn print(color: Color, text: &str) {}``
* 避免使用 bool 當選項
    - Rust 有 enum 可以用，定義清楚支援的選項，不要把界面都用 bool 做開關
    - 例如： ``enum DisplayStyle { Color, Monochrome }``
* 利用 Builder Pattern 簡化使用者的參數設定
    - 可以檢查並轉換參數
    - 可以設定預設值
    - 可以隱藏內部結構
    - 可以向上相容，內部結構可以改變，但是 Builder 的 API 可以維持
* 讓常用的轉換非常易用
    - 減少繁冗的事前準備，
    - 例如： ``let x: IpAddress = [127, 0, 0, 1].into();``
    - ``std::convert`` 很方便
        + ``AsRef``: reference to reference conversion
        + ``From/Into``: value conversions
        + ``TryFrom/TryInto``: fallible conversions
* 想想標準函式庫會怎麼做
    - 讓使用者覺得用起來跟標準函式庫一樣熟悉
    - 實做常見的 trait
        + Debug, (Partial)Ord, (Partial)Eq, Hash
        + Display, Error
        + Default
        + Serde's Serialize + Deserialize


好用範例：

* 實做 FromStr，讓使用者可以直接使用 ``.parse()`` ，例如 ``"green".parse()``
* 實做 Iterator，讓使用者可以爬過你的資料結構，例如 ``regex::Matches``


更多良好設計：

* Session Types
    - 讓 API 可以處理使用者的設定狀態，編譯時期就擋掉不合理的設定
    - API 呼叫完會根據狀態回傳不同的型別，各個型別接受不同的操作

    .. code-block:: rust

        // 原本
        HttpResponse::new()
                     .header("Foo", "1")
                     .header("Bar", "2")
                     .body("asdasd")
                     .header("Baz", "3")   // 依然可以編譯，但是執行時拒絕

        // 採用 Session Types 的概念
        HttpResponse::new()                // NewResponse
                     .header("Foo", "1")   // WritingHeaders
                     .header("Bar", "2")   // WritingHeaders
                     .body("asdasd")       // WritingBody
                     .header("Baz", "3")   // Error, no method `header` found for type `WritingBody`

* Iterator 是 Rust 的良好能力之一，可以在 zero-cost abstraction 下支援特定的 Functional Programming
    - API 接受 Iterator 而不是特定資料結構，既可以減少不必要的 allocation，也可以支援更多資料結構
    - 避免： ``fn foo(data: &HashMap<i32, i32>) {}``
    - 改成： ``fn foo<D>(data: D) where D: IntoIterator<Item=(i32, i32)> {}``
    - 另外讓資料結構可以接受 FromIterator，藉此使用者可以呼叫 ``.collect()``
    - 例如： ``let x: AddressBook = people.collect();``

* 實做更多擴充的 Trait


簡單範例 - Validation：

.. code-block:: rust

    // 避免：
    // 難以擴充，沒有彈性
    enum Validation {
        Required,
        Unique(Table),
        Min(u64),
        Max(u64),
    }

    // 改成：
    struct Required;
    struct Max(u64);
    struct Min(u64);
    struct Unique(Table);

    trait Validate {
      fn validate<T>(&self, data: T) -> bool;
    }

    // 實做 Validate trait

    // 使用：
    // 搭配 FromStr

    use std::str::FromStr;

    let validations = "max:42|required".parse()?;



FOSDEM 2018 - Donald Whyte - Testing in Rust - A Primer in Testing and Mocking
==============================================================================

:Site: https://archive.fosdem.org/2018/schedule/event/rust_testing_mocking/
:Video: https://www.youtube.com/watch?v=sZ8mF3CBAZE
:Slide-HTML: http://donsoft.io/mocking-in-rust-using-double/
:Slide-PDF: https://archive.fosdem.org/2018/schedule/event/rust_testing_mocking/attachments/slides/2113/export/events/attachments/rust_testing_mocking/slides/2113/testing_in_rust_by_donald_whyte.pdf

簡單地介紹 Rust 官方既有的測試功能（例如 doc test），
接著介紹講者做的測試工具 `double <https://github.com/DonaldWhyte/double>`_ ，
介紹設計目標、功能、範例，
最後列出其他 Mocking 工具。

"test double" 是在測試過程中用於替換部份程式碼的物件或函式，
藉此除去外在影響，
建立穩定可複製的測試過程。

不同種類的 "test double"：

* Stub
* Spy
* Mock
* Fake

藉由 ``double`` 可以製造出實做特定 trait 的資料，
並且可以設定特定輸入回傳特定輸出，
又或者把函式替換成另外測試用的 closure，
最後可以檢查函式是否被呼叫，
以及呼叫的參數是否正確等等。

其他 Mocking 工具：

* `mockers <https://github.com/kriomant/mockers>`_
* `mock_derive <https://github.com/DavidDeSimone/mock_derive>`_
* `galvanic-mock <https://github.com/mindsbackyard/galvanic-mock>`_
* `mocktopus <https://github.com/CodeSandwich/Mocktopus>`_
