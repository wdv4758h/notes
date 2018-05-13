========================================
Optimizations
========================================


.. contents:: 目錄


PGO (Profile-Guided Optimizations)
========================================

* `Dr.Dobb's - Profile-Guided Optimizations <http://www.drdobbs.com/profile-guided-optimizations/184410561>`_
* `Wikipedia - Profile-guided optimization <https://en.wikipedia.org/wiki/Profile-guided_optimization>`_
* GCC
    - ``-fprofile-generate``
    - ``-fprofile-use``



IPO (Interprocedural Optimization)
========================================

* `Wikipedia - Interprocedural optimization <https://en.wikipedia.org/wiki/Interprocedural_optimization>`_



Misc
========================================

* ``-O3`` 就正常 general 的優化盡量開
* ``-Ofast`` 除了 ``-O3`` 的參數外，還會加一些更 aggressive 的參數（通常跟數學運算有關
* ``-march=native`` 是以目前在編譯的 CPU 為目標對象做優化，可能會利用到一些特定 CPU 才有的指令（例如 SSE、AVX）
* ``-flto`` 是開 link time 的優化



參考
========================================

* `Gentoo Wiki - GCC Optimization <https://wiki.gentoo.org/wiki/GCC_optimization>`_
* `Stack Overflow - Clang optimization levels <http://stackoverflow.com/questions/15548023/clang-optimization-levels>`_
