========================================
Hardware
========================================

CPU
========================================

* `Arch Wiki - Microcode <https://wiki.archlinux.org/index.php/microcode>`_

.. code-block:: sh

    $ sudo pacman -S intel-ucode

    # update Grub
    $ sudo grub-mkconfig -o /boot/grub/grub.cfg

    # systemd-boot (UEFI)
    $ edit /boot/loader/entries/*.conf
    title   Arch Linux
    linux   /vmlinuz-linux
    initrd  /intel-ucode.img
    initrd  /initramfs-linux.img
    options ...

    # Check
    $ grep microcode /proc/cpuinfo
    microcode	: 0x1b
    microcode	: 0x1b
    microcode	: 0x1b
    microcode	: 0x1b
    $ dmesg | grep microcode
    [    0.000000] microcode: CPU0 microcode updated early to revision 0x1b, date = 2014-05-29
    [    0.139891] microcode: CPU2 microcode updated early to revision 0x1b, date = 2014-05-29
    [    0.630582] microcode: CPU0 sig=0x306a9, pf=0x10, revision=0x1b
    [    0.630592] microcode: CPU1 sig=0x306a9, pf=0x10, revision=0x1b
    [    0.630602] microcode: CPU2 sig=0x306a9, pf=0x10, revision=0x1b
    [    0.630609] microcode: CPU3 sig=0x306a9, pf=0x10, revision=0x1b
    [    0.630664] microcode: Microcode Update Driver: v2.00 <tigran@aivazian.fsnet.co.uk>, Peter Oruba



lstopo - Show the topology of the system
========================================

.. code-block:: sh

    $ sudo pacman -S hwloc
    $ lstopo


Output :

(My Laptop)

.. image:: /images/archlinux/lstopo-laptop.png


(VM on ESXi)

.. image:: /images/archlinux/lstopo-esxi.png
