Channel IO
----------

- https://en.wikipedia.org/wiki/Memory-mapped_I/O

  在 Memory-Map IO 跟 Port-Map IO 以外的第三種 IO 方式, 主要由 mainframe 在使用.

- https://en.wikipedia.org/wiki/IBM_ESA/390#Architecture_and_memory

  IBM 的 System/360 ~ ESA/390 應該都還在用 Channel I/O 的 subsystem.

- https://en.wikipedia.org/wiki/Channel_I/O
- http://www.linux-kvm.org/images/1/13/2012-forum-channel-io-kvm-forum.pdf

  [歷史] 最早的版本是 IBM 1950s 的 mainframe, 後來 System/360 接續著用.
  System/370 開始有 subchannel style (1981), 然後 Channel IO 一直被 System z 強化跟用到現在(2012)

  - Channel IO 有 IO processor 負責做 IO 不透過 CPU, IO processor 又被稱為 DMA controller ..., 並非 general CPU. 
    IO processor 可以被當成 cpu 的 coprocessor
  - Linux Channel IO support: ``lscss``
  - VirtIO 1.0 已經 support 三種 IO 模式: MMIO, PIO, 跟 Channel IO. (virtqueue kick only??)
    virtio-ccw 就在使用 Channel IO.

- IBM, Program-Controlled Interruption Appendage: http://www.ibm.com/support/knowledgecenter/SSLTBW_2.2.0/com.ibm.zos.v2r2.idas300/s3145.htm
