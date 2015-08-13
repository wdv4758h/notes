========================================
strace
========================================

* -k
    - 在紀錄每個 system call 之後加上 stack trace
    - 原先來自於 `strace-plus <https://code.google.com/p/strace-plus/>`_ 後來 merge 回上游
    - 需要在編譯時有開啟 libunwind 支援
