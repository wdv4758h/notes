===============================================================================
``sed``
===============================================================================
``sed`` 的全稱為 Stream Editor，也就是說它是個文字編輯器。

``sed`` 能夠安插在 pipeline 中間，以每行文字為單位做處理，這是它最大的特色。


概念
-------------------------------------------------------------------------------
sed 維護兩個 buffer，一個叫做 pattern space，另一個叫做 hold space。

運作流程如下

1.  從 input stream 讀取一行文字，把行尾的 newline 刪掉，放進 pattern space
2.  執行 command

    * Command 前可以帶有 address（條件）
    * 有些 command 不需要跟著 address，有些可跟可不跟，有些則一定要跟
    * 若 command 有跟著 address，則要條件符合，才會執行
    * 多個 command 之間可以用 ``;`` 隔開

3.  如果 ``-n`` 沒有開啟的話，把 pattern space 印出來，補回 newline
4.  除非有特別的 command 被執行，否則將 pattern space 清空
5.  回到 1.


基本用法
-------------------------------------------------------------------------------
::

  sed [OPTION] <command> [input-file] ...

範例

* 模仿 ``grep`` 的行為 ::

    $ sed -n '/MSG_ID/{=;p}'

* 模仿 ``tr`` 的行為 ::

    $ sed 'y/COOKIE/BANANA/'

* 在每個有 match ``pattern`` 的行前面都插入 ``BANANA`` ::

    $ sed '/pattern/i BANANA'

Option
-------------------------------------------------------------------------------
* ``-i`` - in-place 的修改檔案
* ``-n`` - 不要在 cycle 結束時印出 pattern space


Address
-------------------------------------------------------------------------------
* ``/pattern/`` - match ``pattern``
* ``$`` - match 最後一行


Command
-------------------------------------------------------------------------------
- ``s/pattern/replacement/flags`` - 取代

  + pattern 裡面的 group 小括號需要跳脫，i.e. ``\(\)``

* ``d`` - 刪除
* ``p`` - 印出 pattern space
* ``=`` - 印出行數
* ``{<cmd>; <cmd>; ...}`` - 將一串 command 包成一個
* ``: <label>`` - 在 "此處" 設定 branch label
* ``t <label>`` - 若 ``s///`` 有取代成功，跳至 ``label``
* ``a text`` - append text
* ``i text`` - insert text
