========================================
Web
========================================


.. contents:: 目錄


期望
========================================

* 執行快速
* 資源需求小
* 良好的非同步支援
* 豐富的擴充可以選擇
* 易於整合現有的其他套件，例如 JavaScript 的 framework



Asynchronous I/O
========================================

Standard Library
------------------------------

目前 Rust 的 standard library 還沒加入 asynchronous 的支援，
等後續加入吧 ...

* `Rust - rfcs - Async IO #1081 <https://github.com/rust-lang/rfcs/issues/1081>`_
* `RFC 2033 - experimental coroutines <https://github.com/rust-lang/rfcs/blob/master/text/2033-experimental-coroutines.md>`_


Tokio
------------------------------



Template Engine
========================================



Framework
========================================

Iron
------------------------------


Rocket
------------------------------

:Repo: https://github.com/SergioBenitez/Rocket


Gotham
------------------------------

:Repo: https://github.com/gotham-rs/gotham


Actix Web
------------------------------

:Repo: https://github.com/actix/actix-web



Virtual DOM
========================================

* https://github.com/Pauan/rust-dominator



Web App
========================================

* https://github.com/DenisKolodin/yew



Misc
========================================

* `A standard library for the client-side Web <https://github.com/koute/stdweb>`_
* `A Cargo subcommand for the client-side Web <https://github.com/koute/cargo-web>`_



效能比較 (Benchmarks)
========================================

TechEmpower
------------------------------

* round 16
    - 使用 Docker 把不同 framework 的環境隔離
    - 更換到更新的硬體
    - TCP_NODELAY


目前 Rust 狀況 (round 16)：

* JSON serialization
    - total: 287
    - throughput
        + tokio-minihttp is 2
        + may-minihttp is 15
        + hyper is 16
        + actix-raw is 18
        + actix is 20
        + nickle is 79
    - latency
        + nickle is 1
        + actix-raw is 16
        + actix is 24
* Single query
    - total: 321
    - throughput
        + actix-raw is 17
        + actix-pg is 24
        + actix-diesel is 23
    - latency
        + actix-raw is 140
        + actix-pg is 144
        + actix-diesel is 143
* Multiple queries
    - total: 317
    - throughput
        + actix-raw is 4
        + actix-pg is 9
        + actix-diesel is 12
    - latency
        + actix-raw is 5
        + actix-pg is 8
        + actix-diesel is 14
* Fortunes
    - total: 307
    - throughput
        + actix-raw is 10
        + actix-pg is 14
        + actix-diesel is 16
    - latency
        + actix-raw is 99
        + actix-pg is 111
        + actix-diesel is 113
* Data updates
    - total: 289
    - throughput
        + actix-raw is 5
        + actix-pg is 6
        + actix-diesel is 33
    - latency
        + actix-raw is 4
        + actix-pg is 6
        + actix-diesel is 35
* Plaintext
    - total: 273
    - throughput
        + actix-raw is 1
        + tokio-minihttp is 7
        + hyper is 13
    - latency
        + actix is 1
        + hyper is 2
        + actix-raw is 11



參考
========================================

* `An Opinionated Guide To Rust Web Servers <https://wiki.alopex.li/AnOpinionatedGuideToRustWebServers>`_
* `Are we web yet? Getting there. <http://arewewebyet.com/>`_
* `Rust web framework comparison <https://github.com/flosse/rust-web-framework-comparison>`_
* `Support Rust, create a todobackend implementation <https://users.rust-lang.org/t/support-rust-create-a-todobackend-implementation/1300>`_
* `Todo-Backend - a shared example to showcase backend tech stacks <http://todobackend.com/>`_
