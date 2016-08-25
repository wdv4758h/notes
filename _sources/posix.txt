========================================
POSIX
========================================

"POSIX" == "Portable Operating System Interface"

* `POSIX.1-2008 <http://pubs.opengroup.org/onlinepubs/9699919799/>`_

use "clock_gettime" instead of "gettimeofday"
=============================================

在 POSIX 2008 時，已經把 ``gettimeofday`` 淘汰，推薦使用 ``clock_gettime`` ，
目前 Linux 和 FreeBSD 都有支援，但是 Mac OS 和 Windows 都不支援。

::

    POSIX.1-2008 marks gettimeofday() as obsolete, recommending
    the use of clock_gettime(2) instead.

* `Linux FAQ for clock_gettime(CLOCK_REALTIME) <http://juliusdavies.ca/posix_clocks/clock_realtime_linux_faq.html>`_
* `Is gettimeofday() guaranteed to be of microsecond resolution? <http://stackoverflow.com/questions/88/is-gettimeofday-guaranteed-to-be-of-microsecond-resolution>`_
* `POSIX timers clock_gettime 分析 <http://www.bluezd.info/archives/336>`_
* `cppreference - Date and time utilities <http://en.cppreference.com/w/cpp/chrono>`_
* `std::chrono : typesafe time keeping in C++ <http://th.physik.uni-frankfurt.de/~baeuchle/downloads/30_std_chrono.pdf>`_
* `libstdc++ - chrono.cc <https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/src/c++11/chrono.cc>`_
* `libc++ - chrono.cpp <http://llvm.org/viewvc/llvm-project/libcxx/trunk/src/chrono.cpp?view=markup>`_
