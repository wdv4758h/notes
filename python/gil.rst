========================================
CPython GIL (Global Interpreter Lock)
========================================

CPython 內的 GIL 在 Multithead 上一直是知名的問題。
有了 GIL 很容易可以處理 Single Thread 的狀況，
overhead 小、C extension 容易撰寫、保證不 dead lock。
但是現在硬體內的 CPU 都有很多顆核心，
想要充分利用這些核心的話，
GIL 就變成了阻礙。

在 2016 年的 PyCon US 中，
Larry Hastings 就講了一場講述如何移除 CPython 內的 GIL 的作法，
講者討論了想要移除 GIL 時需要進行的步驟，
並且考慮不同的實作可能，
提出在儘量維持相容性的狀況下，
可以考慮的作法。
最後討論可以如何提升效能，以真正利用到多核心的效能。



Reference
========================================

* `Larry Hastings - Removing Python's GIL: The Gilectomy - PyCon 2016 <https://www.youtube.com/watch?v=P3AyI_u66Bw>`_
* [Hacker News] `Removing Python's GIL: The Gilectomy <https://news.ycombinator.com/item?id=11842779>`_
* [GitHub] `Gilectomy branch of CPython <https://github.com/larryhastings/gilectomy>`_
* [2007] `It isn't Easy to Remove the GIL <http://www.artima.com/weblogs/viewpost.jsp?thread=214235>`_
* `PEP 489 -- Multi-phase extension module initialization <https://www.python.org/dev/peps/pep-0489/>`_


Related Topics
========================================

* Tracing Garbage Collection
* Reference Counting
* Software Transactional Memory
* Global Interpreter Lock
* Python C Extension
* Locking
* Reentrancy
