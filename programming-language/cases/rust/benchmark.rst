========================================
Rust Benchmark
========================================


.. contents:: 目錄


介紹
========================================

效能測試可以根據測試範圍區分，
小如單個函式的就稱為 Micro Benchmarking，
大如整個系統的就稱為 Macro Benchmarking。


注意的是 Micro Benchmarking 並不代表整個系統的運作效能，
有可能在 Micro Benchmarking 表現良好，
但是在最後串起來組成整個系統時出現問題，
導致最後運作效能不佳，
例如有個效能良好的函式在最後整合時呼叫了數萬遍而不是需要的數百遍。
Micro Benchmarking 可以作為參考，但不是全部，各元件整合的狀況也很重要。



需求
========================================

* 容易寫效能比較的案例
* 可以比較前後版本輸出差異
    - 輸出在 Terminal
    - 輸出成 HTML
* 每個測效能的回合要能避免 cache 之類的影響



cargo-benchcmp
========================================

:Repo: https://github.com/BurntSushi/cargo-benchcmp


cargo-benchcmp 可以比較先前和現在測出來的結果差異，
變快和變慢會用不同顏色顯示，
並且會計算出效能改變比例，
在比較效能變化時非常方便。



hyperfine
========================================

:Repo: https://github.com/sharkdp/hyperfine


可以比較數個指令的執行速度



Criterion - statistics-driven micro-benchmarking
================================================

:Repo: https://github.com/japaric/criterion.rs



參考
========================================

* `Wikipedia - Cycles Per Instruction <https://en.wikipedia.org/wiki/Cycles_per_instruction>`_
* `The relative performance of C and Rust <http://dtrace.org/blogs/bmc/2018/09/28/the-relative-performance-of-c-and-rust/>`_
