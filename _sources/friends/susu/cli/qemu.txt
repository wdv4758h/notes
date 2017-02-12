- installation example

.. code:: sh 

    qemu-system-x86_64 -enable-kvm -m 2G -cdrom ArchLinux.iso -boot order=d test.qcow2

- usage example

.. code:: sh 

    qemu -enable-kvm -hda <image> -vga std -cpu host -smp 2 -m 512MB \
    -net nic,vlan=0 \
    -net user,hostfwd=tcp:127.0.0.1:50022-:22 \
    -monitor telnet:0.0.0.0:60023,server,nowait 

- parameters

  - ``-kernel <KERNEL_IMAGE>``
  - ``-append "<KERNEL_PARAMETERS>"``
  
network
-------
http://en.wikibooks.org/wiki/QEMU/Networking
http://wiki.qemu.org/Documentation/Networking

- usermode (default)

  - redirection

- TAP networking
- VDE networking

redirection example::

    -net user,hostfwd=tcp:127.0.0.1:2522-:22
    # host(127.0.0.1):2522 -> guest:22
    # hostfwd=[<host_ip>]:<host_port>-[<guest_ip>]:<guest_port>

[not reading] https://people.gnome.org/~markmc/qemu-networking.html

mechanism
~~~~~~~~~
- usermode

  1. emulated NIC provided to guest
  2. network backend in host (put guest packets onto host's network)

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

  - ``qemu-system-x86_64 -enable-kvm -hda ubuntu_14_04_3.qcow2 -vga qxl -spice port=45900,disable-ticketing``
  - ``qemu-system-x86_64 -enable-kvm -hda ubuntu_14_04_3.qcow2 -vga qxl -spice port=45900,addr=127.0.0.1,disable-ticketing``
  - ``qemu-system-x86_64 -enable-kvm -hda ubuntu_14_04_3.qcow2 -vga qxl -spice port=45900,password=<secret>``

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

related tool
------------
qemu-img
++++++++
qemu-img [command] [options]

- ``-f [format] # raw | qcow2 ... etc``

examples:

::

    qemu-img create -f raw xxx.img 1G
    qemu-img convert -f raw -O qcow2 xxx.img xxx.qcow2

Misc
----
QEMU + GDB debug linux 0.11: https://wwssllabcd.github.io/blog/2012/08/03/compile-linux011/

