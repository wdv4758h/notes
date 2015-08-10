========================================
Compiler Options
========================================

GCC
------------------------------

Common
++++++++++++++++++++

* ``-Ofast`` : ``-O3`` + optimizations that are not valid for all standard-compliant programs
* ``-march=native`` : 針對現在的 CPU 做優化，出來的程式不保證在其他 CPU 上會 work
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
* ``-fdump-tree-original``
* ``-D_FORTIFY_SOURCE``
    - http://stackoverflow.com/questions/13517526/difference-between-gcc-d-fortify-source-1-and-d-fortify-source-2


Reference
========================================

* `What is the difference between '-fpic' and '-fPIC' gcc parameters? <http://stackoverflow.com/questions/3544035/what-is-the-difference-between-fpic-and-fpic-gcc-parameters>`_
* `Neovim - Gradually introduce more compiler flags <https://github.com/neovim/neovim/issues/343>`_
* `Hacker News - What Are Your GCC Flags? <https://news.ycombinator.com/item?id=7371806>`_
* `What Are Your GCC Flags ? <http://blog.httrack.com/blog/2014/03/09/what-are-your-gcc-flags/>`_
