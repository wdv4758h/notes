- demsg: kernel message, print and control kernel ring buffer

  - -H: human readable format
    
    - -d: show delta timestamp
    - -e: human readable timestamp
    - -P, --no-pager: built-in pager

lsmod: show all kernel module
modinfo: show info of one kernel module
insmod/rmmod: add/remove kernel module
modprobe: add/remove kernel module (dependency)

- kernel: /boot/vmlinuz-...
- kernel module: /lib/modules/$(uname -r)/kernel/
- kernel source(if have): /usr/src/kernel/

build linux kernel
------------------
- make help
  
  - clean

    - distclean
    - mrproper
    - clean

  - config
  - Other generic targets: all/vmlinux/modules/modules_install ...
  - Architecture specific targets(x86): bzImage/install/isoimage/i386_defconfig/x86_64_defconfig
  - Static analysers
  - Kernel selftest
  - Kernel packaging
  - Documentation targets

- kernel configuration example

  - general setup

    - Support for paging of anonymous memory, Memory placement aware NUMA scheduler
    - Choose SLAB allocator
    - System V IPC, POSIX Message Queues
    - cgroup, namespace support
    - oprofile, kprobes, GCOV-based kernel profiling
    - system-call auditing support    

    - Initial RAM filesystem and RAM disk (initramfs/initrd) support
    - RCU subsystem
    - Disable heap randomization

Misc
----

- linux kernel source::
  
  - arch/
  - mm/
  - driver/
  - block/
  - sound/
  - fs/
  - net/
  - ipc/
  - security/

  - kernel/
  - lib/
  - init/
  - firmware/

  - crypto/
  - virt/

  - include/
  - Documentation/
