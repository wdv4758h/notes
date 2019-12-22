========================================
Regex (Regular Expression)
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



Regex 相關應用
========================================

* ripgrep
* fd



其他實做比較
========================================

* PCRE
* PCRE-DFA
* PCRE-sljit
* Google RE2
* Go Regexp
* Oniguruma
* TRE
* sregex
* Thompson NFA
* Perl
* Python
* Ruby
* Henry Spencer's regex library
* Hyperscan



參考
========================================

Repos
------------------------------

* `regex <https://github.com/rust-lang/regex>`_
* `fancy-regex <https://github.com/fancy-regex/fancy-regex>`_
    - 想要嘗試混合的實做，支援 NFA 實做無法達成的功能，同時盡量利用 NFA 實做的效能
* `Hyperscan <https://github.com/01org/hyperscan>`_
    - Intel 的 regex engine，使用 SIMD 加速
    - `Paper: Hyperscan: A Fast Multi-pattern Regex Matcher for Modern CPUs <https://branchfree.org/2019/02/28/paper-hyperscan-a-fast-multi-pattern-regex-matcher-for-modern-cpus/>`_
* `RE2 <https://github.com/google/re2>`_
    - Google 的 regex engine


其他
------------------------------

* `Wikipedia - String searching algorithm <https://en.wikipedia.org/wiki/String_searching_algorithm>`_
* `Wikipedia - Aho-Corasick algorithm <https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm>`_
* `演算法筆記 - Multi-Pattern String Matching: Aho-Corasick Algorithm <http://www.csie.ntnu.edu.tw/~u91029/StringMatching.html#4>`_
* `CppCon 2018: Compile Time Regular Expressions <https://cppcon2018.sched.com/event/FnKa/compile-time-regular-expressions>`_
