========================================
Rust Vim Plugin
========================================

Racer - code completion for Rust
========================================

`racer 連結 <https://github.com/phildawes/racer>`_

基本介紹
------------------------------

racer 是一個提供 Rust 程式碼補完功能給各式編輯器和 IDE 的工具，
在安裝並且提供 Rust 程式碼後，
可以使用 CLI 上的工具 Query 補完的推薦，
除此之外可以接到其他編輯器上整合使用（例如 Vim）。

安裝
------------------------------

安裝 racer ：

.. code-block:: sh

    rustup run stable cargo install racer


下載 Rust Source Code ：

.. code-block:: sh

    mkdir -p ~/.multirust/src/
    cd ~/.multirust/src/
    wget https://static.rust-lang.org/dist/rustc-1.8.0-src.tar.gz
    tar xvf rustc-1.8.0-src.tar.gz
    ln -s rustc-1.8.0 stable


設定環境變數：

.. code-block:: sh

    set -g -x RUST_SRC_PATH "$HOME/.multirust/src/stable/src"
    set -g -x CARGO_HOME "$HOME/.cargo"
    set -g -x RACER "$CARGO_HOME/bin/racer"


測試
------------------------------

.. code-block:: sh

    racer complete std::io::B



Vim Racer Plugin
========================================

使用 vim-plug ：

.. code-block:: vim

    Plug 'racer-rust/vim-racer'

    """"""""""""""""""""""""""""""""""""""""

    set hidden
    let g:racer_cmd=$RACER

安裝： ``:PlugInstall``

使用：

* [Insert Mode] ``C-x C-o`` 搜尋補完
* [Normal Mode] ``gd`` go to definition
