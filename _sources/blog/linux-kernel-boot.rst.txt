:title: Linux Kernel Booting Process
:slug: linux-kernel-booting-process
:date: 2014-12-24 20:02
:modified: 2014-12-24 20:02
:category: Misc
:tags: linux
:author: wdv4758h
:summary:

- `Linux/Documentation/x86/boot.txt <http://lxr.free-electrons.com/source/Documentation/x86/boot.txt>`_
- `Wikipedia - vmlinux <https://en.wikipedia.org/wiki/Vmlinux>`_
    * ``vm`` is for virtual memory
    * the Linux kernel in an statically linked executable file format
- vmlinuz
    * compressed vmlinux
- `What is the difference between the following kernel Makefile terms: vmlinux, vmlinuz, vmlinux.bin, zimage & bzimage? <http://unix.stackexchange.com/questions/5518/what-is-the-difference-between-the-following-kernel-makefile-terms-vmlinux-vml>`_
- `Arch Wiki - Arch boot process <https://wiki.archlinux.org/index.php/Arch_boot_process>`_



.. raw:: html

    <iframe src="//www.slideshare.net/slideshow/embed_code/37390677" width="510" height="420" frameborder="0" marginwidth="0" marginheight="0" scrolling="no" style="border:1px solid #CCC; border-width:1px; margin-bottom:5px; max-width: 100%;" allowfullscreen> </iframe> <div style="margin-bottom:5px"> <strong> <a href="//www.slideshare.net/shimosawa/linux-kernel-booting-process-1-for-nlkb" title="Linux Kernel Booting Process (1) - For NLKB" target="_blank">Linux Kernel Booting Process (1) - For NLKB</a> </strong> from <strong><a href="//www.slideshare.net/shimosawa" target="_blank">shimosawa</a></strong> </div>

.. raw:: html

    <iframe src="//www.slideshare.net/slideshow/embed_code/37390718" width="595" height="485" frameborder="0" marginwidth="0" marginheight="0" scrolling="no" style="border:1px solid #CCC; border-width:1px; margin-bottom:5px; max-width: 100%;" allowfullscreen> </iframe> <div style="margin-bottom:5px"> <strong> <a href="//www.slideshare.net/shimosawa/nlkb20140727" title="Linux Kernel Booting Process (2) - For NLKB" target="_blank">Linux Kernel Booting Process (2) - For NLKB</a> </strong> from <strong><a href="//www.slideshare.net/shimosawa" target="_blank">shimosawa</a></strong> </div>


.. image:: /images/linux/linux-kernel-boot.jpg
    :alt: linux kernel boot

bzImage
========================================

bzImage = big zImage

.. image:: /images/linux/linux-kernel-file.png
    :alt: linux kernel file

Linux <= 2.6.22
------------------------------

* bbootsect (bootsect.o):
* bsetup (setup.o)
* bvmlinux (head.o, misc.o, piggy.o)

.. image:: /images/linux/bzimage.png
    :alt: bzimage

``piggy.o`` contains the **gzipped** ``vmlinux`` file in its data section (``ELF``) (see compressed/Makefile piggy.o).
All source files mentioned are in ``arch/i386/boot/``

Linux >= 2.6.23
------------------------------

merged ``bbootsect`` and ``bsetup`` into one (``header.o``)

initramfs
========================================

- `深入理解 Linux 2.6 的 initramfs 機制 (上) - Jserv <http://blog.linux.org.tw/~jserv/archives/001954.html>`_
- `Wikipedia - initramfs <https://en.wikipedia.org/wiki/Initramfs>`_
- `Linux/Documentation/filesystems/ramfs-rootfs-initramfs.txt <http://lxr.free-electrons.com/source/Documentation/filesystems/ramfs-rootfs-initramfs.txt>`_
- `Arch Wiki - mkinitcpio <https://wiki.archlinux.org/index.php/mkinitcpio>`_

zlib
========================================

an abstraction of the ``DEFLATE`` compression algorithm used in the ``gzip`` file compression program

- `Wikipedia - zlib <https://en.wikipedia.org/wiki/Zlib>`_

- Applications
    * Linux Kernel
    * libpng
    * Apache
    * OpenSSH
    * OpenSSL
    * FFmpeg
    * rsync
    * dpkg
    * Subversion
    * Git
    * PostgreSQL
    * ...

feature : code is portable, liberally licensed, and has a relatively small memory footprint

