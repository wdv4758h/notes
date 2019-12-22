========================================
Cargo
========================================


.. contents:: 目錄



介紹
========================================

:Repo: https://github.com/rust-lang/cargo



套件安裝
========================================

.. code-block:: sh

    $ cargo install NAME



套件製作
========================================


.. code-block:: sh

    # 安裝 cargo-edit 方便使用
    # https://github.com/killercup/cargo-edit
    $ cargo install cargo-edit

    $ cargo new myproj
    $ cd myproj
    # 把最新版 serde 加入相依套件表中 (Cargo.toml)
    $ cargo add serde

    # 改程式碼
    # ...

    # 釋出到 crates.io
    $ cargo login
    $ cargo publish



其他
========================================

* 自動套用編譯器建議
    - ``cargo fix``
* 偵測程式碼更動，自動重編
    - `cargo watch <https://github.com/passcod/cargo-watch>`_
    - ``cargo watch -x build``
    - ``cargo watch -x check -x test``
* 更多的程式碼檢查
    - `cargo clippy <https://github.com/rust-lang/rust-clippy>`_
* 檢查相依套件是否有已知安全問題
    - `cargo audit <https://github.com/RustSec/cargo-audit>`_
* 偵測所有 unsafe 的使用，包含相依套件
    - `cargo-geiger <https://github.com/anderejd/cargo-geiger>`_
* 效能比較
    - `cargo-benchcmp <https://github.com/BurntSushi/cargo-benchcmp>`_
* 把所有相依套件載下來管理
    - `cargo-vendor <https://github.com/alexcrichton/cargo-vendor>`_
* 檢查相依套件是否太舊
    - `cargo-outdated <https://github.com/kbknapp/cargo-outdated>`_
* 套件的相依和被相依的成長圖
    - `cargo tally <https://github.com/dtolnay/cargo-tally>`_
* 繪製程式的 call graph
    - `cargo-call-stack <https://github.com/japaric/cargo-call-stack>`_
* 把 ``#[derive]`` 展開
    - `cargo-expand <https://github.com/dtolnay/cargo-expand>`_
* 計算產生的 LLVM IR 量
    - `cargo-llvm-lines <https://github.com/dtolnay/cargo-llvm-lines>`_
* 修改 ``[replace]`` 內來替換掉特定相依套件
    - `cargo-edit-locally <https://github.com/alexcrichton/cargo-edit-locally>`_
* 清理 Cargo 產生的編譯檔案
    - `cargo-sweep <https://github.com/holmgr/cargo-sweep>`_
* 分析 binary 內誰佔的空間比較多
    - `cargo-bloat <https://github.com/RazrFalcon/cargo-bloat>`_
* 找出各相依套件的 issues 幫忙解決
    - `cargo-contribute <https://github.com/Xion/cargo-contribute>`_
* 分析特定函式的 Assembly
    - `cargo-asm <https://github.com/gnzlbg/cargo-asm>`_
* 管理 Cargo 的 cache
    - `cargo-cache <https://github.com/matthiaskrgr/cargo-cache>`_
* 列出套件的樹狀表
    - `cargo-modules <https://github.com/regexident/cargo-modules>`_
* 更新時檢查相依套件的程式碼更動
    - `cargo-review-deps <https://github.com/ferrous-systems/cargo-review-deps>`_
* 檢查是否能夠支援 no_std
    - `cargo-nono <https://github.com/hobofan/cargo-nono>`_



參考
========================================

* `crate-ci <https://crate-ci.github.io/>`_
* `cargo-local-serve - server a local, offline crates.io <https://gitlab.com/est/cargo-local-serve>`_
