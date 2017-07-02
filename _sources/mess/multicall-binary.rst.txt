========================================
Multicall Binary
========================================

Multicall Binary 指的是一個 binary 檔，
可以同時包含好幾隻不同的程式，
依照執行這 binary 的方式而決定要跑裡面的哪種程式，
這技巧的知名例子就是 BusyBox，
把撰寫的許多 command 編在一起，
共用許多部份，
藉此達到省空間的目的 (BusyBox 的目標是跑在資源相對有限的嵌入式系統)，
達到這效果的方式則是利用 ``argv[0]`` 來做判斷，
如果名稱是內部程式之一的話，
就去執行該程式的部份，
因此可以看到諸多個指令都只是 BusyBox 的 symbolic link，
但執行起來效果卻不同。

例如這個樣子：

::

    -rwxr-xr-x 1 root root 931664 Aug  9 13:19 busybox*
    lrwxrwxrwx 1 root root      7 Aug  9 13:20 ls -> busybox*
    lrwxrwxrwx 1 root root      7 Aug  9 13:20 pwd -> busybox*



Reference
========================================

* `Multicall binaries <https://blog.flameeyes.eu/2009/10/multicall-binaries>`_
* `Creating a Multi-Call Linux Binary <http://www.redbooks.ibm.com/abstracts/tips0092.html>`_
* `[GitHub] extemporalgenome/multicall-example - Hybrid multi-call/single-call binaries in Go <https://github.com/extemporalgenome/multicall-example>`_
