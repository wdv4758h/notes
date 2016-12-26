========================================
把 C 程式轉換成 Rust 程式
========================================


.. contents:: 目錄


範例轉換探討
========================================

Corrode - 自動轉換 C 程式碼為 Rust 程式碼
=========================================

介紹
------------------------------

`Corrode <https://github.com/jameysharp/corrode>`_ 是用 Haskell 寫的轉換工具，
餵入 C 程式碼後會產生 Rust 程式碼。
設計方向是盡量保持程式的行為，
在碰到 C 的 Undefined Behavior 或是 Implementation-defined Behavior 時，
盡量選擇常見的行為。
測試方面，
Corrode 可以使用 `csmith <https://github.com/csmith-project/csmith>`_ 產生的 C 程式碼做測試。
未來希望可以利用 `Software Analysis Workbench <http://saw.galois.com/>`_ 和 SMT Solver 做驗證。

目前 Corrode 還在早期階段，
實做的部份不多，
能轉換的程式碼有限。


編譯、安裝
------------------------------

.. code-block:: sh

    sudo pacman -S ghc
    sudo pacman -S cabal-install

    git clone https://github.com/jameysharp/corrode
    cd corrode
    cabal update            # package list for 'hackage.haskell.org'
    cabal install happy     # parser generator
    cabal install alex      # generating lexical analysers
    cabal install           # 完成後將會有 "~/.cabal/bin/corrode"


使用
------------------------------

.. code-block:: sh

    # 後面加上任何 GCC 可以接受的參數
    # 除了 pre-processor 的參數（例如 -C 和 -D）外
    # 其他參數都會被忽略
    # 藉此可以用 "CC=corrode" 來 hook 到現有的 Build System
    # 如果餵入 "filename.c"，則會產生 "filename.rs"
    corrode -Wall filename.c -I/usr/local/include -lm



自動轉換程式碼架構探討
========================================

驗證
------------------------------

目前從 Corrode 的點子看到可能的驗證架構為：

::

    +--------+    +------------------+
    | Csmith | -> | generated C code |---+
    +--------+    +------------------+   |
                                         +---+
    +---------------------+              |   |
    | hand written C code |--------------+   |
    +---------------------+                  |
                                             |
    +----------------------------------------+
    |
    |          +-------+    +--------------+
    |   +----> | Clang | -> | LLVM bitcode |---------------------------------------+
    |   |      +-------+    +--------------+                                       |
    +---+                                                                          |
        |      +--------------+    +-----------+    +-------+    +--------------+  |
        +----> | *Transpiler* | -> | Rust code | -> | rustc | -> | LLVM bitcode |--+
               +--------------+    +-----------+    +-------+    +--------------+  |
                                                                                   |
    +------------------------------------------------------------------------------+
    |
    |    +-----------------------------------+    +--------------------------------------+
    +--> | SAW (Software Analysis Workbench) | -> | symbolic simulator over LLVM bitcode |---+
         +-----------------------------------+    +--------------------------------------+   |
                                                                                             |
    +----------------------------------------------------------------------------------------+
    |
    |   +------------+    +-------------------+
    +-> | SMT solver | -> | prove equivalence |
        +------------+    +-------------------+



參考
========================================

* `The Software Analysis Workbench <https://saw.galois.com/index.html>`_
