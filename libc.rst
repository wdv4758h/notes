========================================
那些 libc 們
========================================

一些 libc 實作
========================================

* BSD libc, implementations distributed under BSD operating systems.
* GNU C Library (glibc), used in Linux, GNU Hurd and GNU/kFreeBSD.
* Microsoft C Run-time Library, part of Microsoft Visual C++
* dietlibc, an alternative small implementation of the C standard library (MMU-less)
* μClibc, a C standard library for embedded μClinux systems (MMU-less)
* Newlib, a C standard library for embedded systems (MMU-less)
* klibc, primarily for booting Linux systems.
* musl, another lightweight C standard library implementation for Linux systems
* Bionic, originally developed by Google for the Android embedded system operating system, derived from BSD libc.

musl
========================================

musl 的目標就要寫出乾淨、有效率、符合標準的 libc 實作，
對於 static linking 也比較有效率，
目前有部份 Linux distrubutions 把 musl 當作預設的 libc (而不是 glibc)，
例如 OpenWRT、Alpine Linux、Void (Linux) 等等。

在 ArchLinux 上可以直接用 pacman 安裝，
或是從 `AUR <https://aur.archlinux.org/packages/musl-git>`_ 抓下來自己 build

.. code-block:: sh

    $ sudo pacman -S musl
    $ cat /usr/bin/musl-gcc
    #!/bin/sh
    exec "${REALGCC:-gcc}" "$@" -specs "/usr/lib/musl/lib/musl-gcc.specs"
    $ musl-gcc -static hello.c -o hello; strip hello; ls -l hello


Static Linked Binary's Size Comparision
========================================

C Code :

.. code-block:: c

    #include <stdio.h>

    int main () {
        printf("Hello World!\n");
    }

Result :

.. code-block:: sh

    # glibc

    $ gcc -static hello.c -o hello; strip hello; ls -l hello
    -rwxr-xr-x 1 dv users 738808 Jul 22 19:29 hello
    $ clang -static hello.c -o hello ; strip hello ; ls -l hello
    -rwxr-xr-x 1 dv users 734776 Jul 22 19:32 hello

    # BSD libc

    $ gcc -static hello.c -o hello; strip hello; ls -l hello
    -rwxrwxr-x  1 wdv4758h  wheel  427408 Jul 22 19:31 hello*
    $ clang -static hello.c -o hello ; strip hello ; ls -l hello
    -rwxrwxr-x  1 wdv4758h  wheel  427264 Jul 22 19:31 hello*

    # musl

    $ musl-gcc -static hello.c -o hello; strip hello; ls -l hello
    -rwxr-xr-x 1 dv dv 5376 Jul 22 22:05 hello
    $ musl-clang -static hello.c -o hello; strip hello; ls -l hello
    -rwxr-xr-x 1 dv dv 14632 Jul 22 22:06 hello



Reference
========================================

* `Wikipedia - C standard library <https://en.wikipedia.org/wiki/C_standard_library>`_
* `Wikipedia - musl <https://en.wikipedia.org/wiki/Musl>`_
* `Comparison of C/POSIX standard library implementations for Linux <http://www.etalabs.net/compare_libcs.html>`_
* `[2013] a libc qsort() shootout of sorts <http://calmerthanyouare.org/2013/05/31/qsort-shootout.html>`_
* `[2014] algorithmic complexity attacks and libc qsort() <http://calmerthanyouare.org/2014/06/11/algorithmic-complexity-attacks-and-libc-qsort.html>`_
* `GLIBC SUCKS <http://galexander.org/glibc.html>`_
