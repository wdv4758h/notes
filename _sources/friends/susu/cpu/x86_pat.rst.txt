x86 PAT and MTRR
================

- memory types & cache control.
- x86 use MTRR(Memory Type and Range Registers) and PAT(Page Attribute Table) to control memory type.

x86 cpu spec
------------

x86 memory types: UC, WC, WT, WB

  .. image:: img/x86_mem_type.png

cache control registers and bits

  - MTRR register
  - PAT
    
    - PAT, PCD, PWT bit in page table entry
    - IA32_PAT MSR

  - others

    - G bit in page table entry
    - CR0's CD, NW bit
    - CR3's PCD, PWT bit
    - CR4's PGE bit

  .. image:: img/x86_cache_control_regs_bits.png

example of memory type setting
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

setting memory types by PAT and MTRR.

  .. image:: img/set_mem_type.png

Linux support
-------------

Linux Kernel Memory API and Memory types

- ``ioremap()``
- ``set_memory_*()``
- pci sysfs resource and pci proc
- ``/dev/mem`` ``mmap()/read()/write()``

table::
    
    -------------------------------------------------------------------
    API                    |    RAM   |  ACPI,...  |  Reserved/Holes  |
    -----------------------|----------|------------|------------------|
    ioremap                |    --    |    UC      |       UC         |
    ioremap_cache          |    --    |    WB      |       WB         |
    ioremap_nocache        |    --    |    UC      |       UC         |
    ioremap_wc             |    --    |    --      |       WC         |
    set_memory_uc          |    UC    |    --      |       --         |
     set_memory_wb         |          |            |                  |
    set_memory_wc          |    WC    |    --      |       --         |
     set_memory_wb         |          |            |                  |
                           |          |            |                  |
    pci sysfs resource     |    --    |    --      |       UC         |
    pci sysfs resource_wc  |    --    |    --      |       WC         |
     is IORESOURCE_PREFETCH|          |            |                  |
    pci proc               |    --    |    --      |       UC         |
     !PCIIOC_WRITE_COMBINE |          |            |                  |
    pci proc               |    --    |    --      |       WC         |
     PCIIOC_WRITE_COMBINE  |          |            |                  |
                           |          |            |                  |
    /dev/mem               |    --    |    UC      |       UC         |
     read-write            |          |            |                  |
    /dev/mem               |    --    |    UC      |       UC         |
     mmap SYNC flag        |          |            |                  |
    /dev/mem               |    --    |  WB/WC/UC  |    WB/WC/UC      |
     mmap !SYNC flag       |          |(from exist-|  (from exist-    |
     and                   |          |  ing alias)|    ing alias)    |
     any alias to this area|          |            |                  |
    /dev/mem               |    --    |    WB      |       WB         |
     mmap !SYNC flag       |          |            |                  |
     no alias to this area |          |            |                  |
     and                   |          |            |                  |
     MTRR says WB          |          |            |                  |
    /dev/mem               |    --    |    --      |    UC_MINUS      |
     mmap !SYNC flag       |          |            |                  |
     no alias to this area |          |            |                  |
     and                   |          |            |                  |
     MTRR says !WB         |          |            |                  |
    ------------------------------------------------------------------

example of MTRR and PAT in Linux::

    # MTRR
    $ cat /proc/mtrr
    reg00: base=0x000000000 (    0MB), size= 8192MB, count=1: write-back
    reg01: base=0x200000000 ( 8192MB), size= 4096MB, count=1: write-back
    reg02: base=0x300000000 (12288MB), size= 1024MB, count=1: write-back
    reg03: base=0x0e0000000 ( 3584MB), size=  512MB, count=1: uncachable
    reg04: base=0x0d0000000 ( 3328MB), size=  256MB, count=1: uncachable
    reg05: base=0x0ce000000 ( 3296MB), size=   32MB, count=1: uncachable
    reg06: base=0x0cd000000 ( 3280MB), size=   16MB, count=1: uncachable
    reg07: base=0x330000000 (13056MB), size=  256MB, count=1: uncachable
    reg08: base=0x32f000000 (13040MB), size=   16MB, count=1: uncachable
    reg09: base=0x32ee00000 (13038MB), size=    2MB, count=1: uncachable

    # PAT
    # p.s. debugfs interface may be not stable
    $ cat /sys/kernel/debug/x86/pat_memtype_list 
    PAT memtype list:
    write-back @ 0xc8fd9000-0xc8fe9000
    write-back @ 0xc8fe8000-0xc8fea000
    write-back @ 0xc8fe9000-0xc8feb000
    ...
    write-combining @ 0xd0000000-0xe0000000
    write-combining @ 0xe0000000-0xe0001000
    uncached-minus @ 0xe0001000-0xe0002000
    uncached-minus @ 0xe0002000-0xe0003000
    ...

Example
-------

- `如何知道在 Windbg 中得到 Memory type(也叫做caching type) <http://www.cnblogs.com/aoaoblogs/archive/2009/11/19/1606067.html>`_
- `Cache Attribute Virtualization in Xen <http://www-archive.xenproject.org/files/xensummitboston08/Cache-Virtualization.pdf>`_
- `Copying Accelerated Video Decode Frame Buffers <https://software.intel.com/en-us/articles/copying-accelerated-video-decode-frame-buffers/>`_

  - Fast USWC(Uncachable Speculative Write Combine) to WB(Write Back) Memory Copy

Reference
---------

- ``Documentation/x86/pat.txt:`` <http://elixir.free-electrons.com/linux/v4.9/source/Documentation/x86/pat.txt>
- `LWN - x86: Full support of PAT <https://lwn.net/Articles/618811/>`_
- ``Documentation/x86/mtrr.txt`` <http://elixir.free-electrons.com/linux/v4.9/source/Documentation/x86/mtrr.txt>
- Intel Developer Manual Vol3 

  - Ch11.3 Methods of Caching Available
  - Ch11.5 Cache Controls
  - Ch11.11 Memory Type Range Registers (MTRRS)
  - Ch11.12 Page Attribute Table(PAT)
