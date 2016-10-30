========================================
Rust 生態圈 (Rust Ecosystem)
========================================

:目前 Rust Stable 版本: 1.12.0
:日期: 2016-10-08


對於各套件期望的特色：

* 功能豐富
* 執行快速
* 資源需求少
* 執行檔小
* 使用簡單


.. contents:: 目錄


第三方套件平台
========================================

Rust 的第三方套件都會蒐集在 `crates.io <https://crates.io/>`_ ，
而放在上面的套件都可以在 `docs.rs <https://docs.rs/>`_ 找到對應的文件。



CLI 參數處理
========================================

Rust 官方有提供 `getopts <https://github.com/rust-lang-nursery/getopts>`_ library
可以幫助處理 CLI 參數，
但是功能比較基本。
另外第三方有功能比較強的套件，
其中 `docopt <https://github.com/docopt/docopt.rs>`_ 可以直接撰寫 help message 來爬參數，
而 `clap-rs <https://clap.rs/>`_ 則提供多樣化的選擇（Method、Macro、YAML），
並且可以生出 help message、Shell 補完（Bash、Fish）、打錯時的建議。



生物資訊
========================================

目前已經出現針對生物資訊的 library - `Rust-Bio <https://rust-bio.github.io/>`_ ，
已經實做不少格式和演算法的支援，
例如 FASTQ、FASTA、BED，
雖然離完整還有段距離，
但是社群、開發活躍度是可以期待的。



Ethereum (Blockchain)
========================================

Rust 實做的 Ethereum client - `Parity <https://ethcore.io/parity.html>`_
在效能測試上已經是最快的 client 了，
在效能和實用性上都已經足夠成熟。



正規表達式引擎
========================================

Rust 目前有一個半官方的 `regex <https://github.com/rust-lang-nursery/regex>`_ 實做，
實做方法是和 Google 的 RE2 類似的 NFA/DFA 作法，
藉此來保證線性的複雜度，
目前已經有相當的成熟度，
大部分需要的功能都有，
在 `regex-dna <http://benchmarksgame.alioth.debian.org/u64q/performance.php?test=regexdna>`_
效能測試上也有不錯的成績，
但是還有些許改進空間。



FFI
========================================

Rust 目前已經有許多 FFI 的專案出現，
有些成熟度還不夠：

* Node.js: `Neon <https://github.com/rustbridge/neon>`_
    - 提供 API 來撰寫 Node.js Module
* Erlang/Elixir: `Rustler <https://github.com/hansihe/Rustler>`_
    - 提供 API 來撰寫 Erlang NIF (Erlang Navtive Implemented Function) 執行在 BEAM 上
* Python: `rust-cpython <https://github.com/dgrunwald/rust-cpython>`_
    - 在 Rust 中使用 Python 程式
* Ruby: `Ruru <https://github.com/d-unseductable/ruru>`_
    - 提供 API 來撰寫 Ruby Extension
* R: `rustr <https://github.com/rustr/rustr>`_
    - 提供 API 來撰寫 R Extension，API 在 Rust 中執行 R 程式碼
* C: `rusty-cheddar <https://github.com/Sean1708/rusty-cheddar>`_
    - 自動從 Rust 程式碼產生 C Header

* `rusty-binder <https://gitlab.com/rusty-binder/rusty-binder>`_
* `rust-bindgen <https://github.com/Yamakaky/rust-bindgen>`_



科學運算
========================================

目前科學運算相關的套件還沒有像 Python 生態圈那樣充足、蓬勃，
幾個有稍微規模的專案：

* `num <https://github.com/rust-num/num>`_
    - 提供基本的數值型別，例如大數
* `rust-ndarray <https://github.com/bluss/rust-ndarray>`_
    - 提供 N 維 Array 相關的操作、計算
* `nalgebra <https://github.com/sebcrozet/nalgebra>`_
    - 提供基本的線性代數運算
* `rulinalg <https://github.com/AtheMathmo/rulinalg>`_
    - 提供基本的線性代數運算
* `vsop87-rs <https://github.com/Razican/vsop87-rs>`_
    - 提供 VSOP87 演算法來計算星體軌道
* `astro-rust <https://github.com/saurvs/astro-rust>`_
    - 提供基本的天文相關演算法



機器學習
========================================

目前相關的套件還不夠蓬勃，
只有少量的資源，
來 Python 生態圈的 ``scikit-learn`` 還有不少距離，
而且目前沒有像 Python 的 ``numpy`` 那樣統一的資料結構，
發展上有些發散。

