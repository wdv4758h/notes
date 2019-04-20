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



RustConf 2018 - C2Rust: Migrating Legacy Code to Rust by Per Larsen
===================================================================

:Video: https://www.youtube.com/watch?v=WEsR0Vv7jhg

介紹 `C2Rust <https://github.com/immunant/c2rust>`_
的架構和能力，
不錯的簡介。


C2Rust 是把 C 程式碼 Transpiling 成 Rust 程式碼的工具，
目前轉換出來會是使用底層功能操作的程式碼，
並不會像是一般人會寫出的 Rust 程式碼，
但是已經有不錯的轉換效果。


如果 C 程式碼有使用 goto 的話會進行 Reloop，
把 goto 的程式碼轉換成一般的 loop 程式碼，
這塊的演算法源自 Emscripten 內的設計。


另外 C2Rust 還支援
`Cross Checking <https://github.com/immunant/c2rust/blob/master/docs/cross-check-tutorial.md>`_ ，
比較原本 C 程式碼的實做和轉換成的 Rust 的版本做比較，
確認兩者的行為一樣。
這方面目前有兩種作法：

* MVEE-based (Multi-Variant Execution Environment)
    - 執行期間比較、檢查
    - `使用 ReMon <https://github.com/stijn-volckaert/ReMon>`_
* log-based
    - 執行完之後比對蒐集到的 log


在轉換成使用低階 API 的 Rust 程式碼之後，
接著可以進行重構來改善程式碼品質，
讓程式碼更像真正的 Rust 程式設計師會寫出來的樣子。
這邊有兩種作法：

* 自動化重構工具
* 手動重寫


C2Rust 目前是運作於前處理將 C macro 展開之後，
所以無法保持原本的 C macro 功能，
這意味著一些平台特定的資訊可能會被寫進轉換出來的程式碼，
而且 C macro 是針對 token 的字串取代，
跟 Rust macro 操作 AST 不同，
無法直接轉換。


總結是要把所有 C 程式碼完全轉換成 Rust 程式碼有難度，
目前可以達到一定程度，
但是仍然有一些難以轉換的功能。



RustConf 2018 - Rust and the Web Platform: A Rookie’s Guide by Sarah Meyer
==========================================================================

:Video: https://www.youtube.com/watch?v=EDoNNFWIRrw


沒有太深的技術內容，
算是入門介紹，
從網頁歷史發展到現在 Rust 的 WebAssembly 相關社群。

* Web
* Java Applet
* Flash
* JavaScript
* asm.js
* NaCI
* WebAssembly
* Rust & WebAssembly
    - wasm-bindgen
    - wasm-pack



RustConf 2017 - Improving Rust Performance Through Profiling and Benchmarking by Steve Jenson
=============================================================================================

:Video: https://www.youtube.com/watch?v=hTHp0gjWMLQ

不錯的演講，
介紹 Rust 既有的效能測試工具，
點出幾個會造成效能損失的常見 Rust 程式碼撰寫問題，
介紹不同的效能測試工具，
以及如何從中觀察出問題點並提升效能。

講者在 Linkerd 工作，
在實做自家 TCP load balancer -
`linkerd-tcp <https://github.com/linkerd/linkerd-tcp>`_ 時，
想了解整體效能狀況和瓶頸，
因此實做了 `Tacho <https://github.com/linkerd/tacho>`_ ，
但是演講中主要是針對其他人可以廣泛採用的知識做講解。


造成效能差的可能原因：

* memory stalls
    - register: 0.5 nanoseconds
    - last-level cache: 10 nanoseconds
    - ram: 100 nanoseconds
    - 參考 `Latency numbers every programmer should know <https://people.eecs.berkeley.edu/~rcs/research/interactive_latency.html>`_
* lock contention
    - spin lock
    - blocking wait
* CPU utilization
    - can hide memory latency (slow instructions)
    - can hide lock contention (spin loops)
    - idlenss is often counted as useful work
        + 90% utilized can also mean 80% waiting for RAM or disk

