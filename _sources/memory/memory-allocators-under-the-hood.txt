========================================
Memory Allocator - Under The Hood
========================================


.. contents:: Table of Contents


Memory Allocator in Different OS
========================================

+---------+-----------+
| Linux   | ptmalloc2 |
+---------+-----------+
| FreeBSD | jemalloc  |
+---------+-----------+



System Call for Malloc
========================================

Testing
------------------------------

testing program :

.. code-block:: c

    // test_malloc.c

    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        puts("===========");
        free(malloc(sizeof(int)));
        puts("===========");
        return 0;
    }



Linux
++++++++++++++++++++

compile, execute, trace system call :

.. code-block:: sh

    $ gcc test_malloc.c -o test_malloc
    $ strace ./test_malloc  # Linux

在 trace system call 時，
這邊觀察到兩個 system call，
``brk(0)`` 和 ``brk(0x14e5000)`` (數值可能會不一樣)，
所以我們可以確定的是，
在 Linux 上目前去 call ``malloc`` 時，
會用到 ``brk`` 這個 system call



FreeBSD
++++++++++++++++++++

compile, execute, trace system call :

.. code-block:: sh

    $ clang test_malloc.c -o test_malloc
    $ truss ./test_malloc   # FreeBSD

在 trace system call 時，
這邊只觀察到一個 system call，
可以發現使用的 system call 是 ``madvise`` ，
和 Linux 上不同 (Linux 上是 ``brk``)。

``madvise(0x2c07000,0x1000,0x5,0xaaaaaaaaaaaaaaab,0x2c00048,0x24c4be0)`` ，
這是用於 ``free`` 的



Explain
------------------------------

所以到底這些 system call (``brk``, ``madvise``) 都做了些什麼勒？
為什麼 call 完後 heap 就會多出空間可以使用？

我們先來看看 Linux 上的 Memory 都放了些什麼東西 :

.. image:: images/memory-management/Linux-Address-Layout.png
    :alt: Linux Address Layout



sbrk
------------------------------

sbrk 是 glibc 的 brk wrapper

glibc
========================================

glibc/misc/sbrk.c :

.. code-block:: c

    /* Extend the process's data space by INCREMENT.
       If INCREMENT is negative, shrink data space by - INCREMENT.
       Return start of new space allocated, or -1 for errors.  */
    void *
    __sbrk (intptr_t increment)
    {
      void *oldbrk;

      /* If this is not part of the dynamic library or the library is used
         via dynamic loading in a statically linked program update
         __curbrk from the kernel's brk value.  That way two separate
         instances of __brk and __sbrk can share the heap, returning
         interleaved pieces of it.  */
      if (__curbrk == NULL || __libc_multiple_libcs)
        if (__brk (0) < 0)		/* Initialize the break.  */
          return (void *) -1;

      if (increment == 0)
        return __curbrk;

      oldbrk = __curbrk;
      if ((increment > 0
           ? ((uintptr_t) oldbrk + (uintptr_t) increment < (uintptr_t) oldbrk)
           : ((uintptr_t) oldbrk < (uintptr_t) -increment))
          || __brk (oldbrk + increment) < 0)
        return (void *) -1;

      return oldbrk;
    }


glibc/sysdeps/unix/sysv/linux/generic/brk.c

.. code-block:: c

    int
    __brk (void *addr)
    {
      INTERNAL_SYSCALL_DECL (err);

      __curbrk = (void *) INTERNAL_SYSCALL (brk, err, 1, addr);
      if (__curbrk < addr)
        {
          __set_errno (ENOMEM);
          return -1;
        }

      return 0;
    }


glibc/sysdeps/unix/sysv/linux/x86_64/sysdep.h

.. code-block:: c

    # define INTERNAL_SYSCALL_NCS(name, err, nr, args...) \
    ({									      \
      unsigned long int resultvar;					      \
      LOAD_ARGS_##nr (args)						      \
      LOAD_REGS_##nr							      \
      asm volatile (							      \
      "syscall\n\t"							      \
      : "=a" (resultvar)							      \
      : "0" (name) ASM_ARGS_##nr : "memory", "cc", "r11", "cx");		      \
      (long int) resultvar; })

    # define INTERNAL_SYSCALL(name, err, nr, args...) \
      INTERNAL_SYSCALL_NCS (__NR_##name, err, nr, ##args)

C - Inline Assembly
========================================

關鍵字 : ``asm``


.. code-block:: c

    asm("movl %ecx %eax");      /* moves the contents of ecx to eax */
    __asm__("movb %bh (%eax)"); /*moves the byte from bh to the memory pointed by eax */


``asm`` 和 ``__asm__`` 都可以用，當 ``asm`` 在程式中會 conflict 時就可以使用 ``__asm__`` ，
如果 assembly code 有很多行的話，每行結尾加上 "\n\t"，
如此一來在把 assembly code 字串丟給後面的 as (ex: GAS (GNU Assembler)) 處理時，
格式才會是正確的。


.. code-block:: c

    asm ("movl %eax, %ebx\n\t"
         "movl $56, %esi\n\t"
         "movl %ecx, $label(%edx,%ebx,$4)\n\t"
         "movb %ah, (%ebx)");


Extended Asm :

.. code-block:: c

    asm ( assembler template
       : output operands                  /* optional */
       : input operands                   /* optional */
       : list of clobbered registers      /* optional */
       );


----

asm volatile ("syscall\n\t" : "=a" (result) : "0" (SYS_BRK) : "memory", "cc", "r11", "cx");

----


GCC 用 AT&T/UNIX assembly syntax



Source-Destination Ordering

    "Op-code src dst"

Register Naming

    prefix by %, %eax

Immediate Operand

Operand Size

Memory Operands





+------------------------------+------------------------------------+
|       Intel Code             |      AT&T Code                     |
+------------------------------+------------------------------------+
| mov     eax,1                |  movl    $1,%eax                   |
| mov     ebx,0ffh             |  movl    $0xff,%ebx                |
| int     80h                  |  int     $0x80                     |
| mov     ebx, eax             |  movl    %eax, %ebx                |
| mov     eax,[ecx]            |  movl    (%ecx),%eax               |
| mov     eax,[ebx+3]          |  movl    3(%ebx),%eax              |
| mov     eax,[ebx+20h]        |  movl    0x20(%ebx),%eax           |
| add     eax,[ebx+ecx*2h]     |  addl    (%ebx,%ecx,0x2),%eax      |
| lea     eax,[ebx+ecx]        |  leal    (%ebx,%ecx),%eax          |
| sub     eax,[ebx+ecx*4h-20h] |  subl    -0x20(%ebx,%ecx,0x4),%eax |
+------------------------------+------------------------------------+

Misc
========================================

* brk 是什麼的縮寫？
* `Linux Syscall Table <https://filippo.io/linux-syscall-table/>`_

Reference
========================================

* `GCC-Inline-Assembly-HOWTO <https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html>`_
* `Whirlwind Tour of ARM Assembly <http://www.coranac.com/tonc/text/asm.htm>`_
