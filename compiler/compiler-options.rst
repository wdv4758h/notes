========================================
Compiler Options
========================================

GCC
------------------------------

* ``-Ofast`` : ``-O3`` + optimizations that are not valid for all standard-compliant programs
* ``-march=native`` : 針對現在的 CPU 做優化，出來的程式不保證在其他 CPU 上會 work
* ``-flto`` : Link Time Optimization
