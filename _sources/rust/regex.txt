========================================
Regex (Regular Expression)
========================================


.. contents:: 目錄


介紹
========================================

Rust 官方有 `Regex Engine <https://github.com/rust-lang/regex>`_ 的實做，
設計上是參考 Google 的 RE2 而不是 PCRE，
也就是採用 Finite Automata 的設計而不是使用 Backtracking 來實做，
藉此來提供線性的時間複雜度。



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



Regex 相關應用
========================================

ripgrep
------------------------------



參考
========================================

Repos
------------------------------

* `regex <https://github.com/rust-lang/regex>`_
* `fancy-regex <https://github.com/google/fancy-regex>`_
* `Hyperscan <https://github.com/01org/hyperscan>`_
* `RE2 <https://github.com/google/re2>`_


文章
------------------------------

* `Wikipedia - String searching algorithm <https://en.wikipedia.org/wiki/String_searching_algorithm>`_
* `Wikipedia - Aho-Corasick algorithm <https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm>`_
* `演算法筆記 - Multi-Pattern String Matching: Aho-Corasick Algorithm <http://www.csie.ntnu.edu.tw/~u91029/StringMatching.html#4>`_
