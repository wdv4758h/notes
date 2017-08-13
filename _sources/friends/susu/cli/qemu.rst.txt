- installation example

.. code:: sh 

    qemu-system-x86_64 -enable-kvm -m 2G -cdrom ArchLinux.iso -boot order=d test.qcow2

- usage example

.. code:: sh 

    qemu -enable-kvm -cpu host -smp 2 -m 512MB \
    -hda <image> \
    -net nic,vlan=0 \
    -net user,hostfwd=tcp:127.0.0.1:50022-:22 \
    -vga std \
    -monitor telnet:0.0.0.0:60023,server,nowait 

- parameters

  - ``-kernel <KERNEL_IMAGE>``
  - ``-append "<KERNEL_PARAMETERS>"``
  
network
-------
- http://wiki.qemu.org/Documentation/Networking

There are 2 parts to networking in QEMU

- virtual network device: ``-device <device>,netdev=<id>``
- network backend: ``-netdev <backend>,id=<id>``

network backend
~~~~~~~~~~~~~~~

- usermode: ``<backend>=user``
- TAP networking: ``<backend>=tap``
- VDE networking:
- socket networking: ``<backend>=socket``

redirection in user backend::

    -netdev user,id=net0,hostfwd=tcp:127.0.0.1:2522-:22
    # host(127.0.0.1):2522 -> guest:22
    # hostfwd=[<host_ip>]:<host_port>-[<guest_ip>]:<guest_port>

virtual network device
~~~~~~~~~~~~~~~~~~~~~~

- device type::

    bash> qemu-system-x86_64 -device help |& less
    # search 'Network'
    name "e1000", bus PCI, alias "e1000-82540em", desc "Intel Gigabit Ethernet"
    name "e1000-82544gc", bus PCI, desc "Intel Gigabit Ethernet"
    name "e1000-82545em", bus PCI, desc "Intel Gigabit Ethernet"
    name "e1000e", bus PCI, desc "Intel 82574L GbE Controller"
    name "i82550", bus PCI, desc "Intel i82550 Ethernet"
    name "rtl8139", bus PCI
    name "virtio-net-device", bus virtio-bus
    name "virtio-net-pci", bus PCI, alias "virtio-net"  
    ...

example
~~~~~~~

::

    # virtio net
    -netdev user,id=net0 \
    -device virtio-net,netdev=net0

    # trap-and-emulate, e1000 
    -netdev user,id=net0 \
    -device e1000,netdev=net0

    # hostfwd
    -netdev user,id=<id>,hostfwd=tcp:127.0.0.1:2522-:22

not reading

- https://people.gnome.org/~markmc/qemu-networking.html

block device
------------
- ``-drive``, ``-hda``, ``-cdrom``

   .. code:: sh

       # Instead of -cdrom <file> you can use:
       qemu-system-i386 -drive file=<file>,index=2,media=cdrom

       # Instead of -hda, -hdb, -hdc, -hdd <file>, you can use:
       qemu-system-i386 -drive file=<file>,index=0,media=disk
       qemu-system-i386 -drive file=<file>,index=1,media=disk
       qemu-system-i386 -drive file=<file>,index=2,media=disk
       qemu-system-i386 -drive file=<file>,index=3,media=disk


remote control
--------------

qemu VM using spice

- qemu VM (server)

  - examples

    - ``qemu-system-x86_64 -enable-kvm -hda ubuntu_14_04_3.qcow2 -vga qxl -spice port=45900,disable-ticketing``
    - ``qemu-system-x86_64 -enable-kvm -hda ubuntu_14_04_3.qcow2 -vga qxl -spice port=45900,addr=127.0.0.1,disable-ticketing``
    - ``qemu-system-x86_64 -enable-kvm -hda ubuntu_14_04_3.qcow2 -vga qxl -spice port=45900,password=<secret>``

  ::

      -vga qxl -spice port=45900,[addr=127.0.0.1],[password=<secret>|disable-ticketing]

- client (gtk-based)

  - ``spicy -h <host> -p <port>``


monitor mode
------------
control the running VM.

- How to use qemu monitor mode

  1. switch between VM screen and qemu monitor mode

     ``alt-1`` to VM screen and ``alt-2`` to qemu monitor mode

  2. redirect monitor to host OS tcp socket::

     -monitor telnet:0.0.0.0:60023,server,nowait # qemu command line option
 
http://wiki.qemu.org/download/qemu-doc.html#pcsys_005fmonitor
http://en.wikibooks.org/wiki/QEMU/Monitor#Devices

examples::

    info network
    help hostfwd_add
    hostfwd_add tcp:127.0.0.1:8000-:8000
    quit # VM 結束

monitor mode 下的 ``hostfwd_add tcp:127.0.0.1:8000-:8000`` command 似乎無效, 待尋找原因.


Qemu hot snapshot
~~~~~~~~~~~~~~~~~

use qemu monitor commands

- savevm
- info snapshots
- loadvm [tag|id]


related tool
------------

qemu-img
~~~~~~~~
qemu-img [command] [options]

- ``-f [format] # raw | qcow2 ... etc``

examples:

::

    qemu-img create -f raw xxx.img 1G
    qemu-img convert -f raw -O qcow2 xxx.img xxx.qcow2

- ``qemu-img resize`` 可用於增大不足的 image 空間 (e.g. ubuntu official 的 cloud image 大小只有 5G)

  - https://gist.github.com/larsks/3933980: qemu-img resize 增大 image + fdisk 重切 MBR + resizefs 增大 ext4.


qemu-nbd
~~~~~~~~
http://newtoypia.blogspot.tw/2015/03/qcow2.html

::

    # load host kernel module
    lsmod | grep nbd
    modprobe nbd max_part=16

    # attach qemu block device
    qemu-nbd -c /dev/nbd0 test.qcow2
    # detach qemu block device
    qemu-nbd -d /dev/nbd0

    # general block device
    lsblk
    fdisk -l /dev/nbd0
    fdisk /dev/nbd0
    mkfs.ext4 /dev/nbd0p1
    mount /dev/nbd0p1 mnt/

Misc
----
- QEMU + GDB debug linux 0.11: https://wwssllabcd.github.io/blog/2012/08/03/compile-linux011/
- ``-vga virtio -display gtk,gl=on``

