========================================
Thread Stack
========================================

檢查系統上每個 thread stack 可以拿到多少 RAM：

.. code-block:: sh

    # Linux
    $ ulimit -s
    8192    # 8192 KB = 8 MB

    $ ulimit -a
    Maximum size of core files created                           (kB, -c) 0
    Maximum size of a process’s data segment                     (kB, -d) unlimited
    Maximum size of files created by the shell                   (kB, -f) unlimited
    Maximum size that may be locked into memory                  (kB, -l) 1024
    Maximum resident set size                                    (kB, -m) unlimited
    Maximum number of open file descriptors                          (-n) 1024
    Maximum stack size                                           (kB, -s) 8192
    Maximum amount of cpu time in seconds                   (seconds, -t) unlimited
    Maximum number of processes available to a single user           (-u) 23231
    Maximum amount of virtual memory available to the shell      (kB, -v) unlimited

    # FreeBSD
    $ ulimit -s
    40960

    $ ulimit -a
    cpu time               (seconds, -t)  5400
    file size           (512-blocks, -f)  unlimited
    data seg size           (kbytes, -d)  25600
    stack size              (kbytes, -s)  40960
    core file size      (512-blocks, -c)  unlimited
    max memory size         (kbytes, -m)  65536
    locked memory           (kbytes, -l)  40960
    max user processes              (-u)  256
    open files                      (-n)  100
    virtual mem size        (kbytes, -v)  unlimited
    swap limit              (kbytes, -w)  unlimited
    sbsize                   (bytes, -b)  unlimited
    pseudo-terminals                (-p)  unlimited

    # Windows 上預設 thread stack limit 是 1 MB


設定檔： ``/etc/security/limits.conf``

ex: ::

    * soft stack 2048
    * hard stack 2048


man ``pthread_create`` ::

    On **Linux/x86-32**, the default stack size for a new thread is **2 megabytes**.
    Under the NPTL threading implementation,
    if the **RLIMIT_STACK** soft resource limit at the time the program started has any value other than "unlimited",
    then it determines the default stack size of new threads.
    Using **pthread_attr_setstacksize**(3),
    the stack size attribute can be explicitly set in the attr argument used to create a thread,
    in order to obtain a stack size other than the default.


* pthread_attr_setstacksize


Reference
========================================

* `Wikipedia - Native POSIX Thread Library (NPTL) <https://en.wikipedia.org/wiki/Native_POSIX_Thread_Library>`_
* `Wikipedia - Futex <https://en.wikipedia.org/wiki/Futex>`_
* `Tweaking stack size of Linux processes to reduce swapping <http://linuxtips.manki.in/2011/11/tweaking-stack-size-of-linux-processes.html>`_
* `NPTL Optimization for Lightweight Embedded Devices <https://www.kernel.org/doc/ols/2011/ols2011-lim.pdf>`_
* `Why does Linux use per-thread kernel stacks? <http://www.quora.com/Why-does-Linux-use-per-thread-kernel-stacks>`_
* `Light-Weight Processes: Dissecting Linux Threads <http://opensourceforu.efytimes.com/2011/08/light-weight-processes-dissecting-linux-threads/>`_
