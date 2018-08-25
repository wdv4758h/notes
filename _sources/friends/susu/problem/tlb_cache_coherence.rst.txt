
:date: 2016-11-28 00:00

We need to do TLB cache coherence by software in SMP environment

The common method is including send IPI and do TLB invalidation in other cpu.

some search:

- http://forum.osdev.org/viewtopic.php?p=190926#p190926
- TLB and Pagewalk Coherence: http://blog.stuffedcow.net/2015/08/pagewalk-coherence/

my code trace (in the progress):

- ./tlb_shootdown_linux.rst
