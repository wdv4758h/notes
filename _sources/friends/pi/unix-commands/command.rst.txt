===========
``command``
===========
* 檢查指令的實際位置 ::

    $ command -v python3

* 和 ``which`` 的差異

  - ``command`` 為 bourne shell 內建指令，沒有 fork 的 overhead，且行為比較能被確定
  - ``which`` 指令只用 ``stdout`` 做為執行結果，無法從 exit status 看出結果
