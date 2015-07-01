========================================
Memory Allocator - Under The Hood
========================================


.. contents:: Table of Contents


System Call for Malloc
========================================

Testing
------------------------------

testing program :

.. code-block:: c

    // test_malloc.c

    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        puts("===========");
        free(malloc(sizeof(int)));
        puts("===========");
        return 0;
    }



Linux
++++++++++++++++++++

compile, execute, trace system call :

.. code-block:: sh

    $ gcc test_malloc.c -o test_malloc
    $ strace ./test_malloc  # Linux

在 trace system call 時，
這邊觀察到兩個 system call，
``brk(0)`` 和 ``brk(0x14e5000)`` (數值可能會不一樣)，
所以我們可以確定的是，
在 Linux 上目前去 call ``malloc`` 時，
會用到 ``brk`` 這個 system call



FreeBSD
++++++++++++++++++++

compile, execute, trace system call :

.. code-block:: sh

    $ clang test_malloc.c -o test_malloc
    $ truss ./test_malloc   # FreeBSD

在 trace system call 時，
這邊只觀察到一個 system call，
``madvise(0x2c07000,0x1000,0x5,0xaaaaaaaaaaaaaaab,0x2c00048,0x24c4be0)`` ，
可以發現使用的 system call 是 ``madvise`` ，
和 Linux 上不同 (Linux 上是 ``brk``)。



Explain
------------------------------

所以到底這些 system call (``brk``, ``madvise``) 都做了些什麼勒？
為什麼 call 完後 heap 就會多出空間可以使用？

我們先來看看 Linux 上的 Memory 都放了些什麼東西 :

.. image:: images/memory-management/Linux-Address-Layout.png
    :alt: Linux Address Layout



sbrk
------------------------------

sbrk 是 glibc 的 brk wrapper



Misc
========================================

* brk 是什麼的縮寫？
