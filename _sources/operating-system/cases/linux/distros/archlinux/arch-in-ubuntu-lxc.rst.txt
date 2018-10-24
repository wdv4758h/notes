========================================
Arch Linux in Ubuntu LXC
========================================

Install pacman & pacstrap
========================================

.. code-block:: sh

    add-apt-repository ppa:thopiekar/pacman
    apt-get update
    apt-get install -y pacman-pm arch-install-scripts
    pacman-key --init


``/etc/pacman.conf`` ::

    [core]
    Include = /etc/pacman.d/mirrorlist

    [extra]
    Include = /etc/pacman.d/mirrorlist


``/etc/pacman.d/mirrorlist`` ::

    # Taiwan
    Server = http://archlinux.cs.nctu.edu.tw/$repo/os/$arch
    Server = http://ftp.tku.edu.tw/Linux/ArchLinux/$repo/os/$arch
    Server = http://shadow.ind.ntou.edu.tw/archlinux/$repo/os/$arch


Create Arch Linux container
========================================

.. code-block:: sh

    $ sudo lxc-create -t archlinux -n myarch
