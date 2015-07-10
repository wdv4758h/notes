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
``madvise(0x2c07000,0x1000,0x5,0xaaaaaaaaaaaaaaab,0x2c00048,0x24c4be0)`` ，
可以發現使用的 system call 是 ``madvise`` ，
和 Linux 上不同 (Linux 上是 ``brk``)。



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


Misc
========================================

* brk 是什麼的縮寫？
