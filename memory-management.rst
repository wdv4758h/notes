========================================
Memory Management
========================================

在現今流通的電腦架構中，要執行一個程式就會需要用到記憶體，
而我們在撰寫程式時，依照不同的語言，會給程式設計師不同的記憶體操作程度。
例如 C 會給你操控 pointer 來對記憶體做各式各樣的處理，
但是像是 Python 這種相對高階的語言則會把記憶體相關的處理打包起來，
讓程式設計師可以專注在計算的撰寫上而不是底層記憶體的掌控。
這當然有好有壞，端看需求來做 tradeoff，
一邊是可以對資源做細部的控制，來用少量的資源達到要做的事，
一邊則是更注重在快速的把可以用的程式寫出來。

在實際開始之前，我們需要先知道一些概念。
在現代常見的電腦中，每隻程式所能看到的記憶體是受限的，
大家會被區隔開來，每隻程式都會以為只有自己在執行，看不到其他人，
這麼做可以保護程式，讓程式間不互相干擾。
想像一下，假如在沒有區隔開的情況下，我寫了一個 C 程式，
不小心沒寫好，裡面的 pointer 可能指向別的程式的資料，
然後還不小心改到，這是多麼可怕的事。
這樣的區隔機制稱為 "Virtual Memory"，
其中的 Virtual 指的意思是分給程式的記憶體空間不是真的實體記憶體，
而是做了一層控管，在存取時中間會把 Virtual Address 轉換成實際的 Physical Address，
而各程式看到的都是同樣的一大塊空間，但其實底下對應到的是不同實體記憶體。
(要做到這樣的機制需要 MMU (memory management unit) 的硬體支援)

在 Virtual Memory 之上，每隻程式看到的記憶體又會依照不同的使用而分區塊，
其中在程式執行時，變數常存在的地方為 Stack 和 Heap，
接下來就來看看裡面在幹嘛。

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

example :

.. code-block:: c

    // C

    #include <stdio.h>
    #include <stdlib.h>     // malloc, free, atoi

    int main (int argc, char *argv[]) {

        int *dynamic_array;

        if (argc < 2) {

            printf("Please give a number\n");

        } else {

            int size = atoi(argv[1]);

            dynamic_array = (int*) malloc (sizeof(int) * size);

            for (int i = 0; i < size; i++) {
                printf("%d\n", dynamic_array[i]);
            }

            free(dynamic_array);

        }

        return 0;
    }

more example (新 malloc 的記憶體真的是新的嗎？) :

.. code-block:: c

    // C

    #include <stdio.h>
    #include <stdlib.h>     // malloc, free, atoi

    int main (int argc, char *argv[]) {

        int *dynamic_array;

        if (argc > 1) {

            int size = atoi(argv[1]);



            dynamic_array = (int*) malloc (sizeof(int) * size);

            printf("first time\n");

            for (int i = 0; i < size; i++) {
                printf("%d\n", dynamic_array[i]);
            }

            for (int i = 0; i < size; i++) {
                // modify
                dynamic_array[i] = i * i;
            }

            free(dynamic_array);



            // get some new memory
            dynamic_array = (int*) malloc (sizeof(int) * size);

            printf("second time\n");

            for (int i = 0; i < size; i++) {
                printf("%d\n", dynamic_array[i]);
            }

            free(dynamic_array);



        } else {

            printf("Please give a number\n");

        }

        return 0;
    }

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

source code :

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
        return 0;
    }

compile :

.. code-block:: sh

    $ gcc -Wall -std=c11 -g double-free.c -o double-free

