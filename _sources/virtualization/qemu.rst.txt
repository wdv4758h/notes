========================================
QEMU
========================================


.. contents:: 目錄


chroot with QEMU
========================================

Arch Linux:

.. code-block:: sh

    # qemu-user-static + binfmt_misc + chroot

Ubuntu:

.. code-block:: sh

    # Setting up an ARM chroot on your x86 machine
    sudo apt-get update
    sudo apt-get install debootstrap qemu-user-static
    sudo qemu-debootstrap --arch armhf trusty eabi-chroot
    sudo chroot eabi-chroot/



參考：

* `Gentoo Wiki - Embedded Handbook/General/Compiling with qemu user chroot <https://wiki.gentoo.org/wiki/Embedded_Handbook/General/Compiling_with_qemu_user_chroot>`_
* `Setup armv7h chroot under x86_64 host <https://gist.github.com/mikkeloscar/a85b08881c437795c1b9>`_



參考
========================================
