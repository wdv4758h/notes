- ref: intel 64 and IA-32 Architectures Software Developer Manuals 3, Ch5.9

- segment

  - LGDT
  - LLDT

- interrupt

  - LIDT: load interrupt descriptor table

- control register

  - mov <CR>
  - CLTS: Clear task-switched flag in register CR0.

- invalidate cache/TLB

  - INVD
  - WBINVD
  - INVLPG

- MSR, other registers

  - RDMSR, WRMSR
  - (enabled by CR4[4]) RDPMC
  - (enabled by CR4[2]) RDTSC
  - MOV <debug registers>
  - LTR: load task register

- misc

  - HLT: halt
  - LMSW: load machine status word
