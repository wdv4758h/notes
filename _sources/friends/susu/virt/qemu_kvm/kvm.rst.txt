kvm
---
- cpu 

  - VM => regular linux process, scheduled by standard linux scheduler
  - more precisely, each vcpu appear as single linux process.

- memory management

  - SLAT: Second Level Address Translation
    
    - [Intel] Extended Page Table(EPT)
    - [AMD] Rapid Virtualization Indexing
    - [ARM] Stage 2 Translation

  - kernel feature: Kernel Same-page Merging (KSM)

    - 如果兩個 VM 有相同的 memory page, KSM 可以把兩個 VM 的 memory page 指到同一個 physical page, 減少 physical memory 的使用.
    - ksmd(daemon) 定期掃描比對跟 merge
    - 比對 algorithm:
    
      - http://blog.csdn.net/summer_liuwei/article/details/6013255
      - http://www.ibm.com/developerworks/linux/library/l-kernel-shared-memory/index.html

    - source: ``./mm/ksm.c``
    - in other system

      - ESXi: Transparent Page Sharing
      - XEN: Memory COW

- interrupt and IO

  - KVM PCIe/MSI Passthrough on ARM/ARM64: http://www.linaro.org/blog/core-dump/kvm-pciemsi-passthrough-armarm64/

- security

  - SVirt: SELinux and kvm virtualization

- ARMv8.1 VHE(Virtualization Host Extension) 

  - https://hkg15.pathable.com/static/attachments/112961/1424963684.pdf?1424963684
  - Linaro Connect 16: http://connect.linaro.org/resource/bkk16/bkk16-504/

Misc
~~~~

Reference
---------
- Architecture of the Kernel-based Virtual Machine(KVM): https://drive.google.com/drive/u/0/folders/0B25hHW4ATym7akZlWTk1ejFGWmM

