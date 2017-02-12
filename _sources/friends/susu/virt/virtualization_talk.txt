find a good example: https://drive.google.com/file/d/0B5ew6mM75LHocDFSbXNFRUdud00/view

Thinking
--------

- intro

  - Emulation (Full virtualization)
  - Hardware-Assisted Virtualization
  - ParaVirtualization

  - ParaVirtualization is general concept, with many different type

    - http://wiki.xen.org/wiki/Virtualization_Spectrum
  
- basement model

  - VM is host process
  - Memory System
  - IO

    - directed pass through
    - trap and emulate

- Hardware-Assisted Virtualization

  - ring & interrupt handling
  - 2 level page table
  - IO

    - file system:
    - network: SR-IOV
    - graphic: API forwarding, Mediated Pass-Through
    
- IO ParaVirtualization
