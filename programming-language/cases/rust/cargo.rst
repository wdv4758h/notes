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



擴充
========================================

偵測程式碼更動，自動重編
------------------------------

.. code-block:: sh

    # https://github.com/passcod/cargo-watch
    cargo install cargo-watch

    cargo watch
    cargo watch -x check -x test
    cargo watch -x build


把所有相依套件載下來管理
------------------------------

把所有相依套件載下來存，讓編譯可以只在目前專案尋找程式碼，不用去 crates.io 抓

.. code-block:: sh

    # 安裝 cargo-vendor
    # https://github.com/alexcrichton/cargo-vendor
    $ cargo install cargo-vendor

    $ cd some_path_to_the_project
    $ cargo vendor  # 所有套件都會被放在 vendor 資料夾


偵測所有 unsafe 的使用，包含相依套件
------------------------------------

.. code-block:: sh

    # https://github.com/anderejd/cargo-geiger
    cargo install cargo-geiger
