========================================
Rust x Regex (Regular Expression)
========================================


.. contents:: 目錄


介紹
========================================

Rust 官方有 `Regex Engine <https://github.com/rust-lang/regex>`_ 的實做，
設計上是類似 Google 的 RE2 而不是 PCRE，
也就是採用 Finite Automata 的設計而不是使用 Backtracking 來實做，
藉此來提供線性的時間複雜度。
Rust 的 regex 實做還參考了 Intel 的 Hyperscan 引入部份 SIMD 加速。
實際應用上也在 ripgrep 中展現了一定程度的優勢。

在 Computer Language Benchmarks Game 的
`regex-redux <https://benchmarksgame-team.pages.debian.net/benchmarksgame/performance/regexredux.html>`_
項目中也展現不錯的速度。

在支援 Lookaround 和 Backtracking 功能方面，
另外有 `fancy-regex <https://github.com/fancy-regex/fancy-regex>`_ 嘗試混合不同實做，
當使用的正規表達不包含 Lookaround 和 Backtracking 需求時，
就採用 DFA/NFA 實做，
否則採用 Backtracking 實做。
（ `syntect <https://github.com/trishume/syntect#pure-rust-fancy-regex-mode-without-onig>`_
有支援使用 fancy-regex 作爲引擎，
在測試資料內，行爲上跟 Oniguruma 相同，但是效能大約只有一半，還有待進一步改善）

使用 NFA 實作的好處是可以控制最差的狀況，
但是壞處是不能支援特定的操作（如 Lookaround 和 Backtracking）。
使用 Backtracking 實作的好處是可以支援更豐富的操作，
壞處是不能控制最差的狀況，
如果提供給使用者的話，
有可能成爲 DoS 攻擊點。



效能比較
========================================

* `Rust regex 的效能測試紀錄 <https://github.com/rust-lang/regex/tree/master/bench/log/07>`_
    - 用 cargo-benchcmp 可以進行比對，除了少部份較 RE2 慢外，Rust regex 在大部分測項中都有大幅的效能提升



DFA
========================================



NFA
========================================



Aho-Corasick
========================================

`Aho-Corasick <https://github.com/BurntSushi/aho-corasick>`_
是一個搜尋子字串的演算法，
可以一次搜尋多個子字串，
搜尋複雜度為 ``O(n + p + m)`` ，
``n`` 為字串長度，
``p`` 為要搜尋的子字串的總共長度，
``m`` 為匹配到的次數。



Teddy SIMD Multiple Substring Searcher
========================================

Teddy 是利用 SIMD 優化過的子字串搜尋演算法，
源自於 Intel 的 Hyperscan 專案，
可以提供執行效能更加的方案。

* https://github.com/rust-lang/regex/blob/master/src/simd_accel/teddy128.rs



Compile Time Regex
========================================



其他實做比較
========================================

* `PCRE2 <https://vcs.pcre.org/pcre2/code/trunk/>`_
* PCRE2-DFA
* PCRE2-sljit
* `RE2 (Google) <https://github.com/google/re2>`_
* Go Regexp
* `Oniguruma <https://github.com/kkos/oniguruma>`_
* `TRE <https://github.com/laurikari/tre>`_
* sregex
* Thompson NFA
* Perl
* Python
* Ruby
* Henry Spencer's regex library
* `Hyperscan (Intel) <https://github.com/01org/hyperscan>`_
    - 使用 SIMD 加速
    - `Paper: Hyperscan: A Fast Multi-pattern Regex Matcher for Modern CPUs <https://branchfree.org/2019/02/28/paper-hyperscan-a-fast-multi-pattern-regex-matcher-for-modern-cpus/>`_



參考
========================================

* `regex <https://github.com/rust-lang/regex>`_
* `fancy-regex <https://github.com/fancy-regex/fancy-regex>`_
    - 想要嘗試混合的實做，支援 NFA 實做無法達成的功能，同時盡量利用 NFA 實做的效能
* `regex-performance - performance comparison of regular expression engines <https://github.com/rust-leipzig/regex-performance>`_
* `regexm - Rust macro for writing regex pattern matching <https://github.com/TaKO8Ki/regexm>`_
* `grex - CLI for generating regular expressions from user-provided test cases <https://github.com/pemistahl/grex>`_
* `Rustexp - online Rust regular expression editor & tester <https://rustexp.lpil.uk>`_

* `Wikipedia - String searching algorithm <https://en.wikipedia.org/wiki/String_searching_algorithm>`_
* `Wikipedia - Aho-Corasick algorithm <https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm>`_
* `演算法筆記 - Multi-Pattern String Matching: Aho-Corasick Algorithm <http://www.csie.ntnu.edu.tw/~u91029/StringMatching.html#4>`_
* `CppCon 2018: Compile Time Regular Expressions <https://cppcon2018.sched.com/event/FnKa/compile-time-regular-expressions>`_
* `String Matching with Multicore CPUs: Performing Better with the Aho-Corasick Algorithm <https://arxiv.org/pdf/1403.1305.pdf>`_
