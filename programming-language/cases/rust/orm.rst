========================================
ORM
========================================


.. contents:: 目錄


Diesel
========================================

特色：

* 在編譯時期就抓到一些資料庫的 runtime error 問題
    - 程式碼的 model 是否和資料庫的 schema 吻合
    - 存取現在 query 的 table 所沒有的資料
    - nullable 問題
    - ... （可以看 `diesel/diesel_compile_tests/tests/compile-fail/ <https://github.com/diesel-rs/diesel/tree/master/diesel_compile_tests/tests/compile-fail>`_ 來知道更多狀況）
* 效能跟直接寫 SQL 語法一樣好
* 容易擴充
* 目前支援 SQLite、MySQL、PostgreSQL


Infer Schema
------------------------------

Diesel 可以用 ``infer_schema!`` 根據資料庫的現有 schema 來生出需要的 DSL，
藉此馬上就可以得到能跟資料庫互動的界面，
但是這會需要在編譯時期有可以參考的資料庫，
因此會建議用 ``diesel print-schema`` 事先把 DSL 生好後存起來，
之後重複直接使用。


假設 SQLite 資料庫是以這樣的語法建立的：

.. code-block:: sql

    CREATE TABLE users (
      id INTEGER PRIMARY KEY NOT NULL,
      name VARCHAR NOT NULL,
      hair_color VARCHAR
    )


那採用編譯時期產生的程式碼會長這樣：

.. code-block:: rust

    infer_schema!("dotenv:DATABASE_URL");


事先產生：

.. code-block:: sh

    $ env DATABASE_URL=test.sqlite diesel print-schema
    table! {
        users (id) {
            id -> Integer,
            name -> Text,
            hair_color -> Nullable<Text>,
        }
    }


Migration
------------------------------

.. code-block:: sh

    $ mkdir -p migrations
    $ env DATABASE_URL=test.sqlite diesel migration list
    Migrations:

    $ env DATABASE_URL=test.sqlite diesel migration initial
    Creating migrations/20170806062219_initial/up.sql
    Creating migrations/20170806062219_initial/down.sql

    $ cat > migrations/20170806062219_initial/up.sql
    CREATE TABLE users (
      id INTEGER PRIMARY KEY NOT NULL,
      name VARCHAR NOT NULL,
      hair_color VARCHAR
    )

    $ cat > migrations/20170806062219_initial/down.sql
    DROP TABLE users

    $ env DATABASE_URL=test.sqlite diesel migration list
    Migrations:
      [ ] 20170806062219_initial

    $ env DATABASE_URL=test.sqlite diesel migration pending
    true

    $ env DATABASE_URL=test.sqlite diesel migration run
    Running migration 20170806062219

    $ env DATABASE_URL=test.sqlite diesel migration list
    Migrations:
      [X] 20170806062219_initial

    $ env DATABASE_URL=test.sqlite diesel migration revert
    Rolling back migration 20170806062219


    $ env DATABASE_URL=test.sqlite diesel migration run
    Running migration 20170806062219
    $ env DATABASE_URL=test.sqlite diesel migration redo
    Rolling back migration 20170806062219
    Running migration 20170806062219


CLI
------------------------------



參考
========================================

* `Diesel - A safe, extensible ORM and Query Builder for Rust <https://github.com/sgrif/diesel>`_
* `Announcing Diesel — A Safe, Extensible ORM and Query Builder for Rust <https://medium.com/@sgrif/announcing-diesel-a-safe-extensible-orm-and-query-builder-for-rust-fdf57966a16c>`_
* `Grokking Diesel <https://hackernoon.com/grokking-diesel-652cb8886a63>`_
