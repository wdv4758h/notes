========================================
init systems
========================================

init 是 initialization 的縮寫，
在 Unix-like 系統中，指的是系統的第一隻程式，
會作為 daemon 一直存在，
直到系統關掉才結束，
也因此 init 會是系統上所有其他程式直接或間接的祖先，
pid 通常為 1。


* Research Unix-style/BSD-style
    - Research Unix init
        + 會去執行寫在 ``/etc/rc`` 的 shell scripts
        + 沒有 runlevels
        + 新軟體可能會需要去更動已經可以正常運作的檔案，有造成系統不能正常啟動的風險
    - BSD init (4.3BSD 之前)
        + 和  Research UNIX init 相同
    - BSD init (4.3BSD)
        + 加入 windowing system 支援 (例如 X)
        + 加入 ``/etc/rc.local`` 支援，會在 boot 的最後用 sub-shell 去執行，如此一來有很多程式不用直接去改 ``/etc/rc``
    - BSD rc.d system (源自 NetBSD 1.5，移植到 FreeBSD 5.0 以及其他 BSD 家族)
        + script 放在 ``/etc/rc.d`` 目錄底下
        + 每隻 script 標上 dependency tags
        + 執行順序由 rcorder script 決定
* SysV-style
    - SysV init
        + 源自 AT&T's UNIX System III，後來經過一些更動後發行於 UNIX System V
        + 事先會決定好 runlevels
        + runlevel 切換前會先執行一些 per-runlevel 的 scripts
* Replacements for init
    - systemd_, a full replacement for init in Linux with concurrent starting of services and other features, used by influential Linux distributions
    - Upstart_, a full replacement of init designed to start processes asynchronously initiated by Ubuntu
    - OpenRC_, a process spawner that utilizes system-provided init, while providing process isolation, parallelized startup, and service dependency; used by Gentoo and its derivatives
    - Mudur_, an init replacement written in Python and designed to start process asynchronously in use by the Pardus Linux distribution
    - ...


.. _Mudur: https://github.com/Pardus-Linux/mudur
.. _OpenRC: https://en.wikipedia.org/wiki/OpenRC
.. _Upstart: https://en.wikipedia.org/wiki/Upstart
.. _systemd: https://en.wikipedia.org/wiki/Systemd


Reference
========================================

* `Wikipedia - init <https://en.wikipedia.org/wiki/Init>`_
* `Wikipedia - Runlevel <https://en.wikipedia.org/wiki/Runlevel>`_
* `Wikipedia - systemd <https://en.wikipedia.org/wiki/Runleve://en.wikipedia.org/wiki/Systemd>`_
* `Unix and Linux startup scripts, Part 1 <http://aplawrence.com/Basics/unix-startup-scripts-1.html>`_
* `Unix and Linux startup scripts, Part 2 <http://aplawrence.com/Basics/unix-startup-scripts-2.html>`_
* `Unix and Linux startup scripts, Part 3 <http://aplawrence.com/Basics/unix-startup-scripts-3.html>`_
* `Unix and Linux startup scripts, Part 4, Systemd <http://aplawrence.com/Basics/unix-startup-scripts-4.html>`_
* `淺析 Linux 初始化 init 系統，第 1 部分: sysvinit <http://www.ibm.com/developerworks/cn/linux/1407_liuming_init1/>`_
* `淺析 Linux 初始化 init 系統，第 2 部分: UpStart <http://www.ibm.com/developerworks/cn/linux/1407_liuming_init2/index.html>`_
* `淺析 Linux 初始化 init 系統，第 3 部分: Systemd <http://www.ibm.com/developerworks/cn/linux/1407_liuming_init3/index.html>`_
* `An experiment in porting the Android init system to GNU/Linux <http://blog.darknedgy.net/technology/2015/08/05/0-androidinit/>`_
* `On portability of init systems <https://teythoon.cryptobitch.de/posts/on-portability-of-init-systems/>`_
