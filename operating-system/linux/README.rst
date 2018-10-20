========================================
Linux
========================================

* Scheduler
    - maximize throughput
    - maximize responsiveness for interactive users
    - minimize latency
    - minimize access times for the scheduler
* Process Scheduler
    - O(n)
        + Linux 2.4 ~ 2.6.0 以前
    - O(1)
        + Linux 2.6.0 ~ 2.6.22
    - CFS (Completely Fair Scheduler)
        + Linux 2.6.23+
    - BFS (Brain Fuck Scheduler)
    - MuQSS
    - PDS-mq (Priority and Deadline based Skiplist multiple queue Scheduler)
* Disk Scheduler
    - Budget Fair Queue
* RCU
    - preemptible tree-based hierarchical
* Kernel Preemption
* 網路 (Network)
    - TCP BBR Congestion Control
    - Smaller TX Net Queues
* Realtime

* 基於 Linux 官方正式釋出的改動
    - `Hardended <https://github.com/anthraxx/linux-hardened>`_
        + 針對安全性
        + AppArmor
        + SELinux
    - Zen
        + 針對日常使用做優化
    - linux-ck
        + Con Kolivas
        + 針對一般桌面系統的回應速度做優化
    - pf-kernel
        + PDS CPU scheduler
        + UKSM
    - `rt <https://wiki.linuxfoundation.org/realtime/start>`_
        + 一群開發者維護的 Realtime 相關 patches
* 部落格
    - `Con Kolivas - -ck <https://ck-hack.blogspot.com/>`_
    - `Alfred Chen - PDS <https://cchalpha.blogspot.com/>`_

----

* `建立自己的 Linux 系統 (Build Your Own Linux) <build-your-own-linux/>`_
* `Realtime Kernel <realtime.rst>`_
* `Kernel Module <Kernel-modules.rst>`_
* `Budget Fair Queueing Storage-I/O Scheduler <bfq.rst>`_
* `Linux Distro <distro.rst>`_
* `Linux Driver <driver.rst>`_
* `Linux IPC <ipc.rst>`_
* `Linux Kernel <kernel.rst>`_
* `seccomp <seccomp.rst>`_
* `SELinux <selinux.rst>`_
* `vDSO <vdso.rst>`_
