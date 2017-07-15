========================================
PyPy
========================================


.. contents:: 目錄


2017 - 七月
========================================

:slides: https://bitbucket.org/pypy/extradoc/raw/22d92b9985f88d6f9c039d9f8c2fa05a5781c2cf/talk/ep2017/pypy-whats-new/slides.pdf


Armin Rigo 在 EuroPython 2017 的 PyPy 近況更新。

清單：

* Python 3.5 支援
* Asynchronous 相關 Library 在效能上有顯著的優勢（跟 CPython 比）
* 更多 NumPy 支援（原本 fork 出去的 Numpypy 已經 deprecated，現在直接用上游），相容度 99.9 %
* CPython C Extension 或是用 Cython 做的 Extension 大部分會動，藉由 cpyext，但效能還待改進
* Software Transactional Memory branch 問題很多，暫時宣告失敗，改往 GIL-free、non-STM 的 PyPy 嘗試
* Reverse Debugger: revdb
* JIT 效率提昇
* CFFI 改進



參考
========================================
