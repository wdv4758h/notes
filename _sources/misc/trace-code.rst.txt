========================================
Trace Code
========================================


.. contents:: 目錄


功能
========================================

* 從使用跳到定義（Jump to Definition 或 Go to Definition）
* 從定義跳到使用（Find Caller）
* 列出目前檔案所有函式和 Class（List of Function and Class）
* 打開特定函式和 Class 所在的檔案（Open Specific Function or Class's File）



Universal Ctags
========================================

Universal Ctags 是 ctags 的分支之一，
現在已經支援許多語言，
可以用 ``ctags --list-languages`` 來看支援哪些語言，
另外可以用 ``ctags --list-kinds`` 來看各語言支援的功能。

Universal Ctags 除了可以各語言的 Tags 檔案供編譯器快速尋找外，
還可以支援 Vim 的 Omni Completion 來提供補完功能。


安裝
------------------------------

.. code-block:: sh

    # Arch Linux 內的 ctags 為原版的 ctags
    # 目前要裝 Universal Ctags 要去 AUR
    $ yaourt -S universal-ctags-git


使用
------------------------------

在專案的根目錄執行指令產生檔案：

.. code-block:: sh

    # 爬現在目錄下的檔案
    $ ctags -R

    # 開啟或關閉特定語言內的特定功能
    $ ctags -R --c++-kinds=+p --python-kinds=+z

    # 開啟或關閉特定欄位
    $ ctags -R --c++-kinds=+p --python-kinds=+z --fields=+iaS

    # 開啟或關閉額外功能
    $ ctags -R --c++-kinds=+p --python-kinds=+z --fields=+iaS --extra=+q


接下來可以直接使用函式或 Class 名稱來開啟對應的檔案：

.. code-block:: sh

    $ vim -t MyClass
    $ vim -t MyFunc


在 Vim 內也可以使用 ``:tag MyFunc`` 來跳到特定函式，
在跳完後可以使用 ``:po`` 或預設的 ``Control+t`` 來跳回上個 tag 處，
使用 ``:ta`` 則可以跳到下一個 tag 處，
Vim 會維護一個 Tags Stack 供這些指令使用，
另外也可以使用預設的 ``Control+o`` 和 ``Control+i`` 來在 Jump List 中跳躍，
Jump List 和 Tags Stack 是不同的儲存區塊，
但是在我們使用 Tags 跳躍時，
它們可能會存入同樣的位置。

+------------+------------------------------------------+
| Vim 按鍵   | 功能                                     |
+============+==========================================+
| Ctrl+]     | 以現在位置的字串做關鍵字，跳入找到的 Tag |
+------------+------------------------------------------+
| Ctrl+t     | 跳回上個 Tag（Tag Stack）                |
+------------+------------------------------------------+
| :po[p]     | 跳回上個 Tag（Tag Stack）                |
+------------+------------------------------------------+
| :ta[g]     | 跳回下個 Tag（Tag Stack）                |
+------------+------------------------------------------+
| :tn[ext]   | 跳到下個被找到的 Tag                     |
+------------+------------------------------------------+
| :tp[rev]   | 跳到上個被找到的 Tag                     |
+------------+------------------------------------------+
| :ts[elect] | 列出符合的 Tags 以供選擇                 |
+------------+------------------------------------------+
| :tags      | 列出目前的 Tag Stack                     |
+------------+------------------------------------------+


Vim
------------------------------

Tagbar
++++++++++++++++++++

:URL: http://majutsushi.github.io/tagbar/

開啟小視窗顯示目前檔案的函式、Class 定義


.. image:: https://i.imgur.com/Sf9Ls2r.png



參考
------------------------------

* `Wikipedia - Ctags <https://en.wikipedia.org/wiki/Ctags>`_
* `Universal Ctags <https://ctags.io/>`_
* [GitHub] `ctags <https://github.com/universal-ctags/ctags>`_



cscope for C & C++
========================================

cscope 是針對 C 和 C++（還有 Java）的輔助工具，
和 ctags 一樣可以提供跳到定義處的功能，
除此之外還支援跳到函式呼叫處，
但沒有像 ctags 一樣支援 Vim 的 Omni Completion。

C 或 C++ 的開發者很可能同時使用 ctags 和 cscope，
因為 cscope 可以提供跳到函式呼叫處，
但是 ctags 運作比較快也支援補完。


安裝
------------------------------

.. code-block:: sh

    $ sudo pacman -S cscope


使用
------------------------------

在專案的根目錄執行指令產生檔案：

.. code-block:: sh

    # 爬現在目錄下的檔案
    $ cscope -R

    # 更多選項
    $ cscope -Rbkq

    # 事先準備好需要用的檔案路徑
    $ find . -name "*.h" -o -name "*.c" -o -name "*.cc" > cscope.files
    $ cscope -Rbkq cscope.files


Vim
------------------------------

cscope.vim
++++++++++++++++++++

:URL: `cscope.vim <https://github.com/brookhong/cscope.vim>`_

.. image:: https://camo.githubusercontent.com/60bae21b2b1b6bc4d457550ef30541640b4ccb83/68747470733a2f2f62726f6f6b686f6e672e6769746875622e696f2f6173736574732f696d616765732f6373636f76652e676966


參考
------------------------------

* `Wikipedia - cscope <https://en.wikipedia.org/wiki/Cscope>`_



jedi for Python
========================================

安裝
------------------------------

.. code-block:: sh

    $ sudo pacman -S python-jedi


Vim
------------------------------

jedi-vim
++++++++++++++++++++

:URL: https://github.com/davidhalter/jedi-vim

.. image:: https://github.com/davidhalter/jedi/raw/master/docs/_screenshots/screenshot_complete.png


deoplete-jedi
++++++++++++++++++++

:URL: https://github.com/zchee/deoplete-jedi


YouCompleteMe
++++++++++++++++++++

:URL: http://valloric.github.io/YouCompleteMe/


參考
------------------------------

* [GitHub] `jedi <https://github.com/davidhalter/jedi>`_



racer for Rust
========================================

Racer 是 Rust 的一套補完工具，
可以提供各個編譯器 Rust 程式碼補完的功能，
另外也有跳到定義處的功能。


安裝
------------------------------

.. code-block:: sh

    $ sudo pacman -S rust-racer

    # 或者用 Cargo
    $ cargo install racer


Vim
------------------------------

* [GitHub] `vim-racer <https://github.com/racer-rust/vim-racer>`_


參考
------------------------------

* [GitHub] `Racer <https://github.com/phildawes/racer>`_
