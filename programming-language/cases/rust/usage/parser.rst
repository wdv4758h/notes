========================================
Parser
========================================


.. contents:: 目錄


介紹
========================================

Rust 生態圈內的 Parser library 有很多，
目前最大的是 Nom，
其他知名的還有 Pest、Combine、PEG、... 等等。


Parser libraries：

* `Nom <https://github.com/Geal/nom>`_
* `Pest <https://github.com/pest-parser/pest>`_
* `Combine <https://github.com/marwes/combine>`_
* `PEG <https://github.com/kevinmehall/rust-peg>`_
* `Oak - typed parser generator with PEG <https://github.com/ptal/oak>`_
* `LALRPOP - LR(1) parser generator <https://github.com/lalrpop/lalrpop>`_
* `Parsell - LL(1) streaming parser combinator <https://github.com/asajeffrey/parsell>`_


目前個人覺得狀況是：

* Nom：      是 Parser Combinator，最成熟，支援最多功能，效能良好
* Combine：  是 Parser Combinator，因採用 Trait 實做語法比 Nom 好看
* Pest：   不是 Parser Combinator，語法乾淨（PEG）


Parser Library 效能比較：

* `parser benchmarks <https://github.com/Geal/parser_benchmarks>`_



Nom
========================================

:Repo: https://github.com/Geal/nom


Nom 是一個 Parser Combinator 的 library，
支援 string/byte/bit 的處理、streaming parser、zero-copy，
而且善用 Rust 的強型別和記憶體處理達到良好的效能。

Nom 已經具有眾多 parser 實做，
包含影音格式、壓縮檔、純文字設定檔、程式語言等等都有。
算是目前 Rust 最成熟的 parser framework。

Nom 早期因為 Rust 的能力還不夠強，
所以設計透過 macro 來處理，
後來在 Nom 5 的時候整個重寫，
先前功能都可以透過函式的方式使用，
而這次改寫也有不小的效能改進。


參考：

* `nom 5 is here <http://unhandledexpression.com/general/2019/06/17/nom-5-is-here.html>`_
* `PEG Parser Generator based on Nom <https://github.com/rust-bakery/nom-peg>`_



Pest
========================================

:Repo: https://github.com/pest-parser/pest


Pest 使用 PEG grammar，
藉此提供可讀性高的語法。


* `List of parsers and combinators <https://github.com/Geal/nom/blob/master/doc/choosing_a_combinator.md>`_
* `No, pest is not faster than nom <https://unhandledexpression.com/general/2018/10/04/no-pest-is-not-faster-than-nom.html>`_
* Pest v.s. Nom
    - Grammar 可讀性比 Nom 高很多



Combine
========================================

:Repo: https://github.com/marwes/combine


Combine 是借鏡 Haskell 的 Parsec 所作的 parser combinator library，
所以會以 LL(1) parser 為預設。


* `Combine v.s. Nom <https://github.com/Marwes/combine/issues/73>`_
    - 明顯差異是 Nom 大量使用 Macro，而 Combine 大量使用 Trait
    - Combine 沒有專注在 byte-level parser 和 bit-level parser
    - Nom 支援一些狀態機的操作，但是 Combine 沒有



Rust PEG
========================================

:Repo: https://github.com/kevinmehall/rust-peg



Parser 實做
========================================

* `Parsers written with Nom <https://github.com/Geal/nom#parsers-written-with-nom>`_
* `Projects using Pest <https://github.com/pest-parser/pest#projects-using-pest>`_
* `Parsers written in Combine <https://github.com/marwes/combine#parsers-written-in-combine>`_

* EcmaScript
    - `RESS (Rusty EcmaScript Scanner) <https://github.com/FreeMasen/RESS>`_
        + `RESS 0.7.0! <https://wiredforge.com/blog/ress-7/>`_
* Org Mode
    - `org-rs <https://github.com/org-rs/org-rs>`_
* SQL
    - `sqlparser <https://github.com/andygrove/sqlparser-rs>`_



參考
========================================

* `lexical <https://github.com/Alexhuszagh/rust-lexical>`_
    - number <-> string
    - 支援 std 和 no_std

* `Safe and fast parsers with nom and Rust <http://dev.unhandledexpression.com/slides/strangeloop-2015/>`_
    - `YouTube - Safe and fast parsers with nom and Rust <https://www.youtube.com/watch?v=EXEMm5173SM>`_
* `FOSDEM 2018 - Demystifying Rust parsing - Language parsing and automatic binding generation <https://fosdem.org/2018/schedule/event/rust_demystifying_parsing/>`_

* `FP in Scala - Chapter 9: Parser combinators <https://github.com/fpinscala/fpinscala/wiki/Chapter-9:-Parser-combinators>`_
* `Wikipedia - Type Length Value <https://en.wikipedia.org/wiki/Type-length-value>`_
