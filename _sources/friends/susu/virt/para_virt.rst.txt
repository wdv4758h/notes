Para-Virtualization
-------------------
Para-Virt: https://en.wikipedia.org/wiki/Paravirtualization

basic

- no need of HW-Assisted Virtualization support by CPU.
- need special support by guest OS kernel and driver.
- performance higher than full virtualization.

features

- HW interface + Para-API
- PV 需要修改 guest OS, 但可以只改動到 OS driver 的部份.

  - Xen Windows GPLPV (a kit of PV device driver)
  - Virtio drivers

history

- [1972] IBM VM OS (earlier is CP-67). "DIAGNOSE code" instruction is like hypercall.
- The term "paravirtualization" is first used in Denali VMM: http://denali.cs.washington.edu/pubs/index.html
- also used in Xen/L4/VMWare/Wind River/Xtratum

  - Xtratum: http://www.xtratum.org/main/pubs

PV-aware OS?

- conventional OS isn't PV-aware
- VMWare PV interface: VMI(Virtual Machine Interface)
  
  - OS 可以同時支援 bare-metal HW + VMI, 因此一份 code 可以在實體機, FV 跟 PV 的 VM 上都能跑.
  - 因為 HW-Assisted Virtualization 而被淘汰, Linux 2.6.37 移出了 VMI support (2009): 
    `x86, vmi: Mark VMI deprecated and schedule it for removal <https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=d0153ca35d344d9b640dc305031b0703ba3f30f0>`_

- Usenix 2006, 幾家 Linux vendors 包含 Xen, 合作產出 paravirt-ops (pv-ops). Linux 2.6.23 開始支援 pv-ops

  - [2009] pv_ops on Dom0 kernel: http://www-archive.xenproject.org/files/xensummit_intel09/xensummit-asia-2009-talk.pdf
  - [2011] http://www-archive.xenproject.org/files/xensummit_santaclara11/aug2/5_KonradW_Update_on_Linux_PVOPS.pdf
