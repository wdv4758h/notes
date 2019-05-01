========================================
Search Engine
========================================


.. contents:: 目錄


Tantivy, inspired by Lucene
========================================

:Repo: https://github.com/tantivy-search/tantivy


Tantivy 是參考 Lucene 設計而用 Rust 寫成的搜尋引擎，
內部使用了 FST 的結構做搜尋，
在眾多測試項目中已經開始顯現比 Lucene 好的效能。


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

:Repo: https://github.com/toshi-search/Toshi/



Sonic - fast, lightweight, schema-less search backend
=====================================================

:Repo: https://github.com/valeriansaliou/sonic



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
