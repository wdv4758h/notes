Introduction
------------
Kbuild is makefile-based build system.

Kbuild rules are at scripts/Makefile.* (makefile rules)

Documentation
-------------
- Documentation/kbuild/

  - Linux kernel makefiles: makefiles.txt
  - Kconfig language: kconfig-language.txt
  - Build external kernel modules: modules.txt

Kbuild
------

- implicit rules: from .c, .S
- obj-y
- obj-m
- <module>-y
- obj-<config>

- directory

  - obj-y, obj-m: 使用 directory 是等效果的, 但 obj-n 有差, 所以用 obj-<CONFIG> 仍然是有用的.

- flags

  - ccflags-y, asflags-y and ldflags-y
  - subdir-ccflags-y, subdir-asflags-y
  - CFLAGS_$@, AFLAGS_$@

details
~~~~~~~

- obj-y = <files>

  - 把 object code link 到 vmlinux
  - obj-y = foo.o
  - LD foo.o => built-in.o

- obj-m = <files>
    
  - 把 object code 單檔成為 kernel module
  - obj-y = foom.o
  - foom.o => foom.ko

- <module>-y = <files>

  - 把 object code linke 成 module.o
  - testfs-y = foo1.o foo2.o
  - LD foo1.o foo2.o => testfs.o

- 多檔案 kernel module?

  - obj-m + <module>-y

- config built-in or kernel module by config file

  - obj-<CONFIG_TESTFS>
  - obj-y for built-in, obj-m for kernel module, obj-n for no build

Kconfig
-------

- define linux kernel configuation options (tree structure)
- type: bool/tristate. tristate is for y/m/n option.
- Menu attribute

  - type, input prompt, default value
  - dependency, reverse dependency, visible(limit menu display): ``depend on``, ``select``, ``visible``
  - numeric range, help text, misc option

- Example

  - ``arch/x86/kvm/Kconfig`` v.s. ``arch/arm64/kvm/Kconfig``
  
    - source ``virt/kvm/Kconfig``, ``drivers/vhost/Kconfig``
