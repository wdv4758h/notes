===========================================================
seccomp -  operate on Secure Computing state of the process
===========================================================


.. contents:: 目錄


介紹
========================================

* Linux kernel's feature since version 2.6.12
* 限定特定 process 只能呼叫特定的 system call。



參考
========================================

* `Wikipedia - seccomp <http://en.wikipedia.org/wiki/Seccomp>`_
* `seccomp 學習筆記 <https://szlin.me/2017/08/23/kernel_seccomp/>`_

* seccomp-bpf: system call filter
* used by
    - OpenSSH
    - vsftpd
    - Chrome/Chromium
    - LXD
    - Firefox
    - Firefox OS
