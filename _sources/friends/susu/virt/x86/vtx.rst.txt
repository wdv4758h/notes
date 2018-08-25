Guide
-----
- intel VT-x

  - [05] CPU virtualization: VMX root mode, VMX instruction
  - [08] EPT: page-table virtualization 
  - [10] unrestricted guest: logical processor directly in real mode, require EPT: https://2013.asiabsdcon.org/papers/abc2013-P5A-paper.pdf
  - [13] VMCS shadowing: accelerate nested virtualization of VMMs. The techique like shadow page table.
  
Content
-------
- VMX instructions

  - VMXON/VMXOFF: enter/leave VMX operation
  - [VMEntry] VMLAUNCH/VMRESUME: launch or resume virtual machine
  - [VMExit] VMEXIT??
  - VMCALL: call to the hypervisor
  - VMFUNC: difference between VMCALL?
  - [VMCS] VMREAD/VMWRITE: read from/write to VMCS
  - [VMCS] VMPTRLD/VMPTRST: load/store VMCS pointer
  - [VMX-specific TLB] INVEPT: 
  - [VMX-specific TLB] INVVPID: 
  - http://virtualizationtechnologyvt.blogspot.tw/2009/04/vmx-instructions-in-x86.html
  - http://linasm.sourceforge.net/docs/instructions/vmx.php

- kvm example

  - picture

    .. image:: kvm_vmexit.png

 - pseudo code::

      open("/dev/kvm")
      ioctl(KVM_CREATE_VM) 
      ioctl(KVM_CREATE_VCPU)
      for (;;) {
           ioctl(KVM_RUN)
           switch (exit_reason) {
           case KVM_EXIT_IO:  /* ... */
           case KVM_EXIT_HLT: /* ... */
           }
      }
 
Reference
---------
- Advanced x86: Intel Hardware Assisted Virtualization Slides: https://drive.google.com/folderview?pli=1&ddrp=1&id=0B25hHW4ATym7Z1pTUUs0cEhOMHc
