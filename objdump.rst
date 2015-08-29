========================================
Objdump
========================================

Get ARM Instruction By Objdump On x86
========================================

target :

* 0xDEFF 0xF8DF
* 0xDEFF 0xF107
* 0xDEFF 0x461F
* 0xDEFF 0x4607

.. code-block:: sh

    $ pacman -S arm-none-eabi-gcc       # for arm-none-eabi-gcc
    $ pacman -S arm-none-eabi-binutils  # for arm-none-eabi-objdump

.. code-block:: asm

    .thumb
    .globl _start
    _start:
    reset:
    _instruction1: .word 0xDEFFF8DF     # ARM 的 .word 可以塞各種東西
    _instruction2: .word 0xDEFFF107
    _instruction3: .word 0xDEFF461F
    _instruction4: .word 0xDEFF4607

.. code-block:: sh

    $ arm-none-eabi-gcc -c tmp.S
    $ arm-none-eabi-gcc -nostdlib tmp.o -o tmp
    $ arm-none-eabi-objdump -d tmp.o

    tmp.o:     file format elf32-littlearm


    Disassembly of section .text:

    00000000 <_start>:
       0:   defff8df        mrcle   8, 7, APSR_nzcv, cr15, cr15, {6}

    00000004 <_instruction2>:
       4:   defff107        nrmlee  f7, f7

    00000008 <_instruction3>:
       8:   deff461f        mrcle   6, 7, r4, cr15, cr15, {0}

    0000000c <_instruction4>:
       c:   deff4607        cdple   6, 15, cr4, cr15, cr7, {0}
