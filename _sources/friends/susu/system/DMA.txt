- 一個解釋 DMA 的故事: `瞭解 DMA (Direct Memory Access) <http://note.heron.me/2014/01/dma-direct-memory-access.html>`_
- 英文 wiki: https://www.wikiwand.com/en/Direct_memory_access

- linux kernel 實作

  - LDD ch13: http://www.xml.com/ldd/chapter/book/ch13.html

- ARM & linux kernel 實作

  - ARM DMA(AMBA, AHB)

    - https://www.wikiwand.com/en/Advanced_Microcontroller_Bus_Architecture
    - https://www.arm.com/zh/products/system-ip/controllers/other-system-controllers.php
    - `ARM, DMA, and memory management <https://lwn.net/Articles/440221/>`_
    - `ARM DMA-Mapping Framework Redesign and IOMMU integration <http://elinux.org/images/7/7c/Elce11_szyprowski_park.pdf>`_
    - `ARM Dma-mapping Explained <http://linuxkernelhacker.blogspot.tw/2014/07/arm-dma-mapping-explained.html>`_


DMA 英文 wiki
~~~~~~~~~~~~~
- https://www.wikiwand.com/en/Direct_memory_access
- `某人的 OS 課筆記 <http://www.csie.ntnu.edu.tw/~swanky/os/chap2.htm#IO運作處理方式>`_

DMA 可在加上 IOMMU(SMMU in ARM) 作 address translation 的支援.

- DMA 種類

  - 3rd party DMA
  - bus mastering (1st party DMA)

- DMA 範例

  - PCI: 似乎是使用 bus mastering
  - ARM AHB: SoC 或 embedded system 中其中一套複雜的 bus structure.
  
    - AMBA: Advanced Microcontroller Bus Architecture 
    - slave interface: 嵌入式 CPU 上的 software, 可以讀寫 device 中的 IO register 或區域記憶體區塊.
    - master interface: device 在不需要給於 CPU 高 overhead 的情況下, 可以 perform DMA transaction 到系統記憶體. 

- Misc

  - scatter-gather I/O, 也稱為 vector I/O: 
