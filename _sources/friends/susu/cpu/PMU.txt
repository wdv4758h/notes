PMU(Performance Monitoring Unit)
--------------------------------
CPU 上面支援監控效能相關的 CPU 事件, 如 instruction fetch, L2 cache miss, hardware interrupt receive 的數量.

通常 CPU 上會有數量不等的 register 來選擇紀錄的 event 以及讀取紀錄的值. x86 中這些 register 稱為 MSR(Model-Specific Register)
 
- Intel P6 家族

  - 4 MSR, 2 個唯讀的 counter, 2 個用於選取 event, 稱為 event-select MSR.

- CPU event 範圍

  - CPU cycles
  - CPU instruction retired(executed)
  - L1, L2, L3 cached access: hit and misses
  - FPU
  - Memory IO: read, write, stall cycles
  - Resource IO: read, write, stall cycles

- Program, x86

  - ``rdmsr``, ``wrmsr`` instruction
  - linux kernel module ``msr``, ``/dev/cpu/<x>/msr``
  - user-space tool ``msr-tool``

reference
---------
- `model-specific register - wikipedia <https://www.wikiwand.com/en/Model-specific_register>`_
- System Performance Ch6.4.1
