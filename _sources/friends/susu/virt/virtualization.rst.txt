virtualization basic
--------------------
- Virtualization Theory (Formal Requirements for Virtualizable Third Generation Architecture (1974))

  - sensitive instruction

    - mode referencing instruction
    - sensitive register/memory access instruction
    - storage protection system referencing instruction
    - all I/O instruction (guess: memory-mapped + port-mapped I/O)

  - privileged instruction

x86 hardware-assisted virtualization
------------------------------------
index: ./x86/index.rst

- intel VT-x and VT-i: VT for x86 and itanium(IA 64)
- intel VT-d: Virtualization of Direct IO

internal
~~~~~~~~
- trap in Hardware Assisted Virtualization
  
  - http://pages.cs.wisc.edu/~remzi/OSTEP/vmm-intro.pdf
