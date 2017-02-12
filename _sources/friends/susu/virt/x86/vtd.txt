Guide
-----
- intel VT-d

  - IOMMU virtualization: allow guest OS directly use peripheral devices
  - DMA and interrupt remapping, PCI passthrough
  - only PCI/PCI-E device support FLR(function level reset)

Content
-------
- DMA remapping: MSI-x
  
    DMA 發出的中斷為 MSI(message signaled interrupt), MSI 中要含有 device 的 memory address.
    如果要虛擬化, DMA 就要可以 access host + all vm 的 memory address, 隔離效果不好.
    解法: interrupt remapping: MSI 改成放 message id, 維護一個 message id to VM 區域的 table

- VT-d Posted-Interrupts

  - 虛擬中斷, 似乎很像 ARM vgic 的虛擬中斷, 只是 x86 是讓 VMM 寫入 VMCS 來發虛擬中斷.
  - Add VT-d Posted-Interrupts support: https://lwn.net/Articles/624245/

    - ``Documentation/virtual/kvm/devices/vfio.txt``

ref
+++
- 從 VT-x 到 VT-d Intel 虚擬化技術發展藍圖 [轉貼]: http://stenlyho.blogspot.tw/2009/01/vt-xvt-d-intel.html
- Intel VT-d (Intel Virtualization Technology for Directed I/O): https://www.thomas-krenn.com/en/wiki/Overview_of_the_Intel_VT_Virtualization_Features#Intel_VT-d_.28Intel_Virtualization_Technology_for_Directed_I.2FO.29

  - spec: http://www.intel.com/content/dam/www/public/us/en/documents/product-specifications/vt-directed-io-spec.pdf
