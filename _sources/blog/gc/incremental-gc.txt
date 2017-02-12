:title: Incremental Garbage Collector
:slug: incremental-gc
:date: 2014-09-26 21:27
:category: Misc
:tags: Python, gc
:author: wdv4758h
:summary: Incremental Garbage Collector

前情提要 - Pause Time
========================================

在 CPython 中使用的是 reference count，所以當 count 變成 0 時就必須把空間回收，
當一個巨大的 object 要被回收時，就會產生不小的 pause time，但是這個時間是 deterministic 的。
reference count 有個問題就是 reference cycle，為了找出 cycle 就必須爬過所有 objects，
但是這就會產生 nondeterministic GC pause。

reference count 是把回收的 cost 分開在各個時間點，而 tracing 的 GC 是把回收的 cost 集中在某一段時期，
回收所需時間可能不低，在這之中得把程式 pause，可能會讓使用者感覺到停頓，
而 Incremental GC 想做的就是把這段過程拆分成好幾個小步驟，
分別在不同時間執行 (打散)，讓程式執行更平順。

Ref
========================================

- `你丟我撿！神奇的 Firefox 內部記憶體回收機制 <http://tech.mozilla.com.tw/posts/1605/你丟我撿！神奇的-firefox-內部記憶體回收機制>`_
- `Incremental GC now in Firefox Aurora <https://blog.mozilla.org/dmandelin/2012/07/20/incremental-gc-now-in-firefox-aurora/>`_
- `Incremental GC in Firefox 16! <https://blog.mozilla.org/javascript/2012/08/28/incremental-gc-in-firefox-16/>`_
- `Incremental Garbage Collector in PyPy <http://morepypy.blogspot.tw/2013/10/incremental-garbage-collector-in-pypy.html>`_
