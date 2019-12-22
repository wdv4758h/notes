========================================
RISC-V
========================================


.. contents:: 目錄


介紹
========================================

RISC-V 是開放的 ISA，
任何人可以都可以把設計拿去使用、修改、販售相關晶片。
RISC-V 的設計有考量到效能和功耗，
也提供相關的開發軟體。
RISC-V 最早是 UC Berkeley 所設計出來的，
但是後續有不少自願者和公司加入進行改進，
設計要點是 "small, fast, and low-power" 。


RISC-V 具有模組化設計，
可以根據 ISA 名稱來知道所指的內容：

* I： Base Integer Instruction Set
* M： Integer Multiplication and Division
* A： Atomic Instructions
* F： Single-Precision Floating-Point
* D： Double-Precision Floating-Point
* Q： Quad-Precision Floating-Point
* L： Decimal Floating-Point
* C： Compressed Instructions
* B： Bit Manipulation
* J： Dynamically Translated Languages
* T： Transactional Memory
* P： Packed-SIMD Instructions
* V： Vector Operations
* N： User-Level Interrupts
* G： General Purpose (代表 IMAFD)
* E： Embedded，代表有經過簡化，例如只支援 16 registers

範例：

* RV32EC： 可能是 32 bit 嵌入式系統
* RV64IMAFDC/RV64GC： 可能是資源較多的 64 bit 電腦
* RVI/RVIMAFD： 完全不考慮是 32 還是 64 bit 的討論
* RV32I： Base Integer Instruction Set，32 bit
* RV32E： RV32I 的簡化版（E = Embedded），只支援 16 registers



參考
========================================

* `Wikipedia - RISC-V <https://en.wikipedia.org/wiki/RISC-V>`_
* [GitHub] `RISC-V <https://github.com/riscv/>`_
* `RISC-V Toolchain Conventions <https://github.com/riscv/riscv-toolchain-conventions>`_

* `RISC-V Foundation | Instruction Set Architecture (ISA) <https://riscv.org/>`_
* `PULP Platform | Parallel Ultra Low Power Platform <http://www.pulp-platform.org/>`_
* `RISC-V 初探 <https://coldnew.github.io/blog/2015/a_brief_view_on_riscv/>`_

* `How RISC-V is Changing the Game <https://info.dovermicrosystems.com/doverlog/how-risc-v-is-changing-processor-design>`_
