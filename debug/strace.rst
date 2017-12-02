========================================
strace
========================================


.. contents:: 目錄


基本介紹
========================================

`strace <https://strace.io/>`_ 是一個追蹤 system call 的工具，
可以指定追蹤某個正在跑的程式、準備執行的程式，
也可以指定要追蹤的 system call 來減少不需要的訊息，
而 strace 的實做則是仰賴 kernel 中的 ptrace。

使用範例：

``-c`` 輸出 system call 使用統計：

.. code-block:: sh

    $ strace -c ls > /dev/null
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
      0.00    0.000000           0        17           read
      0.00    0.000000           0         1           write
      0.00    0.000000           0         4         1 open
      0.00    0.000000           0         8           close
      0.00    0.000000           0         7           fstat
      0.00    0.000000           0         9           mmap
      0.00    0.000000           0         5           mprotect
      0.00    0.000000           0         1           munmap
      0.00    0.000000           0         4           brk
      0.00    0.000000           0         3         3 ioctl
      0.00    0.000000           0         1         1 access
      0.00    0.000000           0         1           execve
      0.00    0.000000           0         2           getdents
      0.00    0.000000           0         1           arch_prctl
      0.00    0.000000           0         3           openat
    ------ ----------- ----------- --------- --------- ----------------
    100.00    0.000000                    67         5 total


``-k`` 輸出每個 system call 的 stack trace，
原先來自於 `strace-plus <https://code.google.com/p/strace-plus/>`_ 後來 merge 回上游，
需要在編譯時有開啟 libunwind 支援：

.. code-block:: sh

    $ strace -k ls > /dev/null
    execve("/usr/bin/ls", ["ls"], 0x7ffc07df1168 /* 45 vars */) = 0
     > /usr/lib/libc-2.26.so(execve+0x7) [0xc45e7]
     > /usr/bin/strace(_init+0x166) [0x63766]
     > /usr/bin/strace(_init+0x28224) [0x8b824]
     > /usr/bin/strace(_init+0x28b63) [0x8c163]
     > /usr/bin/strace(_init+0x1d9) [0x637d9]
     > /usr/lib/libc-2.26.so(__libc_start_main+0xea) [0x20f6a]
     > /usr/bin/strace(_init+0xdaa) [0x643aa]
    brk(NULL)                               = 0x55c73188c000
     > /usr/lib/ld-2.26.so(__brk+0x9) [0x19bf9]
     > /usr/lib/ld-2.26.so(_dl_sysdep_start+0x391) [0x189a1]
    ...
