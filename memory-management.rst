Stack & Heap
=========================================

在講記憶體管理的一開始，我們先來看看資料在記憶體中是如何被放置的。

Linux process :

.. image:: images/memory-management/Linux-Address-Layout.png
    :alt: Linux Address Layout

其中 Stack 是 **local variables** 和 **function parameters** 的地方，
每呼叫一次 function 就會 push 一個 stack frame 進去，
每次 function 回傳時就會被清掉。

[Error] 這邊可以注意到，如果我們不斷地 push 到 stack 裡，
最後超過可容許的大小，就會產生 ``stack overflow``

因為放在 stack 上的資料會在回傳時被清掉，
當遇到回傳後仍需使用的情況，
就要把資料放在 Heap。

在 C 中要使用 Heap 就需要用 **malloc** 並設定需要的大小，
用完後需要使用 **free** 來清除。
這些步驟在一般使用 Stack 的情況中都不需要，
但是 Heap 的特別處就在於不會受限於特定的 scope 裡，
就算 function 回傳還是可以正常使用，也常用動態決定資料大小的情況。

Common Memory Problem
=========================================

管理

* double free (清多次)
* memory leak (沒清到)

使用

* use after free (清了還用)
* dangling pointer (清了還用)
* heap overflow (寫超過)
* stack buffer overflow (寫超過)
* buffer over-read (讀超過)
* stack overflow (用太多)

double free
------------------------------

.. code-block:: c

    // C

    #include <stdio.h>
    #include <stdlib.h>     // malloc, free

    int main() {
        int *x = malloc(sizeof(int));
        printf("origin : %d\n", *x);
        *x = 10;
        printf("assign : %d\n", *x);
        free(x);
        free(x);
    }

