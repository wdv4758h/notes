LXC 1.1 support checkpoint restore by CRIU(checkpoint-restore in userspace)

- https://linuxcontainers.org/lxc/news/#lxc-110-release-announcement-30th-of-january-2015
- https://lists.linuxcontainers.org/pipermail/lxc-devel/2014-August/010081.html
- https://lists.linuxcontainers.org/pipermail/lxc-devel/2014-August/010163.html
- ``lxc-checkconfig`` will check kernel config of CR.
- ``lxc-checkpoint [-r|--restore]``

Kernel config of CR?
~~~~~~~~~~~~~~~~~~~~
1. CRIU wiki: installation - configuring kernel: https://criu.org/Installation#Configuring_the_kernel

  - ``CONFIG_CHECKPOINT_RESTORE=y``

2. archlinux aur linux-criu: https://aur.archlinux.org/packages/linux-criu/

CONFIG_CHECKPOINT_RESTORE?
~~~~~~~~~~~~~~~~~~~~~~~~~~
1. CRIU wiki: upstream kernel commit: https://criu.org/Upstream_kernel_commits

  - c/r: introduce CHECKPOINT_RESTORE symbol: https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=067bce1a06
  - kcmp: make it depend on CHECKPOINT_RESTORE: https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=1e142b29e2

2. CRIU and DMTCP: https://lwn.net/Articles/478111/

  - CRIU kernel patch: prctl() syscall options and kcmp() syscall.
  - DMTCP: LD_PRELOAD libc: wrapper of many libc/syscall.

3. wikipedia of CRIU history 

  - https://www.wikiwand.com/en/CRIU#/History
  - http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=099469502f62fbe0d7e4f0b83a2f22538367f734
