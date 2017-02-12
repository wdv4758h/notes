https://chakraos.org/wiki/index.php?title=Kernel_modules

::

    lsmod
    modinfo <module_name>
    systool -v -m <module_name>
    modprobe -c | grep <module_name>
    modprobe --show-depends <module_name>
