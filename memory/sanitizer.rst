========================================
Sanitizer
========================================


Introduction
========================================

寫程式常碰到有 bug，
用 C 或 C++ 這種程式語言寫的話，
bug 又常跟記憶體有關，
這時常常會使用 Valgrind 來找問題，
而近幾年又多了一些 compiler 參數可以幫忙。

當要跑的平台上可以用 compiler 參數來檢查時，
可以考慮就先使用 compiler 參數，
如果要用的 compiler 沒支援這參數或是 compiler 沒支援要跑的平台，
那麼可以考慮 Valgrind，
雖然比較慢，
但是可用的平台和能偵測的項目很多。

compiler 的 sanitizer 這邊有些細部要注意，
在一些條件下可能會不支援。



* Clang
    - AddressSanitizer
        + memory error detector
        + a compiler instrumentation module and a run-time library
    - MemorySanitizer
        + detector of uninitialized reads
        + a compiler instrumentation module and a run-time library
    - ThreadSanitizer
        + detects data races
    - LeakSanitizer
        + detects memory leaks
    - UndefinedBehaviorSanitier



這三個只能分開使用，不能一起用：

1. AddressSanitizer
2. ThreadSanitizer
3. MemorySanitizer



* UndefinedBehaviorSanitier 可以和其他種結合
* LeakSanitizer 目前只可以和 AddressSanitizer 一起用 (或自己用)


+---------------------------+----------------+------------------------------+----------------------+
| Name                      | Slowdown       | Memory Overhead              | Option               |
+===========================+================+==============================+======================+
| AddressSanitizer_         | 2x             |                              | -fsanitize=address   |
+---------------------------+----------------+------------------------------+----------------------+
| ThreadSanitizer_          | 5x ~ 15x       | 5x ~ 10x                     | -fsanitize=thread    |
+---------------------------+----------------+------------------------------+----------------------+
| MemorySanitizer_          | 3x             | 2x (3x with origin tracking) | -fsanitize=memory    |
+---------------------------+----------------+------------------------------+----------------------+
| LeakSanitizer_            | 0x (with ASan) |                              | -fsanitize=leak      |
+---------------------------+----------------+------------------------------+----------------------+
| UndefinedBehaviorSanitier | 0x             |                              | -fsanitize=undefined |
+---------------------------+----------------+------------------------------+----------------------+


.. _AddressSanitizer: http://clang.llvm.org/docs/AddressSanitizer.html
.. _ThreadSanitizer: http://clang.llvm.org/docs/ThreadSanitizer.html
.. _MemorySanitizer: http://clang.llvm.org/docs/MemorySanitizer.html
.. _LeakSanitizer: http://clang.llvm.org/docs/LeakSanitizer.html


::

    +----------------------------+   no
    | 你想要找 memory 相關的 bug |---------> 不在這邊的討論範圍內
    +----------------------------+
                |
                | yes
                |
                v
    +-------------------------+  no
    | 專案使用 Clang/GCC 編譯 |---------> 用 Valgrind
    +-------------------------+
                |                                          +---------------------+
                | yes                                   +->| 找其他 Memory Error |--+
                |                                       |  +---------------------+  |
                v                                       |                           |
    +----------------------+  no   +--------------+  no |  +----------------+       |
    | 尋找存取未初始化的值 |------>| 找 data race |-----+->| 找 memory leak |       |
    +----------------------+       +--------------+        +----------------+       |
                |                          |                      |                 |
                | yes                      | yes                  | yes             | yes
                |                          |                      |                 |
                v                          v                      v                 v
        MemorySanitizer            ThreadSanitizer           LeakSanitizer    AddressSanitizer
                                                                  |                 |
                                                                  |                 |
                                                                  +--------+--------+
                                                                           |
                                                                           v
                                                            LeakSanitizer + AddressSanitizer

    +----------------------+
    | 找 undefine behavior |
    +----------------------+
                |
                |
                |
                v
    UndefinedBehaviorSanitier


----

* 利用這邊的工具除錯時，推薦的優化參數： ``-O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls``
    - ``-O1`` 是為了關掉 inline
    - ``-fno-omit-frame-pointer`` 是為了更好的 stack trace 訊息
    - ``-fno-optimize-sibling-calls`` 是為了關掉 tail call elimination

----

* PASS 1 : ``-fsanitize=leak -fsanitize=address -fsanitize=undefined``
    - Memory Leaks
    - 大部分的 Memory 相關錯誤
    - Undefined Behavior
* PASS 2 : ``-fsanitize=memory``
    - 找出未初始化的值的使用
* PASS 3 : ``-fsanitize=thread``
    - 找出 data races



AddressSanitizer
========================================

AddressSanitizer 目前支援以下幾種情況：

* (OOB) Out-of-bounds accesses to heap, stack and globals
* (UAF) Use-after-free
* (UAR) Use-after-return (to some extent)
* Double-free, invalid free
* Memory leaks (experimental)


(最後生成 executable 時，需要把 AddressSanitizer run-time library link 上去，所以最後的 link step 要用 clang，不能用 ld)

