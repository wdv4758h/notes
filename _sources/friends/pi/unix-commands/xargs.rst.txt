=========
``xargs``
=========
* 把前面的 output 當成 ``xargs`` 指令的 參數

* 各系統的 ``xargs`` 實作不同 (參數也不同)

  - FreeBSD, GNU ::

      $ find . -type f | xargs -I{} echo test{}test

    + ``-I{}`` 設定對 ``stdin`` 的取代符號，並把 ``stdin`` 的每一行獨立餵給 ``echo``

* 在 ``xargs`` 中使用 pipe（fork 出一個 ``sh`` 來執行） ::

    $ <some-cmd> | xargs -I{} sh -c "echo {} | nl"

