========================================
coredump
========================================


.. contents:: 目錄


介紹
========================================

路徑：

.. code-block:: sh

    # 如果以 "|" 為開頭的話，就會把後面當成指令執行
    $ cat /proc/sys/kernel/core_pattern
    |/usr/lib/systemd/systemd-coredump %P %u %g %s %t %c %e



Arch Linux 上預設的 coredump 位置： ``/var/lib/systemd/coredump/``

.. code-block:: sh

    $ coredumpctl gdb PATTERN

::

    (gdb) info registers
    eax            0x7e	126
    ecx            0x7fffff81	2147483521
    edx            0xf76d0870	-143849360
    ebx            0x0	0
    esp            0xffddfb60	0xffddfb60
    ebp            0x3167953b	0x3167953b
    esi            0x1	1
    edi            0xf76cf000	-143855616
    eip            0x5f892161	0x5f892161
    eflags         0x10286	[ PF SF IF RF ]
    cs             0x23	35
    ss             0x2b	43
    ds             0x2b	43
    es             0x2b	43
    fs             0x0	0
    gs             0x63	99


    (gdb) info registers
    rax            0x0	0
    rbx            0x0	0
    rcx            0x0	0
    rdx            0x7fffffffe8e8	140737488349416
    rsi            0x7fffffffe8d8	140737488349400
    rdi            0x1	1
    rbp            0x7fffffffe7e0	0x7fffffffe7e0
    rsp            0x7fffffffe7d0	0x7fffffffe7d0
    r8             0x4006d0	4196048
    r9             0x7ffff7dea4e0	140737351951584
    r10            0x833	2099
    r11            0x7ffff7a596a0	140737348212384
    r12            0x4004f0	4195568
    r13            0x7fffffffe8d0	140737488349392
    r14            0x0	0
    r15            0x0	0
    rip            0x4005ff	0x4005ff <hook+8>
    eflags         0x202	[ IF ]
    cs             0x33	51
    ss             0x2b	43
    ds             0x0	0
    es             0x0	0
    fs             0x0	0
    gs             0x0	0



參考
========================================

* `Arch Wiki - Core dump <https://wiki.archlinux.org/index.php/Core_dump>`_
* `DMTN-004 - Debugging in Docker Containers <https://dmtn-004.lsst.io/>`_
