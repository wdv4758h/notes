========================================
Kernel Module
========================================

.. code-block:: sh

    $ lsmod | grep psmouse
    psmouse               118784  0
    libps2                 16384  2 atkbd,psmouse
    serio                  20480  6 serio_raw,atkbd,i8042,psmouse

    # load module
    $ sudo insmod hello.ko

    # remove module
    $ sudo rmmod psmouse

    $ modinfo psmouse
    filename:       /lib/modules/4.4.5-1-ARCH/kernel/drivers/input/mouse/psmouse.ko.gz
    license:        GPL
    description:    PS/2 mouse driver
    author:         Vojtech Pavlik <vojtech@suse.cz>
    alias:          serio:ty05pr*id*ex*
    alias:          serio:ty01pr*id*ex*
    depends:        serio,libps2
    intree:         Y
    vermagic:       4.4.5-1-ARCH SMP preempt mod_unload modversions
    parm:           proto:Highest protocol extension to probe (bare, imps, exps, any). Useful for KVM switches. (proto_abbrev)
    parm:           resolution:Resolution, in dpi. (uint)
    parm:           rate:Report rate, in reports per second. (uint)
    parm:           smartscroll:Logitech Smartscroll autorepeat, 1 = enabled (default), 0 = disabled. (bool)
    parm:           resetafter:Reset device after so many bad packets (0 = never). (uint)
    parm:           resync_time:How long can mouse stay idle before forcing resync (in seconds, 0 = never). (uint)

    $ modinfo i915 | grep psr
    parm:           enable_psr:Enable PSR (default: false) (int)

    # load module (find it from /lib/modules/$(uname -r)/modules.dep)
    $ sudo modprobe psmouse

    # remove module
    $ sudo modprobe -r psmouse

    $ cat /lib/modules/$(uname -r)/modules.dep
    $ depmod --dry-run
    # analysis current kernel module and write to modules.dep
    $ sudo depmod


* `Arch Wiki - Kernel parameters <https://wiki.archlinux.org/index.php/Kernel_parameters>`_
