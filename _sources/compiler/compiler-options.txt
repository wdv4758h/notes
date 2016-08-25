========================================
Compiler Options
========================================

GCC
------------------------------

Common
++++++++++++++++++++

* ``-Ofast`` : ``-O3`` + optimizations that are not valid for all standard-compliant programs
* ``-march=native`` : 針對現在的 CPU 做優化，出來的程式不保證在其他 CPU 上會 work
    - 通用於 GCC 和 Clang
* ``-flto`` : Link Time Optimization
* ``-m32`` : 32 bits
* ``-m64`` : 64 bits
* ``-dumpspecs`` : 產生 specs file
* ``-fPIC`` : generate position independent code
* ``-fpic`` : generate position independent code
    - platform-dependent
    - may produce smaller code than `-fPIC`
    - may be a little bit faster
* ``-march=native -Q --help=target`` : 輸出 GCC 在目前機器上使用 ``-march=native`` 參數會打開的優化選項
    - ``-Q --help=target`` 只適用於 GCC
* ``-fdump-tree-original``
* ``-D_FORTIFY_SOURCE``
    - http://stackoverflow.com/questions/13517526/difference-between-gcc-d-fortify-source-1-and-d-fortify-source-2
    - ``man 7 feature_test_macros``
    - 好像會有 function 的 memory (frame) 的 checksum 檢查，避免有蓋值發生？

::

    _FORTIFY_SOURCE (since glibc 2.3.4)
            Defining this macro causes some lightweight checks to be performed to detect some buffer overflow  errors
            when  employing  various  string  and  memory  manipulation functions (for example, memcpy(3), memset(3),
            stpcpy(3),  strcpy(3),  strncpy(3),  strcat(3),   strncat(3),   sprintf(3),   snprintf(3),   vsprintf(3),
            vsnprintf(3), gets(3), and wide character variants thereof).  For some functions, argument consistency is
            checked; for example, a check is made that open(2) has been supplied with a mode argument when the speci‐
            fied flags include O_CREAT.  Not all problems are detected, just some common cases.

            If  _FORTIFY_SOURCE  is  set  to  1,  with compiler optimization level 1 (gcc -O1) and above, checks that
            shouldn't change the behavior of conforming programs are performed.  With _FORTIFY_SOURCE set to 2,  some
            more checking is added, but some conforming programs might fail.

            Some of the checks can be performed at compile time (via macros logic implemented in header files), and
            result in compiler warnings; other checks take place at run time, and result in a run-time error  if  the
            check fails.

            Use of this macro requires compiler support, available with gcc(1) since version 4.0.


* ``-E -v -``
    - ``[gcc|clang] -v -E -march=native -``
* ``-rdynamic``
    - http://stackoverflow.com/questions/10599038/can-i-skip-cmake-compiler-tests-or-avoid-error-unrecognized-option-rdynamic
    - http://stackoverflow.com/questions/31212393/unrecognized-command-line-option-rdynamic-on-gcc-v4-9-2




Reference
========================================

* `What is the difference between '-fpic' and '-fPIC' gcc parameters? <http://stackoverflow.com/questions/3544035/what-is-the-difference-between-fpic-and-fpic-gcc-parameters>`_
* `Neovim - Gradually introduce more compiler flags <https://github.com/neovim/neovim/issues/343>`_
* `Hacker News - What Are Your GCC Flags? <https://news.ycombinator.com/item?id=7371806>`_
* `What Are Your GCC Flags ? <http://blog.httrack.com/blog/2014/03/09/what-are-your-gcc-flags/>`_