Rust 程式撰寫時的注意要點：

* 避免使用 ``#[derive(Copy)]`` 在巨大的 struct
    - Copy 在一開始時可能很方便
    - 使用過度就會造成消耗過多記憶體，也會花費效能在處理記憶體
    - 常見狀況是一開始資料結構很小，但是隨著開發長大，最後變成瓶頸
* 避免不斷地使用 ``clone()`` ，尤其是在 loop 內
    - ``clone()`` 雖然可以快速地滿足 borrow checker，但是會過度使用記憶體
    - 幸運的是 ``clone()`` 不管是在程式碼中還是在 Profiling 中都容易發現
* 標準函式庫中的 HashMap 的預設 hasher 並不是效能最佳的
    - 預設的 hasher 是針對安全性選擇的，會防止 DoS 攻擊
    - 如果有其他使用情境不需要特別的安全性，那就可以選擇其他更有效率的 hasher
    - 在 Rust 社群中算是很多人知道的取捨，但是對於新進來的 Rust 程式設計師可能會感到驚訝
    - 第三方有眾多替代方案，例如 FnvHasher
* 避免在 ``expect()`` 內使用成本高的預設值
    - 例如使用預設值時都會重新計算一次或是 format 一次，如果有很多狀況的話就會造成很多效能損失
* 如果知道資料量的話事先為 Vec 準備好大小


效能測量工具：

* Mac
    - Instruments
    - ``cargo bench``
    - ``cargo benchcmp``
* Linux
    - ``perf``
    - FlameGraphs
    - VTune
    - ``cargo bench``
    - ``cargo benchcmp``


其他：

* Intel Performance Counters
* Instructions Per Cycle
    - 每個 cycle 可以處理多少指令
    - < 1.0 通常表示 memory stalled
    - > 1.0 通常表示  instruction stalled
    - 三個核心的理論最大值為 3.0
* Intel PMCs
    - Instruments 有支援
    - 功能
        + Counter
        + Recording Options
        + Events
        + Can create formula from PMCs

Perf 是 Linux kernel 支援的效能測試工具，
Perf 是 sampling profiler，
可以設定 sampling rate，
支援 scheduler 分析和 I/O 及 Network subsystems，
效能測試的成本也很低。
範例：

.. code-block:: sh

    $ sudo perf stat target/release/examples/multithread
    $ sudo perf stat -e L1-dcache-misses,L1-dcache-loads target/release/examples/multithread


FlameGraphs 是藉由取樣什麼正在 CPU 上執行而製成的圖表，
可以蒐集成 call stack 的變化，
讓程式設計師對於程式的模樣有概念，
圖表上的顏色沒有特別意義，
滑鼠停留可以顯示更多功能，
藉由觀察哪些函式佔了最多時間可以找到瓶頸，
很適合於長時間執行的程式，
但是需要 symbols。


VTune 是 Intel 開發出來的工具，
開源專案開發者可以免費使用，
內容詳細、功能多樣，
也可以找出 "Remote Cache" 的問題。


.. code-block:: sh

    # 找到 Remote Cache 問題後使用 taskset 指定使用特定 CPU 後可以得到效能提
    # 9.3 seconds -> 3.8 seconds
    $ sudo perf stat -e L1-dcache-misses,L1-dcache-loads taskset -c 1 target/release/examples/multithread


總結：

* 效能問題不好了解
* 需要很多觀察以及經驗
* Instructions Per Cycle 是不錯的效能測量方法之一



Percy: Isomorphic Web Apps with Rust + WebAssembly — Chinedu Francis Nwafili
============================================================================

:YouTube: https://www.youtube.com/watch?v=M6RLvGqQU10
:GitHub: https://github.com/chinedufn/percy/
:文件: https://chinedufn.github.io/percy/


不錯的 Percy 展示，
快速了解 Percy 是如何用 Rust + WebAssembly 來撰寫網頁前端，
以及數個方便的 macro 是如何整合進開發流程。
