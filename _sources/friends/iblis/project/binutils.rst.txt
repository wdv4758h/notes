binutils
===============================================================================

``objdump``
----------------------------------------------------------------------

``hello.c``

.. code-block:: c

    int main()
    {
        return 0;
    }


::

    $ objdump -DxS hello.o
    hello.o:     file format elf64-x86-64-freebsd
    hello.o
    architecture: i386:x86-64, flags 0x00000011:
    HAS_RELOC, HAS_SYMS
    start address 0x0000000000000000

    Sections:
    Idx Name          Size      VMA               LMA               File off  Algn
    0 .text         00000008  0000000000000000  0000000000000000  00000040  2**4
    CONTENTS, ALLOC, LOAD, READONLY, CODE
    1 .comment      00000053  0000000000000000  0000000000000000  00000048  2**0
    CONTENTS, READONLY
    2 .note.GNU-stack 00000000  0000000000000000  0000000000000000  0000009b  2**0
    CONTENTS, READONLY
    3 .eh_frame     00000038  0000000000000000  0000000000000000  000000a0  2**3
    CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
    SYMBOL TABLE:
    0000000000000000 l    df *ABS*  0000000000000000 hello.c
    0000000000000000 l    d  .text  0000000000000000 .text
    0000000000000000 g     F .text  0000000000000008 main


    Disassembly of section .text:

    0000000000000000 <main>:
    0:   55                      push   %rbp
    1:   48 89 e5                mov    %rsp,%rbp
    4:   31 c0                   xor    %eax,%eax
    6:   5d                      pop    %rbp
    7:   c3                      retq
