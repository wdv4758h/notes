- https://www.wikiwand.com/en/X86_virtualization

x86 hardware virtualization: allows multiple operating systems to simultaneously share x86 processor resources in a safe and efficient manner.

- keyword: OSs share processor resources, safe, efficient

Guide
-----
- intel VT-x

  - [05] CPU virtualization: VMX root mode, VMX instruction
  - [08] EPT: page-table virtualization 
  - [10] unrestricted guest: logical processor directly in real mode, it requires EPT.

    - `Implements BIOS emulation support forBHyVe: A BSD Hypervisor <https://2013.asiabsdcon.org/papers/abc2013-P5A-paper.pdf>`_
  - [13] VMCS shadowing: accelerate nested virtualization of VMMs. The techique like shadow page table.
  
- [supplement] nested virtualization
  
  - `[OSDI 10] The Turtles Project <https://www.kernel.org/doc/Documentation/virtual/kvm/nested-vmx.txt>`_
  - ``Documentation/virtual/kvm/nested-vmx.txt``

- [12] intel APICv

  - interrupt virtualization
  - 節省 VMExit? https://software.intel.com/en-us/blogs/2013/12/17/apic-virtualization-performance-testing-and-iozone

- intel VT-d

  - IOMMU virtualization: allow guest OS directly use peripheral devices
  - DMA and interrupt remapping, PCI passthrough
  - only PCI/PCI-E device support FLR(function level reset)

- intel GPU virtualization

  - GVT-d: direct passthrough, assign GPU to single VM
  - GVT-g: mediate passthrough: share GPU to multiple VM, command rendering using time-sharing, every VM allocate dedicated frame buffer (ballooning for security)

    - GVT-g/mediate passthrough: Usenix ATC 14

  - GVT-s: API forwarding, para-virtualization
  - https://01.org/blogs/skjain/2014/intel%C2%AE-graphics-virtualization-update

- intel network virtualization

  - address translation services(ATS): native IOV across PCI-E via address translation
  - SR-IOV: native IOV in existing single-root complex PCI Express topologies
  - MR-IOV: native IOV in new topologies (for example, blade servers), by building on SR-IOV to provide multiple root complexes which share a common PCI Express hierarchy.

- SR-IOV resources

  - SR-IOV in Xen: https://www.usenix.org/conference/wiov-08/sr-iov-networking-xen-architecture-design-and-implementation
  - Intro to Intel flexible port partitioning using SR-IOV: http://www.intel.com/content/dam/www/public/us/en/documents/solution-briefs/10-gbe-ethernet-flexible-port-partitioning-brief.pdf
  - http://blogs.scalablelogic.com/2013/12/enhanced-networking-in-aws-cloud.html

interesting
-----------

- x86_64 因為不支援 segmentation, 所以要做純 software emulation 有困難. (Qemu?)

reference
---------

- intel VT instructions: 

  - http://linasm.sourceforge.net/docs/instructions/vmx.php
  - http://virtualizationtechnologyvt.blogspot.tw/2009/04/vmx-instructions-in-x86.html

- Advanced x86: Intel Hardware Assisted Virtualization Slides: https://drive.google.com/folderview?pli=1&ddrp=1&id=0B25hHW4ATym7Z1pTUUs0cEhOMHc
- Intel Developer Manual Volume 3, Ch20 ~ Ch29
