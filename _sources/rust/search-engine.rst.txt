========================================
Search Engine
========================================


.. contents:: 目錄


Tantivy
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



參考
========================================

* `Index 1,600,000,000 Keys with Automata and Rust - Andrew Gallant's Blog <https://blog.burntsushi.net/transducers/>`_
* [Rust] `fst - Finite State Transducers <https://github.com/BurntSushi/fst>`_
* Apache Lucene
* Apache Solr
* Elasticsearch
    - search engine based on Lucene
