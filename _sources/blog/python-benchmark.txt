:title: Python Benchmark for Interpreter
:slug: python-benchmark-for-interpreter
:date: 2015-02-05 13:23
:modified: 2015-02-05 13:23
:category: Python
:tags: Python, Interpreter, Benchmark, CPython, PyPy, Nuitka
:author: wdv4758h
:summary:

Introduction
========================================

什麼是 benchmark ?
------------------------------

benchmark 就是用幾個固定項目來測量不同程式的效率，
取得測量出來的數值後互相做比較，
藉此來做優劣分析，但是這作法其實是蠻粗糙的。
benchmark 這種作法一直都有人在用 (也常會被拿來說嘴)，
雖然一個程式的效率不能就這麼用 benchmark 跑出來的數字來輕易評斷，
但還是能獲得些許的資訊，或者找到進步的空間。

以下會說明幾個拿來評量 Python interpreter 的 benchmark。

實作介紹
------------------------------

CPython
++++++++++++++++++++

Python 官方實作，
中規中矩，
garbage collection 採用 reference counting。

PyPy
++++++++++++++++++++

JIT 版本實作，
garbage collection 為 incremental generational tracing，
內部 data structure 有做過改良。

Nuitka
++++++++++++++++++++

不是一個 Python interpreter 實作，
而是把 Python code compile 成單一的執行檔，
不過這樣一來也就損失了很多 Python 的特性。

Hello World
========================================

Background
------------------------------

沒什麼特別的，就是一個簡單的 Hello World，
目的是要測 interpreter 的 startup time，
在此項目中 startup time 愈小愈好。

Result
------------------------------

Test:

.. table::
    :class: table table-bordered

    +-----------------------------------+---------------+
    | CPython 2.7.9                     | 0.01 ~ 0.03 s |
    +-----------------------------------+---------------+
    | CPython 3.4.2                     | 0.02 ~ 0.04 s |
    +-----------------------------------+---------------+
    | PyPy 2.5  (Python 2.7.8)          | 0.10 ~ 0.12 s |
    +-----------------------------------+---------------+
    | PyPy3 2.4 (Python 3.2.5)          | 0.06 ~ 0.07 s |
    +-----------------------------------+---------------+
    | Nuitka compile 0.5.9 (Python 2.7) | 0.01 ~ 0.02 s |
    +-----------------------------------+---------------+
    | Nuitka compile 0.5.9 (Python 3.4) | 0.06 ~ 0.08 s |
    +-----------------------------------+---------------+

PyStone
========================================

Background
------------------------------

