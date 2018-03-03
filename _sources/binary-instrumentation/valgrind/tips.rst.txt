========================================
Valgrind Tips
========================================

Using Valgrind to get stack traces
========================================

Example
------------------------------

Source Code：

.. code-block:: c

    #include <valgrind/valgrind.h>

    void f() {
        // VALGRIND_PRINTF_BACKTRACE is a variadic printf-style function
        VALGRIND_PRINTF_BACKTRACE("I have backtrace for %s()", "f");
    }

    void g() {
        VALGRIND_PRINTF_BACKTRACE("I have backtrace for g()");
        f();
    }

    int main(int argc, char *argv[]) {
        g();
    }

Build：

.. code-block:: sh

    $ gcc example.c -o example

Run：

.. code-block:: sh

    $ valgrind --tool=none ./example
    ==30795== Nulgrind, the minimal Valgrind tool
    ==30795== Copyright (C) 2002-2013, and GNU GPL'd, by Nicholas Nethercote.
    ==30795== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==30795== Command: ./example
    ==30795==
    **30795** I have backtrace for g()   at 0x4006B5: VALGRIND_PRINTF_BACKTRACE (in /tmp/example)
    ==30795==    by 0x400703: g (in /tmp/example)
    ==30795==    by 0x400729: main (in /tmp/example)
    **30795** I have backtrace for f()   at 0x4006B5: VALGRIND_PRINTF_BACKTRACE (in /tmp/example)
    ==30795==    by 0x4006ED: f (in /tmp/example)
    ==30795==    by 0x40070D: g (in /tmp/example)
    ==30795==    by 0x400729: main (in /tmp/example)
    ==30795==

Reference
------------------------------

* `Using Valgrind to get stack traces <https://blog.mozilla.org/nnethercote/2011/01/11/using-valgrind-to-get-stack-traces/>`_