執行 ::

    origin : 0
    assign : 10
    *** Error in `./double-free': double free or corruption (fasttop): 0x00000000013e3010 ***
    ======= Backtrace: =========
    /usr/lib/libc.so.6(+0x71bad)[0x7ffb1c21cbad]
    /usr/lib/libc.so.6(+0x770fe)[0x7ffb1c2220fe]
    /usr/lib/libc.so.6(+0x778db)[0x7ffb1c2228db]
    ./double-free[0x4005fc]
    /usr/lib/libc.so.6(__libc_start_main+0xf0)[0x7ffb1c1cb790]
    ./double-free[0x4004c9]
    ======= Memory map: ========
    00400000-00401000 r-xp 00000000 00:1e 1685697                            /tmp/memory/double-free
    00600000-00601000 rw-p 00000000 00:1e 1685697                            /tmp/memory/double-free
    013e3000-01404000 rw-p 00000000 00:00 0                                  [heap]
    7ffb1bf95000-7ffb1bfab000 r-xp 00000000 08:01 137661                     /usr/lib/libgcc_s.so.1
    7ffb1bfab000-7ffb1c1aa000 ---p 00016000 08:01 137661                     /usr/lib/libgcc_s.so.1
    7ffb1c1aa000-7ffb1c1ab000 rw-p 00015000 08:01 137661                     /usr/lib/libgcc_s.so.1
    7ffb1c1ab000-7ffb1c344000 r-xp 00000000 08:01 134345                     /usr/lib/libc-2.21.so
    7ffb1c344000-7ffb1c543000 ---p 00199000 08:01 134345                     /usr/lib/libc-2.21.so
    7ffb1c543000-7ffb1c547000 r--p 00198000 08:01 134345                     /usr/lib/libc-2.21.so
    7ffb1c547000-7ffb1c549000 rw-p 0019c000 08:01 134345                     /usr/lib/libc-2.21.so
    7ffb1c549000-7ffb1c54d000 rw-p 00000000 00:00 0
    7ffb1c54d000-7ffb1c56f000 r-xp 00000000 08:01 134444                     /usr/lib/ld-2.21.so
    7ffb1c72a000-7ffb1c72d000 rw-p 00000000 00:00 0
    7ffb1c76c000-7ffb1c76e000 rw-p 00000000 00:00 0
    7ffb1c76e000-7ffb1c76f000 r--p 00021000 08:01 134444                     /usr/lib/ld-2.21.so
    7ffb1c76f000-7ffb1c770000 rw-p 00022000 08:01 134444                     /usr/lib/ld-2.21.so
    7ffb1c770000-7ffb1c771000 rw-p 00000000 00:00 0
    7ffe79fa4000-7ffe79fc5000 rw-p 00000000 00:00 0                          [stack]
    7ffe79fdf000-7ffe79fe1000 r--p 00000000 00:00 0                          [vvar]
    7ffe79fe1000-7ffe79fe3000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    Aborted (core dumped)

memory leak
------------------------------

source code :

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

        return 0;
    }

compile :

.. code-block:: sh

    $ gcc -Wall -std=c11 -g memory-leak.c -o memory-leak


觀看 Memory 使用：

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

source code :

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

compile :

.. code-block:: sh

    $ gcc -Wall -std=c11 -g use-after-free.c -o use-after-free

.. code-block:: sh

    $ ./use-after-free
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

Valgrind
------------------------------

double free
++++++++++++++++++++

執行：

.. code-block:: sh

    $ valgrind ./double-free

Valgrind output ::

    ==22811== Memcheck, a memory error detector
    ==22811== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==22811== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==22811== Command: ./double-free
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7D3DC: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Use of uninitialised value of size 8
    ==22811==    at 0x4E7A33B: _itoa_word (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E7D6BD: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7A345: _itoa_word (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E7D6BD: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7D730: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7D4AB: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7D837: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7D4FB: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Conditional jump or move depends on uninitialised value(s)
    ==22811==    at 0x4E7D53B: vfprintf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4E84E38: printf (in /usr/lib/libc-2.21.so)
    ==22811==    by 0x4005C2: main (double-free.c:8)
    ==22811==
    ==22811== Invalid free() / delete / delete[] / realloc()
    ==22811==    at 0x4C2B200: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==22811==    by 0x4005FB: main (double-free.c:12)
    ==22811==  Address 0x51d8040 is 0 bytes inside a block of size 4 free'd
    ==22811==    at 0x4C2B200: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==22811==    by 0x4005EF: main (double-free.c:11)
    ==22811==
    ==22811==
    ==22811== HEAP SUMMARY:
    ==22811==     in use at exit: 0 bytes in 0 blocks
    ==22811==   total heap usage: 1 allocs, 2 frees, 4 bytes allocated
    ==22811==
    ==22811== All heap blocks were freed -- no leaks are possible
    ==22811==
    ==22811== For counts of detected and suppressed errors, rerun with: -v
    ==22811== Use --track-origins=yes to see where uninitialised values come from
    ==22811== ERROR SUMMARY: 9 errors from 9 contexts (suppressed: 0 from 0)

memory leak
++++++++++++++++++++

執行：

.. code-block:: sh

    $ valgrind --leak-check=full ./memory-leak

Valgrind output ::

    ==27173== Memcheck, a memory error detector
    ==27173== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==27173== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==27173== Command: ./memory-leak
    ==27173==
    ==27173==
    ==27173== HEAP SUMMARY:
    ==27173==     in use at exit: 32,000 bytes in 4 blocks
    ==27173==   total heap usage: 4 allocs, 0 frees, 32,000 bytes allocated
    ==27173==
    ==27173== 8,000 bytes in 1 blocks are still reachable in loss record 1 of 2
    ==27173==    at 0x4C29F90: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==27173==    by 0x400621: main (memory-leak.c:15)
    ==27173==
    ==27173== 24,000 bytes in 3 blocks are definitely lost in loss record 2 of 2
    ==27173==    at 0x4C29F90: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==27173==    by 0x400621: main (memory-leak.c:15)
    ==27173==
    ==27173== LEAK SUMMARY:
    ==27173==    definitely lost: 24,000 bytes in 3 blocks
    ==27173==    indirectly lost: 0 bytes in 0 blocks
    ==27173==      possibly lost: 0 bytes in 0 blocks
    ==27173==    still reachable: 8,000 bytes in 1 blocks
    ==27173==         suppressed: 0 bytes in 0 blocks
    ==27173==
    ==27173== For counts of detected and suppressed errors, rerun with: -v
    ==27173== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

use after free
++++++++++++++++++++



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

More Allocator Implementations
=========================================

* jemalloc
* tcmalloc

Reference
=========================================

* `[2009] Anatomy of a Program in Memory <http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/>`_
* `[2013] Using the Pointer Ownership Model to Secure Memory Management in C and C++ <http://blog.sei.cmu.edu/post.cfm/using-the-pointer-ownership-model-to-secure-memory-management-in-c-and-c>`_
* `Wikipedia - C dynamic memory allocation <https://en.wikipedia.org/wiki/C_dynamic_memory_allocation>`_
* `Wikipedia - Memory management unit <https://en.wikipedia.org/wiki/Memory_management_unit>`_
* `Wikipedia - Virtual memory <https://en.wikipedia.org/wiki/Virtual_memory>`_
* `Wikipedia - Memory management <https://en.wikipedia.org/wiki/Memory_management>`_