PyStone 是 CPython 裡面一個非常 high-level 的 benchmark (CPython ``lib/test/pystone.py`` ，
拿不同的實作跑下去會拿到各自的 PyStone，代表著整體的效能分數，
愈多的 PyStone 愈好。

Result
------------------------------

在這個項目中，PyPy JIT 的優勢大幅顯現，隨著 loop 量的上升，差距也跟著拉大。

Test: (50000 passes)

.. table::
    :class: table table-bordered

    +-----------------------------------+------------------------+
    | CPython 2.7.9                     | 59814 pystones/second  |
    +-----------------------------------+------------------------+
    | CPython 3.4.2                     | 46957 pystones/second  |
    +-----------------------------------+------------------------+
    | PyPy 2.5  (Python 2.7.8)          | 570821 pystones/second |
    +-----------------------------------+------------------------+
    | PyPy3 2.4 (Python 3.2.5)          | 475670 pystones/second |
    +-----------------------------------+------------------------+
    | Nuitka compile 0.5.9 (Python 2.7) | 188474 pystones/second |
    +-----------------------------------+------------------------+
    | Nuitka compile 0.5.9 (Python 3.4) | 94807 pystones/second  |
    +-----------------------------------+------------------------+

Test: (1000000 passes)

.. table::
    :class: table table-bordered

    +-----------------------------------+-----------------------------+
    | CPython 2.7.9                     | 56851.8 pystones/second     |
    +-----------------------------------+-----------------------------+
    | CPython 3.4.2                     | 46869.8 pystones/second     |
    +-----------------------------------+-----------------------------+
    | PyPy 2.5  (Python 2.7.8)          | 1.88367e+06 pystones/second |
    +-----------------------------------+-----------------------------+
    | PyPy3 2.4 (Python 3.2.5)          | 1.54948e+06 pystones/second |
    +-----------------------------------+-----------------------------+
    | Nuitka compile 0.5.9 (Python 2.7) | 186711 pystones/second      |
    +-----------------------------------+-----------------------------+
    | Nuitka compile 0.5.9 (Python 3.4) | 103947 pystones/second      |
    +-----------------------------------+-----------------------------+

PyBench 2.0
========================================

Background
------------------------------

PyBench 是 CPython 裡的 low-level benchmarks (CPython ``Tools/pybench``)，
PyStone 用來衡量整體效能，
PyBench 用來衡量特定細項的效能。

Richards
========================================

Background
------------------------------

和 PyStone 類似，
是 PyPy 裡的 high-level benchmark (原版本是由 Dr. Martin Richards 在 Cambridge University 用 BCPL 寫的)
(PyPy ``rpython/translator/goal/richards.py``)，
一樣給出單一的值來衡量 (Average time per iteration)，
愈低的 "Average time per iteration" 愈好。

Result
------------------------------

.. table::
    :class: table table-bordered

    +-----------------------------------+-----------+
    | CPython 2.7.9                     | 382.70 ms |
    +-----------------------------------+-----------+
    | CPython 3.4.2                     | 437.50 ms |
    +-----------------------------------+-----------+
    | PyPy 2.5  (Python 2.7.8)          | 49.66 ms  |
    +-----------------------------------+-----------+
    | PyPy3 2.4 (Python 3.2.5)          | 58.72 ms  |
    +-----------------------------------+-----------+
    | Nuitka compile 0.5.9 (Python 2.7) | 178.72 ms |
    +-----------------------------------+-----------+
    | Nuitka compile 0.5.9 (Python 3.4) | 261.62 ms |
    +-----------------------------------+-----------+

總結
========================================

Nuitka 把 Python 轉成 C++ 然後 compile，
雖然可以得到效能提升，但是缺失去很多 Python 的特質，
雖然小 script 在處理過後可以得到小小的執行檔，
但如果是一個大專案的話，
compile 出來的結果可能就會很大 (先別提是否能好好處理)，
這樣相對之下選用原本 interpreter 的方式可能還會好一些，
而且如此一來，在更改 Python 專案時也需要不斷重新 compile，
失去了一些方便性，
如果別人要把 compile 過的 Python code import 進去來用又是另外一個問題，
但不可否認，對於一個小 script 且又有 performance 和 memory 考量下，
目前可能是個選擇。

若是單純講究 performance 的話，
PyPy 的可能性會大很多，
保留原本 Python 的特質，
還有 JIT 加持，
又有更好的 garbage collection 支援，
一些 data structure 也有做過改良，
雖然 PyPy 的成熟度已經愈來愈高了，
但是還是會有地方需要改進，
若發現有比原本 CPython 慢的地方可以回報，
PyPy developer 會找到問題點然後解決 (有時是 project code 需要小改進，讓 JIT 可以幫上忙)，
而且 PyPy 還有很多更 advanced 的 interpreter features 正在實驗，
評估效能和整體架構下，可看性最高。

不過這邊的 benchmark 都只是一個粗略衡量，
還是要像 speed.pypy.org 一樣拿一些實際在用的 project 來跑，
可看性會比較高。

Reference
========================================

* `CPython benchmark suite <https://hg.python.org/benchmarks/>`_
* `IronPython Performance Report <https://ironpython.codeplex.com/wikipage?title=IP26RC1VsCPy26Perf>`_
* `Wikipedia - IronPython <http://en.wikipedia.org/wiki/IronPython>`_
* `Wikipedia - Jython <http://en.wikipedia.org/wiki/Jython>`_
* `Wikipedia - Dynamic Language Runtime <http://en.wikipedia.org/wiki/Dynamic_Language_Runtime>`_
* `Wikipedia - Common Language Infrastructure <http://en.wikipedia.org/wiki/Common_Language_Infrastructure>`_
* `Wikipedia - Cython <http://en.wikipedia.org/wiki/Cython>`_
