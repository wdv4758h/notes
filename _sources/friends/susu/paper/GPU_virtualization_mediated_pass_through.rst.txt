- paper name: A Full GPU Virtualization Solution with Mediated Pass-Through
- link: https://www.usenix.org/system/files/conference/atc14/atc14-paper-tian.pdf

Outline
-------

Note
----
1. 4 GPU virtualization technique

  - Slow to Fast

    - Device Emulation (trap-and-emulate)
    - API Forwarding (ex. OpenGL API)
    - Mediate Pass-Through 
    - Direct Pass-Through

  - Device Emulation (trap-and-emulate)

    - too slow
    - complete sharing and feature

  - Direct Pass-Through
    
    - nearly 100% performance
    - no sharing, only 1 VM can use

  - API Forwarding (ex. OpenGL API)

    - slow than Mediated Pass-Through, sharing better than Pass-Through
    - hard to support full feature
      
      - complexity of guest graphic stack
      - API compatibility between different OSes.

  - Mediated Pass-Through

    - pass performance-critical resources, emulate privileged instruction
    - only sharing 7 VM for good performance

2. GPU model

   - Intel Graphic

     - rendering engine and display engine
     - use system memory
     - memory: page table

       - Global Graphic Memory: 2GB virtual address space, accessed by CPU and GPU
       - Local Graphic Memory: Multiple 2GB virtual address space, only accessed by render engine
     
     - CPU fetch commands to ring buffer for GPU (needed for supplement)
     - 4 critical interface

       - frame buffer
       - command buffer
       - GPU Page Table Entries (PTE)

         - GPU Page Table
         - Memory-Mapped I/O && Port Mapped I/O registers

       - PCI configuration space register 

3. Design and Implementation

   - Architecture

     - Mediate Pass-Through
       
       - Mix Pass-Through & trap-and-emulate

     - Xen Hypervisor: gVirt stub
       
       - extend vMMU for Mediate Pass-Through

         - Pass-Through: frame buffer & command buffer
         - trap-and-emulate: GPU Page Table Entries (PTE) & PCI configuration space register 

     - Dom0 kernel module: gVirt Mediator

       - emulate vGPU for privileged resource (trap-and-emulate)
       - GPU scheduler
       - rely on the Dom0 graphics driver to initialize the physical device and to manage power

     - Native driver
     - Qemu

       - emulate legacy VGA mode, which relys on BIOS bootstate.

   - GPU sharing

     - Mediator
       
       - Manage all vGPU of all VMs
       - emulate privileged instruction

         - handles physical GPU interrupt, generate virtual interrupt to the designated VMs
         - ex. interrupt: completion of command execution, GPU => OS
           
           - GPU => hypervisor (=> Mediator) => VM

     - render engine scheduling

       - time slice: 1/60 sec, because overhead of context switch is 1000x more than CPU's one.

     - render context switch
       
       - store internal pipeline state and I/O register states.
       - cache/TLB flush
    
     - dedicated ring buffer to carry additional command
     - display management

       - manage display engine of different VM framebuffer

video
+++++
Feature of Mediate Pass-Through

  1. Full-featured vGPU, so we can run native graphic driver in VM (no paravirtualization)
  2. 95% native performance
  3. scale-up to 7 VM
  
Mediate Pass Through
    
  1. Pass through: command buffer & frame buffer
  2. Trap and Emulate: PageTable, Register

Render Engine Sharing

  1. direct execution of guest command buffer
  2. Time-based Sharing. time quatium: 60 ms

Display Engine Sharing
Graphic Memory Resource Partitioning

    - easy to implement in current graphic driver

Secure Isolation

    - VM may map unauthorized graphic memory pages (Mediate Pass-Through)
    - VM may program unauthorized graphic memory addressses in register and commands
    - VM may DoS attack to hang GPU

Q&A

    - NVIDIA GPU doesn't support preemption, how about Intel GPU, and how can you audit GPU instruction
    
      - Intel GPU doesn't support preemption. We preempt it not at instruction level but ...
