========================================
vDSO
========================================


.. contents:: 目錄


介紹
========================================

vDSO 的全名是 Virtual Dynamically Shared Object，
是 Linux 把特定 kernel sapce 內的函式放給 user space 程式使用的機制，
藉此可以省去一些 system call 以及所帶來的 context switch，
其開發是要提供先前 vsyscall 的功能，
同時避免 vsyscall 所碰到的一些問題。

也就是說 vDSO 是一塊動態分配地 user space 記憶體空間（vsyscall 是靜態的），
user space 程式在使用到 vDSO 含有的 kernel space 功能時，
可以直接在 user space 的記憶體內找到，
不需要再呼叫 system call 造成效能損失。



參考
========================================

* `Wikipedia - vDSO <https://en.wikipedia.org/wiki/VDSO>`_
* `System calls in the Linux kernel. Part 3 - vsyscalls and vDSO <https://0xax.gitbooks.io/linux-insides/content/SysCall/syscall-3.html>`_
* `[TWLKH主題] vDSO Implementation in Linux - (Viller Hsiao) <https://www.youtube.com/watch?v=LVMjpCVUEAM>`_
* `vDSO and vsyscall <https://docs.google.com/document/d/1Yg3L_StCQxPLJf3gDWJ9UQqIeCYgjqbThLSkQImP-JA/edit>`_
* `Taiwain Linux Kernel Hackers about Linux vDSO internals <https://www.slideshare.net/vh21/twlkhlinuxvsyscallandvdso>`_
* [GitHub] `Linux - arch/x86/include/asm/vdso.h <https://github.com/torvalds/linux/blob/master/arch/x86/include/asm/vdso.h>`_
* [GitHub] `FreeBSD - sys/sys/vdso.h <https://github.com/freebsd/freebsd/blob/master/sys/sys/vdso.h>`_