遇到錯誤會馬上停止，developer 會被強迫修正問題後才能繼續執行。


Example 1
------------------------------

Source Code :

.. code-block:: cpp

    int main() {
        // UAF (Use After Free)
        int *array = new int[42];
        delete [] array;
        return array[0];    // BOOM
    }


Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=address -fno-omit-frame-pointer example.cpp -o example


Run :

.. code-block:: sh

    $ ./example
    =================================================================
    ==26771==ERROR: AddressSanitizer: heap-use-after-free on address 0x60f00000ef50 at pc 0x0000004dc22c bp 0x7fffc3c85060 sp 0x7fffc3c85058
    READ of size 4 at 0x60f00000ef50 thread T0
        #0 0x4dc22b in main /tmp/example.cpp:5:12
        #1 0x300042078f in __libc_start_main (/usr/lib/libc.so.6+0x300042078f)
        #2 0x434fa8 in _start (/tmp/example+0x434fa8)

    0x60f00000ef50 is located 0 bytes inside of 168-byte region [0x60f00000ef50,0x60f00000eff8)
    freed by thread T0 here:
        #0 0x4dbb22 in operator delete[](void*) (/tmp/example+0x4dbb22)
        #1 0x4dc1fa in main /tmp/example.cpp:4:5
        #2 0x300042078f in __libc_start_main (/usr/lib/libc.so.6+0x300042078f)

    previously allocated by thread T0 here:
        #0 0x4db562 in operator new[](unsigned long) (/tmp/example+0x4db562)
        #1 0x4dc1ef in main /tmp/example.cpp:3:18
        #2 0x300042078f in __libc_start_main (/usr/lib/libc.so.6+0x300042078f)

    SUMMARY: AddressSanitizer: heap-use-after-free /tmp/example.cpp:5 main
    Shadow bytes around the buggy address:
    0x0c1e7fff9d90: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9da0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9db0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9dc0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9dd0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    =>0x0c1e7fff9de0: fa fa fa fa fa fa fa fa fa fa[fd]fd fd fd fd fd
    0x0c1e7fff9df0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fa
    0x0c1e7fff9e00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9e10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9e20: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c1e7fff9e30: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    Shadow byte legend (one shadow byte represents 8 application bytes):
    Addressable:           00
    Partially addressable: 01 02 03 04 05 06 07
    Heap left redzone:       fa
    Heap right redzone:      fb
    Freed heap region:       fd
    Stack left redzone:      f1
    Stack mid redzone:       f2
    Stack right redzone:     f3
    Stack partial redzone:   f4
    Stack after return:      f5
    Stack use after scope:   f8
    Global redzone:          f9
    Global init order:       f6
    Poisoned by user:        f7
    Container overflow:      fc
    Array cookie:            ac
    Intra object redzone:    bb
    ASan internal:           fe
    Left alloca redzone:     ca
    Right alloca redzone:    cb
    ==26771==ABORTING


Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=address -fno-omit-frame-pointer example.cpp -o example


Run with Valgrind :

.. code-block:: sh

    $ valgrind ./example
    ==28951== Memcheck, a memory error detector
    ==28951== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==28951== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==28951== Command: ./example
    ==28951==
    ==28951== Invalid read of size 4
    ==28951==    at 0x4005A7: main (in /tmp/example)
    ==28951==  Address 0xfff000674 is on thread 1's stack
    ==28951==  412 bytes below stack pointer
    ==28951==
    ==28951==
    ==28951== HEAP SUMMARY:
    ==28951==     in use at exit: 72,704 bytes in 1 blocks
    ==28951==   total heap usage: 1 allocs, 0 frees, 72,704 bytes allocated
    ==28951==
    ==28951== LEAK SUMMARY:
    ==28951==    definitely lost: 0 bytes in 0 blocks
    ==28951==    indirectly lost: 0 bytes in 0 blocks
    ==28951==      possibly lost: 0 bytes in 0 blocks
    ==28951==    still reachable: 72,704 bytes in 1 blocks
    ==28951==         suppressed: 0 bytes in 0 blocks
    ==28951== Rerun with --leak-check=full to see details of leaked memory
    ==28951==
    ==28951== For counts of detected and suppressed errors, rerun with: -v
    ==28951== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)



Example 2 (Can Not Detect) (Neither Valgrind ...)
-------------------------------------------------

Source Code :

.. code-block:: cpp

    int main() {
        int *ptr= nullptr;

        {
            int array[42];
            array[0] = 42;
            ptr = array;
        }

        ptr[0] = 99;

        return ptr[0];    // ptr points to an array which is out of scope !!!
    }


Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=address -fno-omit-frame-pointer example.cpp -o example


Run :

.. code-block:: sh

    $ ./example
    # nothing happen ...


Example 3 (Can Not Detect) (Valgrind can find it !!!)
-----------------------------------------------------

Source Code :

