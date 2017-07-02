Protection Ring/Privilege level

- 決定一個程式能不能 access 一塊記憶體, 執行特定的 cpu instruction (privilege instruction)
  
  a. 程式的權限基於 cpu 的 register, 程式切換時 OS 會 context switch 掉 register.
  b. 記憶體的權限透過 page table 或 x86 segment 的 metadata.
  c. cpu 執行特定 instruction 會檢查 register 上面的 ring 值

- Advanced

  - system call 如何實作, gate
  - other thing like system call: hypervisor call, arm supervisor call(trustzone)
  - Linux vDSO: sysenter, inject vDSO section in process. e.g. gettimeofday()
  - https://0xax.gitbooks.io/linux-insides/content/SysCall/
  - http://duartes.org/gustavo/blog/post/cpu-rings-privilege-and-protection/: gate destriptor, sysenter


- http://duartes.org/gustavo/blog/post/cpu-rings-privilege-and-protection/

  - CPL & RPL.
  - memory protection 1 (segment): MAX(CPL, RPL) <= DPL
  - memory protection 2 (page): supervisor bit and RW bit
  - 4 sub-types of gate descriptor

    - interrupt gate
    - trap gate
    - task gate
    - call gate

  - IDT(Interrupt Descriptor Table): register IDTR point to, use LIDT/SIDT to load/store register.
  - each IDT entry is a gate descriptor
  - http://wiki.osdev.org/Interrupt_Descriptor_Table
  - linux kernel (linux 4.7)

    - arch/x86/include/asm/desc.h: call gate 相關的 function
    - arch/x86/kernel/traps.c: trap_init()
    - arch/x86/include/traps.h: 定義 interrupt macro: X86_TRAP_NMI, X86_TRAP_BP,
