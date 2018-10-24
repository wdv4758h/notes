========================================
Parser
========================================


.. contents:: 目錄


Nom
========================================

:Repo: https://github.com/Geal/nom


Nom 是一個 Parser Combinator 的 library，
支援 string/byte/bit 的處理、streaming parser、zero-copy，
而且善用 Rust 的強型別和記憶體處理達到良好的效能。

Nom 已經具有眾多 parser 實做，
包含影音格式、壓縮檔、純文字設定檔、程式語言等等都有。
算是目前 Rust 最成熟的 parser framework。



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



各 parser library 比較
========================================

目前個人覺得狀況是：

* Nom：    是 Parser Combinator，最成熟，支援最多功能，效能良好
* Combine：是 Parser Combinator，因採用 Trait 實做語法比 Nom 好看
* Pest： 不是 Parser Combinator，語法乾淨（PEG）



Parser 效能比較
========================================

* `parser benchmarks <https://github.com/Geal/parser_benchmarks>`_



其他實做
========================================

* `Oak - typed parser generator with PEG <https://github.com/ptal/oak>`_
* `LALRPOP - LR(1) parser generator <https://github.com/lalrpop/lalrpop>`_
* `Parsell - LL(1) streaming parser combinator <https://github.com/asajeffrey/parsell>`_



參考
========================================

* `Safe and fast parsers with nom and Rust <http://dev.unhandledexpression.com/slides/strangeloop-2015/>`_
    - `YouTube - Safe and fast parsers with nom and Rust <https://www.youtube.com/watch?v=EXEMm5173SM>`_
* `FOSDEM 2018 - Demystifying Rust parsing - Language parsing and automatic binding generation <https://fosdem.org/2018/schedule/event/rust_demystifying_parsing/>`_

* `FP in Scala - Chapter 9: Parser combinators <https://github.com/fpinscala/fpinscala/wiki/Chapter-9:-Parser-combinators>`_
* `Wikipedia - Type Length Value <https://en.wikipedia.org/wiki/Type-length-value>`_
