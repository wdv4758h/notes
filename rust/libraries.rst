========================================
Libraries
========================================

.. contents:: 目錄


html5ever - High-performance browser-grade HTML5 parser
=======================================================

:repo: https://github.com/servo/html5ever
:docs: http://doc.servo.org/html5ever/index.html

Mozilla 的 Servo 專案中的 HTML parser



clap - A full featured, fast Command Line Argument Parser for Rust
==================================================================

:repo: https://github.com/kbknapp/clap-rs
:docs: http://kbknapp.github.io/clap-rs/clap/index.html

目前我慣用的 CLI 參數處理方式，提供大量方便的設定



hyper - An HTTP library for Rust
========================================

:repo: https://github.com/hyperium/hyper
:docs: https://hyperium.github.io/hyper

Rust 生態圈中最大的 HTTP library，
Mozilla 的 Servo 專案在 HTTP 方面也是使用這個 library



log - Logging implementation for Rust
========================================

:repo: https://github.com/rust-lang-nursery/log
:doc: https://doc.rust-lang.org/log/log/index.html

專案目的為提供統一的 logging API，抽象化各 logging 的實作，
libraries 可以用這個 API 來撰寫，
而在使用 libraries 做出執行檔時，
可以選擇適合自己的 logging 實作，
藉此達到統一的 logging 機制。

* libraries：只使用 ``log`` 這個套件
* 執行檔：需選擇要使用的 logging 實作

如果沒提供 logging 實作的話，
會 fallback 回 noop 實作，
此時會忽略所有 log 資訊，
overhead 非常小。

層級（使用時當作 ``println!`` 在使用）：

* error!
* warn!
* info!
* debug!
* trace!
