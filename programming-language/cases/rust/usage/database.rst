========================================
Database
========================================


.. contents:: 目錄


ORM
========================================

Diesel
------------------------------

:Site: http://diesel.rs/
:Repo: https://github.com/diesel-rs/diesel


Diesel 是 Rust 的一個 ORM Framework，
提供方便的 derive 可以幫 struct 產生需要的 SQL Query。


* schema
    - 用於在編譯時期檢查 SQL query 是否有問題
    - 可以自己用 ``table!`` 定義
    - 可以讓 Diesel 連到資料庫後用 ``print-schema`` 或 ``infer_schema!`` 自動產生使用 ``table!`` 的程式碼



Database Connection Pool
========================================

r2d2
------------------------------

:Repo: https://github.com/sfackler/r2d2


r2d2 是 Rust 的一個資料庫連線 Pool 的 Library，
藉此可以避免在每次操作時重複建立連線。



Database 實做
========================================

sled - modern embedded database
-------------------------------

:Repo: https://github.com/spacejam/sled


相關專案：

* `MeiliDB <https://github.com/meilisearch/MeiliDB>`_
    - A full-text search database using sled


TiKV - distributed transactional key-value database
---------------------------------------------------

:Site: https://tikv.org/
:Repo: https://github.com/tikv/tikv

TiKV 本來是 PingCAP 公司內的專案，
設計上參考了 Google Spanner 和 HBase，
但是加入更多管理和相依套件考量。

TiKV 於 2019 年 5 月加入
CNCF (Cloud Native Computing Foundation)，
成為 CNCF 旗下扶持的專案。



Database Management UI
========================================

* `Diwata - database interface for PostgreSQL <https://github.com/ivanceras/diwata>`_
    - written in Rust


其他語言實做：

* `DBeaver - Universal Database Tool <https://dbeaver.io/>`_
    - written in Java
    - [GitHub] `DBeaver <https://github.com/dbeaver/dbeaver>`_
    - `DBeaver 企業版 <https://dbeaver.com/>`_
* `pgAdmin <https://www.pgadmin.org/>`_
    - written in Python



參考
========================================

Repos
------------------------------

* `r2d2 <https://github.com/sfackler/r2d2>`_
* `Diesel <https://github.com/diesel-rs/diesel>`_
* `Barrel - A database schema migration builder <https://github.com/spacekookie/barrel>`_
* `sled - modern embedded database <https://github.com/spacejam/sled>`_
    - [HN] `An embedded database written in Rust <https://news.ycombinator.com/item?id=17170733>`_
