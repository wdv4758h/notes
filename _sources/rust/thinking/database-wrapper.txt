========================================
Database Wrapper
========================================

* Common Database Interface
* PEP 0249 -- Python Database API Specification v2.0

::

    +--------+  +----------------+ +----------------------------+
    | ORM    |  | simple program | | other programming language | ...
    +--------+  +----------------+ +----------------------------+
        |             |                          |
        |             |                          |
        |             |                          |
    +----------------------------------------------------------------------+
    | Database Wrapper (as library)                                        |
    +----------------------------------------------------------------------+
        |           |             |  ^                       |
        |           |  general    |  | special ability       |
        |           |             |  v                       |
    +--------+ +---------+ +------------+               +-------+
    | SQLite | | MariaDB | | PostgreSQL |               | MySQL | .....
    +--------+ +---------+ +------------+               +-------+


structure ?

::

    src/
        connector/
            platform/
                sqlite.rs
                mariadb.rs
                ...
            connector.rs
        ...



可參考 repo :

* https://github.com/ivanceras/rustorm
