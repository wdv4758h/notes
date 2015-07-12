========================================
Compiler Options
========================================

GCC
------------------------------

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


Reference
========================================

* `What is the difference between '-fpic' and '-fPIC' gcc parameters? <http://stackoverflow.com/questions/3544035/what-is-the-difference-between-fpic-and-fpic-gcc-parameters>`_
