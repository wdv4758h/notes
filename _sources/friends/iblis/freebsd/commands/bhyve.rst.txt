bhyve
===============================================================================

Network
----------------------------------------------------------------------

Ref: https://www.freebsd.org/doc/handbook/virtualization-host-bhyve.html

::

    # ifconfig tap0 create
    # sysctl net.link.tap.up_on_open=1
    net.link.tap.up_on_open: 0 -> 1
    # ifconfig bridge0 create
    # ifconfig bridge0 addm re0 addm tap0
    # ifconfig bridge0 up

::

    # ifconfig re0 alias 192.168.1.1

* configure ``isc-dhcpd`` to listenon ``192.168.1.0/24```

``pf.conf`` ::

    ex_if='re0'
    ex_ip='...'

    bhyve_net='192.168.1.0/24'
    nat on $ex_if proto { tcp, udp, icmp } from { $bhyve_net } to any -> $ex_ip


NetBSD
----------------------------------------------------------------------

* install *sysutils/grub2-bhyve*

* create disk image::

    $ truncate -s 3g netbsd.img

* create installation map file::

    $ cat install.map
    (cd0) ./netbsd.iso
    (hd1) ./netbsd.img

* setup grub::

    $ grub-bhyve -r cd0 -M 1G -m instdev.map netbsd

* under the grub interface::

    knetbsd -h -r cd0a (cd0)/netbsd
    boot

* and boot the installer from ISO::

    bhyve -A -H -P -s 0:0,hostbridge -s 1:0,lpc \
        -s 2:0,virtio-net,tap0 \
        -s 3:0,virtio-blk,./netbsd.img \
        -s 4:0,ahci-cd,./netbsd.iso \
        -l com1,stdio -c 2 -m 1G netbsd

* stop vm::

    bhyvectl --destroy --vm=netbsd

* create ``dev.map``::

    $ cat dev.map
    (hd1) netbsd.img

* setup grub::

    grub-bhyve -r cd0 -M 1G -m dev.map netbsd

* under grub interface::

    knetbsd -h -r ld0a (hd1,msdos1)/netbsd
    boot

* start bhyve::

    bhyve -A -H -P -s 0:0,hostbridge \
        -s 1:0,lpc \
        -s 2:0,virtio-net,tap0 \
        -s 3:0,virtio-blk,./netbsd.img \
        -l com1,stdio -c 2 -m 1G netbsd


OpenBSD
----------------------------------------------------------------------

grub install::

    kopenbsd -h com0 (cd0)/5.7/amd64/bsd.rd
    boot

grub::

    kopenbsd -h com0 -r sd0a (hd1,openbsd1)/bsd
    boot
