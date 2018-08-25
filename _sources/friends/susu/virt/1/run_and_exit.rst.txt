- http://blog.csdn.net/dashulu/article/details/17090293

Qemu run vcpu::

  kvm_cpu_exec()

  - kvm_vcpu_ioctl(cpu, KVM_RUN, 0)
  - switch (run->exit_reason) ...

KVM_RUN vcpu_ioctl::

  [x86]

     kvm_vcpu_ioctl()
  => kvm_arch_vcpu_ioctl_run() // x86 version
  => vcpu_run()                // infinite loop for VM
  => vcpu_enter_guest()    

     - kvm_x86_op->run() = vmx_vcpu_run() 
  
       - run guest OS. // inline asm, VMLAUNCH
       - vmx->exit_reason = vmcs_read32(VM_EXIT_REASON);

     - kvm_x86_op->handle_exit() = vmx_handle_exit()

       - kvm_vmx_exit_handlers[vmx->exit_reason]

  [arm64]

     kvm_vcpu_ioctl()
  => kvm_arch_vcpu_ioctl_run()
     
     [1] ret = kvm_call_hyp(__kvm_vcpu_run, vcpu); 
    
         [ ] kvm_call_hyp == __kvm_call_hyp // kvm_call_hyp at ``arch/arm64/include/asm/kvm_host.h``
         [ ] __kvm_vcpu_run == __guest_run
         [2] __guest_run() // at ``arch/arm64/kvm/hyp/switch.c``

             [3] vcpu = kern_hyp_va(vcpu);
             [3] host_ctxt = kern_hyp_va(vcpu->arch.host_cpu_context);
             [3] again: exit_code = __guest_enter(vcpu, host_ctxt); // at ``arch/arm64/kvm/hyp/entry.S``

                 [4] run guest OS by exception return instruction (ERET) // PC = ELR_hyp, CPSR = SPSR_hyp

             [3] if (exit_code == ARM_EXCEPTION_TRAP && !__populate_fault_info(vcpu)) goto again

     [1] handle_exit() // arm64/kvm/handle_exit.c , arm/kvm/handle_exit.c
    
         [2] arm_exit_handlers[]

----

- QEMU / KVM interface

  - enter: kvm_vcpu_ioctl(KVM_RUN)
  - exit: ioctl syscall return, struct kvm_run (shared memory, mmap vcpu_fd)

    - struct kvm_run: Documentation/virtual/kvm/api.txt ch5 The kvm_run structure
    - QEMU use ``kvm_run->exit_reason`` to do device emulation and ... etc. (``kvm_cpu_exec``)
    - shared memory, mmap vcpu_fd: ``env->kvm_run = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, env->kvm_fd, 0);     at kvm_init_vcpu()``

- KVM / Guest interface

  - [x86] enter: vmlaunch instruction
  - [x86] exit: vmexit, VMCS exit_reason field
  - [arm64] enter: ERET or ?? instruction
  - [arm64] exit: HSR register

----

MMIO::

  
  -  arm_exit_handlers[ESR_ELx_EC_IABT_LOW, ESR_ELx_EC_DABT_LOW] = kvm_handle_guest_abort()
  => kvm_handle_guest_abort() // at ``arch/arm/mmu.c``
  
     - io_mem_abort()         // at ``arch/arm/mmio.c``

       - kvm_io_bus_write() (or read)                // at ``virt/kvm/kvm_main.c``
       - kvm_handle_mmio_return()
       - run->exit_reason = KVM_EXIT_MMIO; return 0; // handled in userland, QEMU emulation

     - user_mem_abort()       // at ``arch/arm/mmu.c``

MMIO2

- kvm_io_bus_write()     // at ``virt/kvm/kvm_main.c``

  - kvm_iodevice_write() 

IO device and bus

- ``struct kvm_io_device`` at ``include/kvm/iodev.h``

  - ``struct kvm_io_device_op`` has read, write, destructor 3 function pointers
  - kvm_iodevice_write() = dev->op->write() // kvm_iodevice_read/destructor also
  
- ``struct kvm_io_bus`` at ``include/linux/kvm_host.h``

  - example:

    - (``struct kvm_io_bus``) bus->range[idx].dev
    - ``struct kvm_io_bus`` => ``struct kvm_io_range`` => ``struct kvm_io_device``