::

    origin : 0
    assign : 10
    *** Error in `./a.out': double free or corruption (fasttop): 0x0000000001288010 ***
    ======= Backtrace: =========
    /usr/lib/libc.so.6(+0x71bad)[0x7f9fe836ebad]
    /usr/lib/libc.so.6(+0x770fe)[0x7f9fe83740fe]
    /usr/lib/libc.so.6(+0x778db)[0x7f9fe83748db]
    ./a.out[0x4005fc]
    /usr/lib/libc.so.6(__libc_start_main+0xf0)[0x7f9fe831d790]
    ./a.out[0x4004c9]
    ======= Memory map: ========
    00400000-00401000 r-xp 00000000 08:02 1704311                            /home/dv/zone/a.out
    00600000-00601000 rw-p 00000000 08:02 1704311                            /home/dv/zone/a.out
    01288000-012a9000 rw-p 00000000 00:00 0                                  [heap]
    7f9fe80e7000-7f9fe80fd000 r-xp 00000000 08:01 137661                     /usr/lib/libgcc_s.so.1
    7f9fe80fd000-7f9fe82fc000 ---p 00016000 08:01 137661                     /usr/lib/libgcc_s.so.1
    7f9fe82fc000-7f9fe82fd000 rw-p 00015000 08:01 137661                     /usr/lib/libgcc_s.so.1
    7f9fe82fd000-7f9fe8496000 r-xp 00000000 08:01 134345                     /usr/lib/libc-2.21.so
    7f9fe8496000-7f9fe8695000 ---p 00199000 08:01 134345                     /usr/lib/libc-2.21.so
    7f9fe8695000-7f9fe8699000 r--p 00198000 08:01 134345                     /usr/lib/libc-2.21.so
    7f9fe8699000-7f9fe869b000 rw-p 0019c000 08:01 134345                     /usr/lib/libc-2.21.so
    7f9fe869b000-7f9fe869f000 rw-p 00000000 00:00 0
    7f9fe869f000-7f9fe86c1000 r-xp 00000000 08:01 134444                     /usr/lib/ld-2.21.so
    7f9fe887d000-7f9fe8880000 rw-p 00000000 00:00 0
    7f9fe88be000-7f9fe88c0000 rw-p 00000000 00:00 0
    7f9fe88c0000-7f9fe88c1000 r--p 00021000 08:01 134444                     /usr/lib/ld-2.21.so
    7f9fe88c1000-7f9fe88c2000 rw-p 00022000 08:01 134444                     /usr/lib/ld-2.21.so
    7f9fe88c2000-7f9fe88c3000 rw-p 00000000 00:00 0
    7ffc6d416000-7ffc6d437000 rw-p 00000000 00:00 0                          [stack]
    7ffc6d593000-7ffc6d595000 r--p 00000000 00:00 0                          [vvar]
    7ffc6d595000-7ffc6d597000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    Aborted (core dumped)

memory leak
------------------------------

.. code-block:: c

    // C

    #include <stdio.h>
    #include <stdlib.h>     // malloc
    #include <unistd.h>     // getpid

    int main() {
        long long *x;

        printf("pid : %d\n", getpid());
        printf("per size %lu\n", sizeof(long long));

        while (1) {
            // malloc, no free
            x = malloc(sizeof(long long) * 1000);
            getchar();
        }
    }

.. code-block:: sh

    $ pmap -x $pid
    30593:   ./a.out
    Address           Kbytes     RSS   Dirty Mode  Mapping
    0000000000400000       4       4       0 r-x-- a.out
    0000000000600000       4       4       4 rw--- a.out
    0000000002572000     136       8       8 rw---   [ anon ]
    00007fe14389b000    1636    1044       0 r-x-- libc-2.21.so
    00007fe143a34000    2044       0       0 ----- libc-2.21.so
    00007fe143c33000      16      16      16 r---- libc-2.21.so
    00007fe143c37000       8       8       8 rw--- libc-2.21.so
    00007fe143c39000      16       8       8 rw---   [ anon ]
    00007fe143c3d000     136     136       0 r-x-- ld-2.21.so
    00007fe143e1b000      12      12      12 rw---   [ anon ]
    00007fe143e5c000       8       4       4 rw---   [ anon ]
    00007fe143e5e000       4       4       4 r---- ld-2.21.so
    00007fe143e5f000       4       4       4 rw--- ld-2.21.so
    00007fe143e60000       4       4       4 rw---   [ anon ]
    00007fff33951000     132       8       8 rw---   [ stack ]
    00007fff3397a000       8       0       0 r----   [ anon ]
    00007fff3397c000       8       4       0 r-x--   [ anon ]
    ffffffffff600000       4       0       0 r-x--   [ anon ]
    ---------------- ------- ------- -------
    total kB            4184    1268      80

.. code-block:: sh

    $ cat /proc/$pid/smaps | grep -A 15 heap
    02572000-02594000 rw-p 00000000 00:00 0                                  [heap]
    Size:                136 kB
    Rss:                   8 kB
    Pss:                   8 kB
    Shared_Clean:          0 kB
    Shared_Dirty:          0 kB
    Private_Clean:         0 kB
    Private_Dirty:         8 kB
    Referenced:            8 kB
    Anonymous:             8 kB
    AnonHugePages:         0 kB
    Swap:                  0 kB
    KernelPageSize:        4 kB
    MMUPageSize:           4 kB
    Locked:                0 kB
    VmFlags: rd wr mr mw me ac

use after free
------------------------------

.. code-block:: c

    // C

    #include <stdio.h>
    #include <stdlib.h>     // malloc

    int main() {
        int *x;

        x = malloc(sizeof(int));
        *x = 9;

        printf("use before free : %d\n", *x);

        free(x);

        printf("use after free : %d\n", *x);

        int *y = malloc(sizeof(int));
        *y = 10;

        printf("use after free : %d\n", *x);

        return 0;
    }

.. code-block:: sh

    $ ./a.out
    use before free : 9
    use after free : 0
    use after free : 10

stack buffer overflow
------------------------------

.. code-block:: c

    // C

    #include <stdio.h>

    int main() {
        int x = 0;
        char c[1];
        printf("%d\n", x);
        scanf("%s", c);
        printf("%d\n", x);
        return 0;
    }

.. code-block:: sh

    $ ./a.out
    x : 0
    test
    x : 7631717

buffer over-read
------------------------------

.. code-block:: c

    // C

    #include <stdio.h>

    int main() {

        int x = 'z';

        char c[1];
        c[0] = 'a';

        printf("c[0] : %c\n", c[0]);
        printf("c[1] : %c\n", c[1]);    // read x

        return 0;
    }

.. code-block:: sh

    $ ./a.out
    c[0] : a
    c[1] : z

stack overflow
------------------------------

.. code-block:: c

    // C

    #include <stdio.h>

    void stack_overflow() {
        static int count = 0;

        count++;

        printf("count : %d\n", count);

        stack_overflow();
    }

    int main() {
        stack_overflow();
        return 0;
    }

.. code-block:: sh

    $ gcc -O0 stack-overflow.c  # avoid optimization

Debugger
=========================================

* Valgrind

RAII (Resource Acquisition Is Initialization)
=============================================

RAII 為在數個 OO 語言中使用的 programming idiom，
為 C++ 於 1984 到 1989 年間發展出來，主要由 Bjarne Stroustrup 和 Andrew Koenig 來完成，
後來也用於 D、Ada、Vala、Rust 等語言。

主要概念為把資源和物件的 lifetime 綁在一起，
當物件由 constructor 建立時，就做 resource allocation，
當物件由 destructor 拆掉時，就做 resource deallocation，
如此一來只要物件正常的拆掉，就不會有 resource leak 發生。

Ownership
=========================================

Garbage Collection
=========================================

Cases
=========================================

* Python
    - CPython : GC with reference counting
    - PyPy : GC with incremental generational tracing (incminimark)

Reference
=========================================

* `[2009] Anatomy of a Program in Memory <http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/>`_
* `[2013] Using the Pointer Ownership Model to Secure Memory Management in C and C++ <http://blog.sei.cmu.edu/post.cfm/using-the-pointer-ownership-model-to-secure-memory-management-in-c-and-c>`_
