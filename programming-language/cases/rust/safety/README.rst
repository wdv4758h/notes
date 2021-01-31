========================================
Rust x 安全性
========================================


.. contents:: 目錄


介紹
========================================

目前 Rust 在這塊主要是
`Rust Secure Code Working Group <https://www.rust-lang.org/governance/wgs/wg-secure-code>`_ 負責。
Rust Secure Code Working Group 維護了
`RustSec Advisory Database <https://rustsec.org>`_ ，
內容就好像 CVE (Common Vulnerabilities and Exposures) 一樣，
會說明有問題的套件、原因、受影響的版本、相關建議等等。

可以透過 RustSec 的 `cargo-audit <https://github.com/RustSec/cargo-audit>`_ 來檢查專案的 Cargo.lock，
如果裡面含有 Advisories 的話就會被抓出來。
除了 cargo-audit 之外，Embark Studios 的 `cargo-deny <https://github.com/EmbarkStudios/cargo-deny>`_
也有支援這個檢查。

Advisories 內可能的種類：

* 會造成未定義行爲
* 會造成不當的記憶體操作
* 套件已經太久沒有維護
* 其他 ...


除此之外，
也有針對 unsafe 使用的檢查工具
`cargo-geiger <https://github.com/rust-secure-code/cargo-geiger>`_ ，
可以掃過所有相依套件列出有使用 unsafe 的部分。



放入 CI 自動化
========================================

* `cargo-audit with Github Actions <https://github.com/actions-rs/audit-check>`_



Fuzzy 檢查
========================================

除了前面的已回報的檢查外，
也有透過 Fuzzy Testing 來戳套件的檢驗，
主要的工具在 `Rust Fuzzing Authority <https://github.com/rust-fuzz>`_ 組織內。

可以在 `Trophy Case <https://github.com/rust-fuzz/trophy-case>`_
看到過去挖出的問題含種類。



參考
========================================

* [GitHub] `Rust Secure Code Working Group <https://github.com/rust-secure-code>`_
* [GitHub] `RustSec <https://github.com/RustSec>`_
* [2020] `cargo-audit v0.11 Introducing the 'fix' feature, yanked crate detection, and more | Inside Rust Blog <https://blog.rust-lang.org/inside-rust/2020/01/23/Introducing-cargo-audit-fix-and-more.html>`_
* `Rust Safety Dance <https://github.com/rust-secure-code/safety-dance>`_
    - 討論 unsafe 程式碼檢查的 repo
    - 有建議的檢查流程
    - 可以在 issue 裡徵求特定套件的 review，並且討論裡面的 unsafe 是否是合理使用，以及能否在不失去任何功能和效能的情況下換成 safe 程式碼
    - 有一些案例記錄在裡面

其他：

* `Rustig! - tool to detect code paths leading to Rust's panic handler <https://github.com/Technolution/rustig>`_
* `overflower - Rust compiler plugin and support library to annotate overflow behavior <https://github.com/llogiq/overflower>`_
* `Minimum Safe Abstractions — Llogiq on stuff <https://llogiq.github.io/2019/08/01/unsafe.html>`_
