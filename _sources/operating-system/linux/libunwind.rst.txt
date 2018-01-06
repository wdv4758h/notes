========================================
libunwind
========================================

Introduction
========================================

libunwind 是一個跨平台的 C API，
提供取得程式 call-chain 的方式，
原先由 HP 開發，
以 MIT 授權釋出。

一般會把 call stack 上加入 subroutine 進入點的動作稱為 ``winding`` ，
而反過來則稱為 ``unwinding`` ，
C 的 return 就是一個 ``unwinding`` 的例子，
但是使用 libunwind 的話可以一次 unwind 好幾個 function，
除此之外可以取得 call stack 的資訊，
藉此獲得 backtrace、原先的呼叫點。


Example
========================================

Build libunwind
------------------------------

.. code-block:: sh

    $ git clone git://git.sv.gnu.org/libunwind.git
    $ cd libunwind
    $ ./autogen.sh
    $ ./configure --prefix=/usr/local/
    $ make -j8
    $ make install

    # test
    $ make check

    # bench
    $ cd tests
    $ make perf

Backtrace
------------------------------

``backtrace.c`` :

.. code-block:: c

    #define UNW_LOCAL_ONLY  // We only need local unwinder.
                            // On x86_64 machine, you will need to link with libunwind-x86_64 without this define.

    #include "libunwind.h"

    #include <stdio.h>      // printf

    void show_backtrace() {
        unw_cursor_t cursor;
        unw_context_t uc;
        unw_word_t ip, sp;
        char buf[4096];
        unw_word_t offset;
        unw_getcontext(&uc);            // store registers
        unw_init_local(&cursor, &uc);   // initialze with context

        printf("==========\n");

        while (unw_step(&cursor) > 0) {                         // unwind to older stack frame
            unw_get_reg(&cursor, UNW_REG_IP, &ip);              // read register, rip
            unw_get_reg(&cursor, UNW_REG_SP, &sp);              // read register, rbp
            unw_get_proc_name(&cursor, buf, 4095, &offset);     // get name and offset
            printf("0x%016lx <%s+0x%lx>\n", ip, buf, offset);   // x86_64, unw_word_t == uint64_t
        }

        printf("==========\n");
    }

    void func() {
        show_backtrace();
    }

    int main() {
        show_backtrace();
        func();
        show_backtrace();
        return 0;
    }



Build and Run :

.. code-block:: sh

    # libunwind.h use sys/ucontext.h, which need GNU11 instead of pure C11
    $ gcc -std=gnu11 -Wall -lunwind backtrace.c -o backtrace
    $ ./backtrace
    ==========
    0x0000000000400914 <main+0x14>
    0x00007fa19af32790 <__libc_start_main+0xf0>
    0x00000000004006f9 <_start+0x29>
    0x0000000000000000 <+0x29>
    ==========
    ==========
    0x00000000004008f9 <func+0x9>
    0x0000000000400919 <main+0x19>
    0x00007fa19af32790 <__libc_start_main+0xf0>
    0x00000000004006f9 <_start+0x29>
    0x0000000000000000 <+0x29>
    ==========
    ==========
    0x000000000040091e <main+0x1e>
    0x00007fa19af32790 <__libc_start_main+0xf0>
    0x00000000004006f9 <_start+0x29>
    0x0000000000000000 <+0x29>
    ==========

Unwind
------------------------------

``unwind.c`` :

.. code-block:: c

    #define UNW_LOCAL_ONLY  // We only need local unwinder.
                            // On x86_64 machine, you will need to link with libunwind-x86_64 without this define.

    #include "libunwind.h"

    #include <stdio.h>      // printf

    void skip_func() {
        unw_cursor_t cursor;
        unw_context_t uc;

        unw_getcontext(&uc);
        unw_init_local(&cursor, &uc);
        unw_step(&cursor);
        unw_step(&cursor);
        unw_resume(&cursor);            // restore the machine state
        printf("will be skipped\n");    // won't be executed
    }

    void skipped_func() {
        skip_func();
        printf("will be skipped\n");    // won't be executed
    }

    int main() {
        printf("start\n");
        skipped_func();
        printf("end\n");
        return 0;
    }



Build and Run :

.. code-block:: sh

    $ gcc -std=gnu11 -Wall -lunwind unwind.c
    $ ./unwind
    start
    end


Use getcontext/setcontext to unwind
-----------------------------------