* `Leaf <https://github.com/autumnai/leaf>`_
    - 機器學習 Framework，支援 GPU
* `rusty-machine <https://github.com/AtheMathmo/rusty-machine>`_
    - 提供基本的機器學習演算法
* `rustlearn <https://github.com/maciejkula/rustlearn>`_
    - 提供基本的機器學習演算法
* `Rustml <https://github.com/daniel-e/rustml>`_
    - 提供基本的機器學習演算法
* `HAL : Hyper Adaptive Learning <https://github.com/jramapuram/hal>`_
    - 基於 ArrayFire 提供 RNN、LTSM 等演算法



Unicode
========================================

在處理 Unicode 上面，Rust 有許多基本的操作都在 `unicode-rs <https://github.com/unicode-rs>`_ 底下，
其中的

* ``unicode-segmentation`` 會根據 ``Unicode Standard Annex #29`` 來做分割
* ``unicode-width`` 會根據 ``Unicode Standard Annex #11`` 判斷顯示的寬度
* ``unicode-xid`` 會根據 ``Unicode Standard Annex #31`` 判斷是否有 ``XID_Start`` 或 ``XID_Continue`` 屬性
* ``unicode-normalization`` 會根據 ``Unicode Standard Annex #15`` 來組合或拆解文字

其他

* `WTF-8 <https://github.com/SimonSapin/rust-wtf8>`_ - implementation of the WTF-8 encoding
* `Emojicons <https://github.com/jiri/rust-emojicons>`_ - Parse :emoji: notation to unicode representation
* `libucd <https://github.com/sourtin/libucd>`_ - exposing much of the Unicode Character Database
* `unicode-bidi <https://github.com/servo/unicode-bidi>`_ - implements the Unicode Bidirectional Algorithm for display of mixed right-to-left and left-to-right text
* `unicode_names <https://github.com/huonw/unicode_names>`_ - char <-> Unicode character name
* `unicode-categories <https://github.com/swgillespie/unicode-categories>`_ - allows for unicode categories can be queried for characters



雜類
========================================

* `itertools <https://github.com/bluss/rust-itertools>`_
    - 更多 iterator 相關的操作
* `Corrode <https://github.com/jameysharp/corrode>`_
    - Automatic semantics-preserving translation from C to Rust
* `Rust-PHF <https://github.com/sfackler/rust-phf>`_
    - Compile time static maps
* `ripgrep <https://github.com/BurntSushi/ripgrep>`_
    - combines the usability of The Silver Searcher (an ack clone) with the raw speed of GNU grep
* `xsv <https://github.com/BurntSushi/xsv>`_
    - A fast CSV toolkit
* `tokei <https://github.com/Aaronepower/tokei>`_
    - counts the lines of code
* `substudy <https://github.com/emk/substudy/>`_
    - Use SRT subtitle files to study foreign languages



Parallel
========================================

* `rayon <https://github.com/nikomatsakis/rayon/>`_ - data-parallelism by work stealing



Serialization
========================================

* `Serde <https://serde.rs/>`_
* `rustc-serialize <https://github.com/rust-lang-nursery/rustc-serialize>`_



網站開發
========================================

網站相關的部份有 `hyper <http://hyper.rs/>`_ 負責 HTTP 的處理，
HTTP 的實做完整度已經非常充足。



參考
========================================

* `Neon: Node + Rust = 💖 <http://calculist.org/blog/2015/12/23/neon-node-rust/>`_
* `The Rust FFI Omnibus <https://github.com/shepmaster/rust-ffi-omnibus>`_
* `About Rust’s Machine Learning Community <https://medium.com/@autumn_eng/about-rust-s-machine-learning-community-4cda5ec8a790>`_
* `Future updates to the rustup distribution format <https://internals.rust-lang.org/t/future-updates-to-the-rustup-distribution-format/4196>`_

* `Are we game yet? <http://arewegameyet.com/>`_
* `Are we web yet? <http://www.arewewebyet.org/>`_
* `Are we learning yet? <http://www.arewelearningyet.com/>`_
* `Are we (I)DE yet? <https://areweideyet.com/>`_
* `Are we concurrent yet? <http://areweconcurrentyet.com/>`_

* `TechEmpower Framework Benchmarks <https://www.techempower.com/benchmarks/>`_
