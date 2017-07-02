========================================
Embedded Resource
========================================


.. contents:: 目錄


Talks
========================================

Embedded Linux Size Reduction Techniques
----------------------------------------

:講者: Michael Opdenacker
:Conf: Embedded Linux Conference 2017
:Slides: http://events.linuxfoundation.org/sites/events/files/slides/opdenacker-embedded-linux-size-reduction-techniques_0.pdf
:Video: https://www.youtube.com/watch?v=ynNLlzOElOU

* 編譯器優化
    - Clang & GCC： ``-Os``
    - Clang： ``-Oz`` ，比 ``-Os`` 更進一步
* Linker
    - Clang & GCC： ``-flto``
* ARM 平台（ARM mode vs Thumb mode）
    - ``-marm``
    - ``-mthumb``
* Linux kernel
    - ``make tinyconfig``
* BusyBox vs Toybox
    - 相較之下 Toybox 在大小上比較有優勢，而且可以有極小的 rootfs
    - 相較之下 BusyBox 在彈性上比較有優勢，而功能也比較多
* glibc vs uclibc vs musl
* super strip (sstrip)
    - https://github.com/BR903/ELFkickers
    - removes the contents at the end of an ELF file that are not part of the program's memory image


實測：

.. code-block:: sh

    $ cat hello.c
    #include <stdio.h>

    int main() {
        printf("Hello World\n");
    }
    $ clang hello.c -o hello

    $ ll hello
    -rwxr-xr-x 1 user user 8312 Mar  3 14:58 hello

    $ strip hello
    $ ll hello
    -rwxr-xr-x 1 user user 6184 Mar  3 14:58 hello

    $ sstrip hello
    $ ll hello
    -rwxr-xr-x 1 user user 4144 Mar  3 14:58 hello
