========================================
Rust x 搜尋引擎 (Search Engine)
========================================


.. contents:: 目錄


Tantivy - full-text search engine library
=========================================

:repo: https://github.com/tantivy-search/tantivy
:benchmark: https://tantivy-search.github.io/bench/


Tantivy 的專案目標是像 Lucene 這樣的搜尋引擎 library，
而不是像 Elasticsearch 這樣的搜尋伺服器，
分散式搜尋也不在專案目標內。
而如同 Elasticsearch 是基於 Lucene，
其他人也可以基於 Tantivy 建立出類似 Elasticsearch 的專案。

Tantivy 參考 Lucene 的設計，
內部使用了 FST 的結構做搜尋，
在衆多測試項目中都已經有比 Lucene 好的效能。

另外效能比較中，
有專案 `PISA (Performant Indexes and Search for Academia) <https://github.com/pisa-engine/pisa>`_ ，
儘管 Tantivy 以及比 Lucene 快，
但是 PISA 的效能更快，
具有更優良的演算法，
是未來學習的對象。


tantivy-cli
------------------------------

官方有提供簡單的 CLI 工具
`tantivy-cli <https://github.com/tantivy-search/tantivy-cli>`_
可以快速地使用。


.. code-block:: sh

    # 建立新的專案
    tantivy new -i myproject

    # 匯入資料
    wget http://fulmicoton.com/tantivy-files/wiki-articles-1000.json
    cat wiki-articles-1000.json | tantivy index -i myproject

    # 搜尋
    tantivy search -i myproject/ -q "taiwan"
    # 開 HTTP API
    tantivy serve -i myproject/
    curl "http://localhost:3000/api/?q=taiwan&nhits=1"



Toshi - based on Tantivy, similar to Elasticsearch
==================================================

:repo: https://github.com/toshi-search/Toshi/



Sonic - fast, lightweight, schema-less search backend
=====================================================

:repo: https://github.com/valeriansaliou/sonic



資料結構
========================================

DAFSA vs Trie
------------------------------

* Trie 只共享 prefix
* DAFSA 會共享所有 common prefix
* DAFSA 跟 Trie 相比可以節省不少記憶體使用，但是不能像 Trie 一樣帶些額外的資訊，
* Trie 到的每個節點的路徑都只有一個，所以可以在節點上附加像是存取頻率之類的資訊或是特定字串的 index



參考
========================================

* `The Definitive Guide to Elasticsearch <https://github.com/elastic/elasticsearch-definitive-guide>`_
* `Index 1,600,000,000 Keys with Automata and Rust - Andrew Gallant's Blog <https://blog.burntsushi.net/transducers/>`_
* [Rust] `fst - Finite State Transducers <https://github.com/BurntSushi/fst>`_
* Apache Lucene
* Apache Solr
* Elasticsearch
    - search engine based on Lucene


* Deterministic Acyclic Finite State Acceptor (FSA) (DAFSA)
    - Ordered Set
        + Deterministic
        + Acyclic
        + Acceptor
* Deterministic Acyclic Finite State Transducer (FST) (DAFST)
    - Ordered Map
        + Deterministic
        + Acyclic
        + Transducer
