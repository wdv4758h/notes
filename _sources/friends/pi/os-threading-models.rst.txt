================
Threading Models
================
在作業系統中，執行緒（Thread）如何被分配執行資源，根據 Threading Model 而有所不同

Threading Model 只是理論分類，實作上可能會有更多種不同的變化

名詞定義
---------
* Hardware Thread：物理上能夠同時運作的執行單元數量

  - 單核心的 CPU 只有一個 Hardware Thread
  - 多核心的 CPU 可以有多個 Hardware Thread
  - 原本這件事其實不重要，但在 Intel 做出 Hyperthreading 的技術以後，一顆 CPU 可以同時執行兩個指令，也就是有兩個 Hardware Thread

    + 實際上這種 CPU 也並不總是能夠同時執行兩個指令，但對作業系統來說，一次可以放兩個指令給這顆 CPU

* Kernel Thread：在作業系統中被排程的單位

  - 作業系統在運作時，會帶有很多 Kernel Thread，這些 Kernel Thread 要何時被放到 Hardware Thread 上執行，由作業系統中的排程器決定

* User Thread：程式所產生的 Thread

  - 對程式而言，User Thread 代表兩項並行的工作，執行的速度以及順序無法保證

* Threading Model

  - 程式在運作時，可以帶有多個 User Thread，這些 User Thread 該如何被放到 Kernel Thread 上執行，即為 Threading Model

1:1 Threading Model
--------------------
* 最簡單的 Model，一條 User Thread 對應一條 Kernel Thread
* 程式每開一條 Thread，對作業系統而言就多一項工作需要排程
* 目前大部份的系統都採用這個 Model
* 在這個 Model 底下，Thread 和 Process 之間的差異可能只有「資源是否共享」

  - 例如記憶體空間、全域變數、File descriptors、tty、...

* 例如 Pthread 的 Linux Implementation

N:1 Threading Model
--------------------
* 在一支 Process 內的所有 Thread 都對應到同一條 Kernel Thread
* 作業系統只管排程到某個 Process，這支 Process 自己決定要讓哪一條 Thread 執行

  - 也就是 Process 內部自己有一個排程器

* 這種方式被稱為 Green Thread

  - 這個名字是從 Java 1.1 來的

* 物理上，這些 User Thread 不可能被同時執行，因為它們都在同一個 Kernel Thread 裡面

  - 若有任何一條 User Thread 呼叫了 Blocking System Call，整個 Process 都會被 Block 住
  - 因為一次只有一個 User Thread 能被執行，Process 自帶的排程器當然也在這個限制之下

* 註：CPython VM 並不是使用 N:1 Threading Model

  - 每條 Python Thread 都是 Kernel Thread
  - 但因為 CPython 採用的 GC 機制並不是 Thread Safe，所以有個 Process Level 的 GIL 限制一次只有一條 Python Thread 能被執行
  - 但在執行 Blocking I/O 時，GIL 會解除，所以 CPython 程式並不會因為 Blocking I/O 而完全卡住

M:N Threading Model
--------------------
* 最複雜的 Model，多條 User Thread 對應多條 Kernel Thread
* Process 內需要一個排程器，且這個排程器需要和作業系統內的排程器溝通

  - 若兩方不溝通，則可能發生一支 Process 對應的兩條 Kernel Thread 同時被排程到，此時 Process Context 會同時被兩條 Kernel Thread 修改
