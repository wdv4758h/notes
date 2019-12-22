========================================
Linux 4.20
========================================


.. contents:: 目錄


Scheduler - better "misfit" task migration in asymmetric CPU systems
====================================================================

asymmetric CPU systems 指的是像 ARM big.LITTLE 這樣 CPU 處理能力不一的平台，
當任務太吃重時搬移到能力比較強的 CPU 會有比較好的結果，
因此任務的調度會影響到不少效能。



Faster FUSE
========================================



RAID10 improvement for MD RAID (Linux Software RAID)
====================================================



Linux kernel VLA-free
========================================

C99 的 VLA (variable length array) 可以讓 array 長度動態決定，
但是需要額外成本來決定長度，
甚至可能會因為影響 stack 而造成安全性問題。

Linux kernel 在 4.20 版時正式移除掉 VLA 相關的使用，
也開啟 ``-Wvla`` 參數檢查未來任何使用 VLA 的程式碼。



XArray 資料結構
========================================

XArray 的目標是要取代 Linux kernel 內的 radix tree，
XArray 整合 lock 的能力、page cache 改進、不需要 memory pre-loading、提供許多適合現有 radix tree 使用的功能。


* `Linux - Core API Documentation - XArray <https://www.kernel.org/doc/html/latest/core-api/xarray.html>`_
* `[GIT PULL] XArray for 4.20 <http://lkml.iu.edu/hypermail/linux/kernel/1810.2/06430.html>`_



PCI Peer-to-Peer Memory
========================================