.. code-block:: cpp

    void f(int **pptr) {
        int array[42];
        array[0] = 42;
        *pptr = array;
    }

    int main() {
        int *ptr= nullptr;
        f(&ptr);
        ptr[0] = 99;
        return ptr[0];    // ptr points to an array which is out of scope !!!
    }


Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=address -fno-omit-frame-pointer example.cpp -o example


Run :

.. code-block:: sh

    $ ./example
    # nothing happen ...



Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=address -fno-omit-frame-pointer example.cpp -o example


Run with Valgrind :

.. code-block:: sh

    $ valgrind ./example
    ==13109== Memcheck, a memory error detector
    ==13109== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==13109== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==13109== Command: ./example
    ==13109==
    ==13109== Invalid write of size 4
    ==13109==    at 0x4005AD: main (example.cpp:10)
    ==13109==  Address 0xfff000760 is on thread 1's stack
    ==13109==  176 bytes below stack pointer
    ==13109==
    ==13109== Invalid read of size 4
    ==13109==    at 0x4005B7: main (in /tmp/example)
    ==13109==  Address 0xfff000760 is on thread 1's stack
    ==13109==  176 bytes below stack pointer
    ==13109==
    ==13109==
    ==13109== HEAP SUMMARY:
    ==13109==     in use at exit: 72,704 bytes in 1 blocks
    ==13109==   total heap usage: 1 allocs, 0 frees, 72,704 bytes allocated
    ==13109==
    ==13109== LEAK SUMMARY:
    ==13109==    definitely lost: 0 bytes in 0 blocks
    ==13109==    indirectly lost: 0 bytes in 0 blocks
    ==13109==      possibly lost: 0 bytes in 0 blocks
    ==13109==    still reachable: 72,704 bytes in 1 blocks
    ==13109==         suppressed: 0 bytes in 0 blocks
    ==13109== Rerun with --leak-check=full to see details of leaked memory
    ==13109==
    ==13109== For counts of detected and suppressed errors, rerun with: -v
    ==13109== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)


Example 4 (Can Not Detect) (Valgrind can find it !!!)
-----------------------------------------------------

from `address-sanitizer - Example: UseAfterReturn <https://code.google.com/p/address-sanitizer/wiki/ExampleUseAfterReturn>`_

Source Code :

.. code-block:: cpp

    int *ptr;
    __attribute__((noinline))
    void FunctionThatEscapesLocalObject() {
        int local[100];
        ptr = &local[0];
    }

    int main(int argc, char **argv) {
        FunctionThatEscapesLocalObject();
        return ptr[argc];
    }


Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=address -fno-omit-frame-pointer example.cpp -o example



Run :

.. code-block:: sh

    $ ./example
    # nothing happen ...



Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fno-omit-frame-pointer example.cpp -o example


Run with Valgrind :

.. code-block:: sh

    $ valgrind ./example
    ==27388== Memcheck, a memory error detector
    ==27388== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==27388== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==27388== Command: ./example
    ==27388==
    ==27388== Invalid read of size 4
    ==27388==    at 0x4005A7: main (in /tmp/example)
    ==27388==  Address 0xfff000674 is on thread 1's stack
    ==27388==  412 bytes below stack pointer
    ==27388==
    ==27388==
    ==27388== HEAP SUMMARY:
    ==27388==     in use at exit: 72,704 bytes in 1 blocks
    ==27388==   total heap usage: 1 allocs, 0 frees, 72,704 bytes allocated
    ==27388==
    ==27388== LEAK SUMMARY:
    ==27388==    definitely lost: 0 bytes in 0 blocks
    ==27388==    indirectly lost: 0 bytes in 0 blocks
    ==27388==      possibly lost: 0 bytes in 0 blocks
    ==27388==    still reachable: 72,704 bytes in 1 blocks
    ==27388==         suppressed: 0 bytes in 0 blocks
    ==27388== Rerun with --leak-check=full to see details of leaked memory
    ==27388==
    ==27388== For counts of detected and suppressed errors, rerun with: -v
    ==27388== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)



MemorySanitizer
========================================

compile 時加上參數 : ``-fsanitize=address``


Example 1
------------------------------

前面用過的範例，再用一次

Source Code :

.. code-block:: cpp

    int *ptr;
    __attribute__((noinline))
    void FunctionThatEscapesLocalObject() {
        int local[100];
        ptr = &local[0];
    }

    int main(int argc, char **argv) {
        FunctionThatEscapesLocalObject();
        return ptr[argc];
    }


Compile :

.. code-block:: sh

    $ clang++ -O1 -g -fsanitize=memory -fno-omit-frame-pointer example.cpp -o example



Run :

.. code-block:: sh

    $ ./example
    ==12719== WARNING: MemorySanitizer: use-of-uninitialized-value
        #0 0x7f1030669d16 in main /tmp/example.cpp:11:9
        #1 0x7f102f17578f in __libc_start_main (/usr/lib/libc.so.6+0x300042078f)
        #2 0x7f1030615798 in _start (/tmp/example+0x35798)

    SUMMARY: MemorySanitizer: use-of-uninitialized-value /tmp/example.cpp:11 main
    Exiting
