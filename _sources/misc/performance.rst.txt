========================================
效能要點 (Performance)
========================================


.. contents:: 目錄


參考
========================================

* `Infographics: Operation Costs in CPU Clock Cycles <http://ithare.com/infographics-operation-costs-in-cpu-clock-cycles/>`_
    - 詳細地說明各種操作所需要的 cycles，以及實務上的問題
    - 整數和浮點數轉換有成本
    - 改善 data locality
    - 改善 code locality
    - 改善 memory locality
    - 減少 allocation
    - C++ 的話減少 virtual call，可以採用 CRTP 之類的技巧
* `Latency numbers every programmer should know <https://people.eecs.berkeley.edu/~rcs/research/interactive_latency.html>`_
    - `Gist - Latency numbers every programmer should know <https://gist.github.com/hellerbarde/2843375>`_
* `Teach Yourself Programming in Ten Years <http://norvig.com/21-days.html>`_
* `2018 - uops.info: Characterizing Latency, Throughput, and Port Usage of Instructions on Intel Microarchitectures <https://arxiv.org/abs/1810.04610>`_
* `2007 - What Every Programmer Should Know About Memory - Ulrich Drepper <https://people.freebsd.org/~lstewart/articles/cpumemory.pdf>`_
* `Computer latency: 1977-2017 <https://danluu.com/input-lag/>`_
