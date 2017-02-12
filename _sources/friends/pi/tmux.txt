===============
tmux 用法及設定
===============

用詞
-----
``tmux`` 的介面可以分成

* 類似 ``screen`` 的分頁
* 分割畫面的區塊

這份文件統一稱呼

* 類似 ``screen`` 的分頁: window
* 分割畫面的區塊: pane

Command Line Arguments
-----------------------
* 開啟一個新的 ``tmux`` session，並指定 session name 為 ``portmaster`` ::

    tmux new -s portmaster

* 列出目前的 ``tmux`` session ::

    tmux ls

* 開啟 tmux 後立即執行一個指令 ::

    tmux new vim

Hot Keys
---------
* ``tmux`` 的 hot key 預設都以 ``C-b`` (``Ctrl`` ``b``) 為前綴

* Hot keys 可參考 http://www.dayid.org/os/notes/tm.html

* 新增一個 ``window`` ::

    C-b c

* 切換至下/上一個 ``window`` ::

    C-b n/p

* 進入指令模式 ::

    C-b :

* 重新命名當前的 ``window`` ::

    C-b ,

  - 與指令 ``rename-window`` 相同，可在 ``C-b ?`` 中查詢到

* 進入 copy mode，按下 enter 或 q 離開 ::

    C-b [

* pane 相關功能

  - 在當前 ``window`` 中新增一個水平分割的 pane ::

      C-b "

  - 在當前 ``window`` 中新增一個垂直分割的 pane ::

      C-b %

  - 切換至另一個 pane ::

      C-b o

    + 也可用 ``C-b 方向鍵`` 或是 ``C-b hjkl`` 來切換

  - 把當前 ``window`` 中的 pane 位置旋轉 ::

      C-b ^o

  - 更換 layout 方向（直的變成橫的） ::

      C-b <SPACE>

  - 往左/右交換 pane 的位置 ::

      C-b {/}

  - 把當前的 pane 分出去變成 ``window`` ::

      C-b !

  - 調整 pane 的大小 ::

      C-b C-(arrow key)

  - 顯示 pane 編號 ::

      C-b q

* 其他

  - 列出 key bindings ::

      C-b ?

    + 按下 enter 後離開

tmux 內部指令
--------------

* ``:detach``

* 把當前的 ``window`` 重命名為 ``test`` ::

    :rename-window test

設定
-----

* 個人設定檔: ``~/.tmux.conf``

* ``M-x`` 為 ``meta+x`` (``alt+x``)

* ``bind-key``

  - ``bind`` 為 ``bind-key`` 的簡寫，此處只提到，不使用
  - ``bind-key key action``

    + 按下 ``C-b key`` 後執行 ``action``

  - ``bind-key -n key action``

    + 按下 ``key`` 後執行 ``action`` (不需前綴的 ``C-b``)

  - ``bind-key -r key action``

    + 按下 ``C-b key`` 後執行 ``action``
    + 但在短時間內 ``key`` 可以重覆而不需要重覆 ``C-b``

  - 範例 ::

      bind-key -n S-Left  previous-window
      bind-key -n S-Right next-window
