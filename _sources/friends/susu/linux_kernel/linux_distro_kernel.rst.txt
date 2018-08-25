- ubuntu kernel

  - https://wiki.ubuntu.com/Kernel
  - distro and kernel version: https://wiki.ubuntu.com/Kernel/FAQ#Kernel.2BAC8-Support.Ubuntu_Kernel_Support
  - get distro kernel: https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel

    - ``apt-get source`` or ``git clone git://kernel.ubuntu.com/...``

build kernel
------------
1. add patch, modify kernel extra version
   
   - vim Makefile

2. kernel config

   - make menuconfig
   - save, exit

3. build kernel

   - all: bzImage + vmlinux + module

4. install kernel

   - make module_install & install (move bzImage, initramfs)

     - target: ``/boot/``
     - [if manual] mkinit* for initramfs

5. bootloader configuration

   - modify(update) grub

     - No Grub Menu Issue: http://askubuntu.com/a/101693
     - update grub
     - grub-customizer: https://launchpad.net/~danielrichter2007/+archive/ubuntu/grub-customizer


- reference

  - http://kernelnewbies.org/KernelBuild
  - ``Linux Kernel Doc - README``: http://lxr.free-electrons.com/source/README#L124
  - ``Linux Kernel Doc - kbuild/makefiles.txt``: http://lxr.free-electrons.com/source/Documentation/kbuild/makefiles.txt
    
    - ch1, 2, 6

  - archwiki - kernel compilation: https://wiki.archlinux.org/index.php/Kernels/Compilation/Traditional
