:title: QEMU - First Step
:slug: qemu-first-step
:date: 2014-12-24 19:07
:modified: 2014-12-24 19:07
:category: QEMU
:tags: qemu, virtualization, kvm
:author: wdv4758h
:summary: create image and install OS for QEMU

- `Wikipedia - QEMU <https://en.wikibooks.org/wiki/QEMU>`_
- `Arch Wiki - QEMU <https://wiki.archlinux.org/index.php/QEMU>`_

Install QEMU
========================================

.. code-block:: sh

    pacman -S qemu  # Arch Linux

::

    Name                New Version  Net Change  Download Size

    extra/bluez-libs    5.26-1       0.28 MiB         0.06 MiB
    extra/celt0.5.1     0.5.1.3-3    0.16 MiB         0.04 MiB
    extra/libcacard     2.1.2-1      0.09 MiB         0.03 MiB
    extra/libiscsi      1.12.0-1     0.44 MiB         0.10 MiB
    extra/seabios       1.7.5-2      1.69 MiB         0.12 MiB
    extra/spice         0.12.5-1     2.41 MiB         0.56 MiB
    community/usbredir  0.6-4        0.15 MiB         0.03 MiB
    extra/vde2          2.3.2-6      0.78 MiB         0.19 MiB
    extra/qemu          2.1.2-1      178.21 MiB      19.38 MiB

    Total Download Size:    20.53 MiB
    Total Installed Size:   184.21 MiB

Create Image
========================================

.. code-block:: sh

    qemu-img create -f qcow2 test.qcow2 100G

output :

::

    Formatting 'test.qcow2', fmt=qcow2 size=107374182400 encryption=off cluster_size=65536 lazy_refcounts=off

Install OS from bootable ISO
========================================

* ``-m`` to assign memory size
* ``-cdrom`` to assign bootable ISO
* ``-boot order=d`` to change the booting priority for cdrom

.. code-block:: sh

    qemu-system-x86_64 -m 2G -cdrom ArchLinux.iso -boot order=d test.qcow2

QEMU with KVM
========================================

check your kernel has KVM support :

.. code-block:: sh

    lsmod | grep kvm

output :

::

    kvm_intel             143245  0
    kvm                   421519  1 kvm_intel

start QEMU in KVM mode (add ``--enable-kvm``)

.. code-block:: sh

    qemu-system-x86_64 --enable-kvm test.qcow2

with previous booting optinos :

.. code-block:: sh

    qemu-system-x86_64 --enable-kvm -m 2G -cdrom ArchLinux.iso -boot order=d test.qcow2
