========================================
FreeBSD Kernel Module
========================================

.. code-block:: sh

    $ make
    @ -> /usr/src/sys
    machine -> /usr/src/sys/amd64/include
    x86 -> /usr/src/sys/x86/include
    cc -O2 -pipe  -fno-strict-aliasing -D_KERNEL -DKLD_MODULE -nostdinc   -I. -I@ -I@/contrib/altq -fno-common  -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer  -mno-aes -mno-avx -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -msoft-float  -fno-asynchronous-unwind-tables -ffreestanding -fstack-protector -std=iso9899:1999 -Qunused-arguments  -fstack-protector -Wall -Wredundant-decls -Wnested-externs -Wstrict-prototypes  -Wmissing-prototypes -Wpointer-arith -Winline -Wcast-qual  -Wundef -Wno-pointer-sign -fformat-extensions  -Wmissing-include-dirs -fdiagnostics-show-option  -Wno-error-tautological-compare -Wno-error-empty-body  -Wno-error-parentheses-equality -Wno-error-unused-function   -c hello_fsm.c
    ld  -d -warn-common -r -d -o hello_fsm.ko hello_fsm.o
    :> export_syms
    awk -f /sys/conf/kmod_syms.awk hello_fsm.ko  export_syms | xargs -J% objcopy % hello_fsm.ko
    objcopy --strip-debug hello_fsm.ko
    $ sudo make load
    /sbin/kldload -v /tmp/module/hello_fsm.ko
    simple module: Hello
    Loaded /tmp/module/hello_fsm.ko, id=33
    $ sudo make unload
    /sbin/kldunload -v hello_fsm.ko
    Unloading hello_fsm.ko, id=33
    simple module: Goodbye
