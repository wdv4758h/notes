========================================
ARM Introduction
========================================

分類：

* ARM-Cortex A : 行動計算  (A for Application)
* ARM-Cortex M : 工業控制  (M for Microcontroller)
* ARM-Cortex R : real-time (R for Real-time)


其他常見的縮寫：

* e : EABI
* l : little endian
* hf : hard float point
* vfp : vector float point
* fp : hf 以前的名字


Float Point
========================================

三種模式：

* soft
    - 所有浮點數運算由軟體實作，效率不高
    - 與其他兩者相容
* softfp
    - 浮點數運算交給 FPU 處理，用整數暫存器傳遞
    - 和 hard 不相容
* hard
    - 浮點數運算交給 FPU 處理，用浮點暫存器傳遞
    - 和 softfp 不相容


預設狀況下 "armel" 會使用 softfp，
把 hard 模式的 armel 視為另一個 ABI，
稱為 "armhf"

softfp 模式下會不斷有整數和浮點數之間的轉換，
而使用 hard 模式時大約可以節省 20 個 CPU cycles，
使的某些程式可以獲得 20 ~ 25 % 的效能提升，
對於大量使用浮點數運算的程式有人甚至獲得了 300 % 的提升。

GCC 參數: ``-mfloat-abi=hard -mfpu=vfp``


Thumb
========================================

Thumb
------------------------------

ARM 有兩套指令集，
一套是 ARM，
另一套是 Thumb。

Thumb 的目地是要增加 code 的密度，
Thumb instruction set 實作的是 ARM instruction set 的子集，
指令用了 16 bits，
藉由限制一些能力來換取空間。

(本來可以放 32 條 32 bits 的 ARM 指令換成放 Thumb 就可以放 64 條)

Thumb 沒有 coprocessor 指令、Semaphore 指令、CPSR 和 SPSR 相關的指令、乘加指令、64 位元乘法指令，
指令的第二個 operand 受到限制，
只有 branch 指令可以跳 address，
採用的是 relative jump，
可以跳到的範圍有限制。

Thumb 和 ARM 在組語上是相同的，
但是 compile 後會產生初步同的資料，
所以「Thumb 是一套 16 bits 的指令集，為 ARM 指令集的子集，可以在 32 bits 的 ARM 指令集找到對應」，
Thumb mode 和 ARM mode 兩個不能同時運作，
選好後處理器就會依照指定的模式運作，
如果是 Thumb mode 的話會進行解壓縮，
轉換成 ARM 指令來執行。


Thumb2
------------------------------

Thumb2 在原本單純的 16 bits Thumb 指令集加入了一些 32 bits 的指令，
也加入了 IT (If Then) 指令 (對於 ARM 指令集來說，IT 指令不會產生任何 code)。


Reference
========================================

* `Wikipedia - ARM <https://en.wikipedia.org/wiki/ARM_architecture>`_
* `Wikipedia - List of ARM microarchitectures <https://en.wikipedia.org/wiki/List_of_ARM_microarchitectures>`_
* `關於armhf (hard-float ABI for ARM) <http://www.claudxiao.net/2012/02/armhf/>`_
* `Thumb Instruction in ARM <http://stackoverflow.com/questions/10638130/thumb-instruction-in-arm>`_
