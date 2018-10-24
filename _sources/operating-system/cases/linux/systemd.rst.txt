========================================
systemd
========================================


.. contents:: 目錄


設計
========================================

systemd 的設計緣由可以參考 Lennart Poettering 在 2010 年的文章
`Rethinking PID 1 <http://0pointer.net/blog/projects/systemd.html>`_ ，
在此文章發出的同時也釋出了 systemd 實做。


優勢
------------------------------


劣勢
------------------------------



hostnamectl
========================================

.. code-block:: sh

    $ hostnamectl
         Static hostname: n/a
      Transient hostname: archlinux
               Icon name: computer-laptop
                 Chassis: laptop
              Machine ID: 00000000000000000000000000000000
                 Boot ID: 00000000000000000000000000000000
        Operating System: Arch Linux
                  Kernel: Linux 4.15.11-1-ARCH
            Architecture: x86-64


.. code-block:: sh

    $ hostnamectl set-hostname mymachine
       Static hostname: mymachine
             Icon name: computer-laptop
               Chassis: laptop
            Machine ID: d24ae6664f914902a4cce7ef81cce921
               Boot ID: ed185744bb824ad5b0be8eae0040814e
      Operating System: Arch Linux
                Kernel: Linux 4.15.11-1-ARCH
          Architecture: x86-64



systemd-resolve
========================================

.. code-block:: sh

    # DNS Server 查詢的狀態
    $ systemd-resolve --status



參考
========================================

* `systemd System and Service Manager <http://www.freedesktop.org/wiki/Software/systemd/>`_
    - systemd 在 freedesktop.org 的網站
    - 有許多相關文章、Documentation 的連結
* `[GitHub] systemd/systemd <https://github.com/systemd/systemd>`_
* `[2013] The Biggest Myths <http://0pointer.net/blog/projects/the-biggest-myths.html>`_
    - 這篇文章提出了 30 個作者碰到的迷思 XD
    - systemd 有 configuration 可以選，如果全選的話會編成許多不同 binary，分別儘量用最小的權限平行執行。
    - 速度不是 systemd 的主要目標，但是是 systemd 把事情最對的一大副作用 (?)
    - 可以用任何語言來撰寫 systemd 的 service
* `[2011] Why systemd? <http://0pointer.de/blog/projects/why.html>`_
* `Arch Wiki - systemd <https://wiki.archlinux.org/index.php/systemd>`_

* `Systemd Essentials: Working with Services, Units, and the Journal <https://www.digitalocean.com/community/tutorials/systemd-essentials-working-with-services-units-and-the-journal>`_
* `How To Use Systemctl to Manage Systemd Services and Units <https://www.digitalocean.com/community/tutorials/how-to-use-systemctl-to-manage-systemd-services-and-units>`_
* `How To Use Journalctl to View and Manipulate Systemd Logs <https://www.digitalocean.com/community/tutorials/how-to-use-journalctl-to-view-and-manipulate-systemd-logs>`_
* `Understanding Systemd Units and Unit Files <https://www.digitalocean.com/community/tutorials/understanding-systemd-units-and-unit-files>`_


* `Systemd is the best example of Suck. <http://suckless.org/sucks/systemd>`_
* `Things I learned about systemd <https://nelsonslog.wordpress.com/2016/04/30/things-i-learned-about-systemd/>`_


* `systemd in 2018 <https://media.ccc.de/v/ASG2018-230-systemd_in_2018>`_
* `BSDCan 2018 - The Tragedy of systemd <https://www.bsdcan.org/2018/schedule/track/Plenary/927.en.html>`_
* `2018 Demystifying systemd <https://www.redhat.com/it/about/videos/summit-2018-demystifying-systemd>`_

* `A list of non-systemd distributions (revisited) <https://sysdfree.wordpress.com/2018/05/09/135/>`_
