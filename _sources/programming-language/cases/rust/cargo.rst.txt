========================================
Cargo
========================================


.. contents:: 目錄



套件安裝
========================================

.. code-block:: sh

    $ cargo install NAME



套件製作
========================================


.. code-block:: sh

    # 安裝 cargo-edit 方便使用
    # https://github.com/killercup/cargo-edit
    $ cargo install cargo-edit

    $ cargo new myproj
    $ cd myproj
    # 把最新版 serde 加入相依套件表中 (Cargo.toml)
    $ cargo add serde



把所有相依套件載下來管理
========================================


.. code-block:: sh

    # 安裝 cargo-vendor
    # https://github.com/alexcrichton/cargo-vendor
    $ cargo install cargo-vendor

    $ cd some_path_to_the_project
    $ cargo vendor  # 所有套件都會被放在 vendor 資料夾
