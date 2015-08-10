========================================
Valgrind Resource Collection
========================================


Valgrind Articles
========================================

* `Julian Seward's blog <https://blog.mozilla.org/jseward?s=Valgrind>`_



Valgrind Slides
========================================



Projects with Valgrind
========================================

* `Servo <https://github.com/servo/servo/wiki/Debugging>`_
* Firefox
* `Cython <https://github.com/cython/cython/wiki/UsingValgrindToDebug>`_
* `scikit-learn <http://scikit-learn.org/stable/developers/debugging.html>`_
* `Chromium <https://www.chromium.org/developers/how-tos/using-valgrind>`_



Papers
========================================

* `[2015] MemorySanitizer: fast detector of uninitialized memory use in C++ <http://research.google.com/pubs/pub43308.html>`_
* `[2014] ACDC-JS: explorative benchmarking of javascript memory management <http://research.google.com/pubs/pub43216.html>`_
* `[2013] JSWhiz - Static Analysis for JavaScript Memory Leaks <http://research.google.com/pubs/pub40738.html>`_
* `[2012] AddressSanitizer: A Fast Address Sanity Checker <http://research.google.com/pubs/pub37752.html>`_
* `[2012] Transparent Dynamic Instrumentation <http://research.google.com/pubs/archive/38225.pdf>`_
* `[2011] Practical Memory Checking with Dr. Memory <http://research.google.com/pubs/pub37274.html>`_
* `[2011] Dynamic cache contention detection in multi-threaded applications <http://research.google.com/pubs/pub37659.html>`_
* `[2011] Dynamic Race Detection with LLVM Compiler <http://research.google.com/pubs/pub37278.html>`_
* `[2007] Flayer: Exposing Application Internals <http://research.google.com/pubs/archive/33253.pdf>`_



Related Projects
========================================

* `Dr. Memory <https://github.com/DynamoRIO/drmemory>`_
* DRD
* rr
* LeakSanitizer
    - https://www.chromium.org/developers/testing/leaksanitizer
    - AddressSanitizer 的一部份
* Heap Leak Checker
    - deprecated (use LeakSanitizer instead)
    - google-perftools 的一部份



Comparison Of Memory Tools
========================================

Table Modify from `address-sanitizer - ComparisonOfMemoryTools <https://code.google.com/p/address-sanitizer/wiki/ComparisonOfMemoryTools>_



+------------+------------------+---------------------+--------------------+
|            | AddressSanitizer | Valgrind (Memcheck) | Valgrind (SGCheck) |
+============+==================+=====================+====================+
| technology | CTI              | DBI                 | DBI                |
+------------+------------------+---------------------+--------------------+
| ARCH       | x86,             | x86,                | x86,               |
|            | x86_64,          | x86_64,             | x86_64,            |
|            | ARM,             | ARM,                | ARM,               |
|            | PPC,             | PPC,                | PPC,               |
|            | ...              | ...                 | ...                |
+------------+------------------+---------------------+--------------------+
| OS         | Linux,           | Linux,              | Linux,             |
|            | FreeBSD,         | FreeBSD,            | FreeBSD,           |
|            | Android,         | Android,            | Android,           |
|            | Mac,             | Mac,                | Mac,               |
|            | Windows,         | ...                 | ...                |
|            | ...              |                     |                    |
+------------+------------------+---------------------+--------------------+
| Slowdown   | 2x               | 20x                 |                    |
+------------+------------------+---------------------+--------------------+
| Detects:   |                  |                     |                    |
+------------+------------------+---------------------+--------------------+
| Heap OOB   | O                | O                   | X                  |
+------------+------------------+---------------------+--------------------+
| Stack OOB  | O                | X                   | O                  |
+------------+------------------+---------------------+--------------------+
| Global OOB | O                | X                   | O                  |
+------------+------------------+---------------------+--------------------+
| UAF        | O                | O                   | X                  |
+------------+------------------+---------------------+--------------------+
| UAR        | O                | X                   | X                  |
+------------+------------------+---------------------+--------------------+
| UMR        | X                | O                   | X                  |
+------------+------------------+---------------------+--------------------+
| Leaks      | O                | O                   | X                  |
+------------+------------------+---------------------+--------------------+

+------+---------------------------------------+
| 縮寫 | 全名                                  |
+======+=======================================+
| CTI  | Compile-Time Instrumentation          |
+------+---------------------------------------+
| DBI  | Dynamic Binary Instrumentation        |
+------+---------------------------------------+
| UMR  | Uninitialized Memory Reads            |
+------+---------------------------------------+
| UAF  | Use-After-Free (aka dangling pointer) |
+------+---------------------------------------+
| UAR  | Use-After-Return                      |
+------+---------------------------------------+
| OOB  | Out-Of-Bounds                         |
+------+---------------------------------------+
