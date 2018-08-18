========================================
Benchmark
========================================


.. contents:: 目錄


參考
========================================

* `How to run stable benchmarks <https://archive.fosdem.org/2017/schedule/event/python_stable_benchmark/>`_
    - 有些 benchmarks 每次跑結果都差很多
    - 不好的 benchmarks 會造成不好的決定
    - CPU-bound microbenchmark
        + 在同個系統跑同樣的程式碼，在不同狀況會有不同結果
        + python3 -m timeit 'sum(range(10**7))'
        + idle system: 229 ms
        + busy system: 372 ms (背景有隻 "python3 -c 'while True: pass'")
    - isolate CPUs
        + 系統和應用程式會共享 CPU、記憶體、儲存空間
        + Linux kernel 可以用 ``isolcpus=3`` 來告知不要排程到 CPU 3
        + ``taskset -c 3 python script.py`` 可以把程式固定在 CPU 3
        + idle system: 229 ms
        + busy system, isolated CPU: 230 ms
    - NOHZ_FULL & RCU
        + GRUB 的 Linux 參數加上 ``isolcpus=3``
        + ``nohz_full=3`` ：如果只有 0 或 1 個程式，跑在 CPU 3 上，關閉所有中斷
        + ``rcu_nocbs=3`` ：不要在 CPU 3 上跑 kernel 程式
    - code placement
        + memory layout 和函式位址會影響 CPU cache
    - PGO (Profiled Guided Optimizations)
        + ``./configure --with-optimizations``
        + compile with instrumentation -> run test suite to collect statistics and "branches" and "code paths" (hot code) -> use statistics to recompile CPython
    - Python hash function
        + different ``PYTHONHASHSEED=N`` cause different performance
    - other things will impact performance
        + unused environment variables
        + current working directory
        + unused CLI args
        + ...
    - 使用平均值
        + disable ASLR (Address Space Layout Randomization)
        + disable randomizing Python hash function
        + 太多會隨機影響效能的變因
        + ``timeit`` 用最小值，這是不對的
        + 對於隨機產生的干擾，要使用多個結果的平均值
    - perf
        + 新的 Python module
        + 會產生多個 process
        + 計算平均和標準差
    - 現代 Intel CPU
        + 從 2005 開始會動態調整運作頻率
        + 影響的參數有工作量、CPU 溫度、啟用的核心數目等等
        + Turbo Boost 也會影響
        + 可以用 ``sudo cpupower frequency-info`` 取得相關資訊
        + 可以在 BIOS 把 Turbo Boost 關掉，或是把 ``/sys/devices/system/cpu/intel_pstate/no_turbo`` 設成 1
    - 處理完以上影響後，效能測試會穩定很多
    - 回顧
        + 系統和干擾的程式 ➡ ``isolcpus``
        + deadcode 和 code placement ➡ PGO
        + ASLR、Python hash function、env vars、cmdline、... ➡ average + std dev
        + Turbo Boost ➡ disable
    - NOHZ_FULL & Pstate
        + ``nohz_full=3`` 關閉所有中斷
        + ``intel_pstate`` & ``intel_idel`` CPU drivers registers a scheduler callback
        + 沒有中斷代表沒有排程器中斷 (LOC in /proc/interrupts)
        + CPU 3 Pstate doesn't depend on isolated CPUs workload, but other CPU workload
        + ``intel_pstate`` & ``intel_idel`` driver 的維護者沒有試過 ``NOHZ_FULL``
        + Linux RT (real time) 的開發者說這是 feature：
            - 用固定的 CPU 頻率
            - 或是不用 ``NOHZ_FULL``
    - 快速結論
        + 設定環境準備跑效能測試 ``python3 -m perf system tune``
        + 不要再用 ``timeit``
        + 用 ``python3 -m perf timeit "YOUR_CODE"``
        + 相關文件： https://perf.readthedocs.io/en/latest/
    - perf
        + 會蒐集系統的 metadata （CPU 速度、系統運作時間、Python 版本、kernel task、...）
        + 比較兩筆結果，檢查是否有重大改變
        + 統計：min/max、mean/median、...
        + 輸出所有時間，包含 warmup
        + 檢查穩定度、畫出長方圖、...
* `Python's Web Framework Benchmarks <http://klen.github.io/py-frameworks-bench/>`_