[待研究細節] source code 來自《Binary Hacks》，
目前嘗試 x86 版 (``-m32``) 用 gcc 邊完後可以正常執行完，
clang 編的話則是結束後會 coredump。x86_64 版本則是連用 gcc 編都會在結束時 coredump。
需要再研究細節，還有結構需要的調整。

x86
++++++++++++++++++++

.. code-block:: c

    #define _GNU_SOURCE

    #include <stdio.h>
    #include <ucontext.h>

    typedef struct layout {
        struct layout *ebp;
        void *ret;
    } layout;

    void skip_func() {
        ucontext_t uc;
        layout *ebp = __builtin_frame_address(0);
        ebp = ebp->ebp;

        getcontext(&uc);
        uc.uc_mcontext.gregs[REG_EIP] = (unsigned int)ebp->ret;
        uc.uc_mcontext.gregs[REG_EBP] = (unsigned int)ebp->ebp;
        setcontext(&uc);
        printf("will be skipped\n");    // won't be executed
    }

    void skipped_func() {
        skip_func();
        printf("will be skipped\n");    // won't be executed
    }

    int main() {
        printf("start\n");
        skipped_func();
        printf("end\n");
        return 0;
    }



x86_64
++++++++++++++++++++

.. code-block:: c

    #define _GNU_SOURCE

    #include <stdio.h>
    #include <ucontext.h>

    typedef struct layout {
        struct layout *rbp;
        void *ret;
    } layout;

    void skip_func() {
        ucontext_t uc;
        layout *rbp = __builtin_frame_address(0);
        rbp = rbp->rbp;

        getcontext(&uc);
        uc.uc_mcontext.gregs[REG_RIP] = (unsigned long)rbp->ret;
        uc.uc_mcontext.gregs[REG_RBP] = (unsigned long)rbp->rbp;
        setcontext(&uc);
        printf("will be skipped\n");    // won't be executed
    }

    void skipped_func() {
        skip_func();
        printf("will be skipped\n");    // won't be executed
    }

    int main() {
        printf("start\n");
        skipped_func();
        printf("end\n");
        return 0;
    }


libunwind - test ptraace
------------------------------

* http://git.savannah.gnu.org/cgit/libunwind.git/plain/tests/test-ptrace.c


Reference
========================================

* `The libunwind project <http://www.nongnu.org/libunwind/>`_
* `libunwind documentation <http://www.nongnu.org/libunwind/docs.html>`_
* `Wikipedia - Call stack <https://en.wikipedia.org/wiki/Call_stack>`_
* `Wikipedia - setcontext <https://en.wikipedia.org/wiki/Setcontext>`_
    - specified in POSIX.1-2001
    - POSIX.1-2004 obsoleted these functions
    - in POSIX.1-2008 they were removed
* 《Binary Hacks》 - #73
* `Linaro Wiki - ZachWelch - libunwind <https://wiki.linaro.org/ZachWelch/Sandbox/libunwind>`_
* `Linaro Wiki - KenWerner - libunwind <https://wiki.linaro.org/KenWerner/Sandbox/libunwind>`_
* `Linaro - ARM32/64: perf: dwarf stack frame unwinding support <https://wiki.linaro.org/LEG/Engineering/TOOLS/perf-callstack-unwinding>`_
* `Linaro - Git Hosting - libunwind.git <http://git.linaro.org/people/renato.golin/libunwind.git>`_
* `[2011] Stack frame unwinding on ARM <https://wiki.linaro.org/KenWerner/Sandbox/libunwind?action=AttachFile&do=get&target=libunwind-LDS.pdf>`_
* `libunwind - src/x86_64/getcontext.S <http://git.savannah.gnu.org/gitweb/?p=libunwind.git;a=blob;f=src/x86_64/getcontext.S;hb=HEAD>`_
* `libunwind - src/x86_64/setcontext.S <http://git.savannah.gnu.org/gitweb/?p=libunwind.git;a=blob;f=src/x86_64/setcontext.S;hb=HEAD>`_
* `stacktrace with libunwind and elfutils <https://gist.github.com/banthar/1343977>`_
* `libdwarf and libunwind <http://cwndmiao.github.io/programming%20tools/2013/11/26/Dwarf/>`_
* `[LLVM] New libunwind implementation in libc++abi <http://blog.llvm.org/2013/10/new-libunwind-implementation-in-libcabi.html>`_
    - `[GitHub] llvm-mirror/libunwind <https://github.com/llvm-mirror/libunwind>`_
