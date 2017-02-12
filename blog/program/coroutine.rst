:title: coroutine 概念
:slug: coroutine
:date: 2014-02-06 21:33
:category: Misc
:tags: coroutine, program
:author: wdv4758h
:summary: coroutine

直接往下到 Reference 看別人寫的文章比較好 (X




coroutine 是由 Melvin Conway 在 1960 年代所提出來

Coroutine 基本概念
========================================

Coroutine 可以視為 **可以中斷及繼續執行的 function call**

在程式語言中，通常這種中斷會用 **yield** 來表示，中斷時程式狀態會被保留，下次就恢復到該狀態繼續執行

Generator
========================================

generator 又稱為 semicoroutine

雖然 generator 一樣可以中斷、繼續，但是 coroutine 可以指定從哪裡繼續執行，而 generator 不行，generator 只能回到上次中斷處

但是 coroutine 可以用 generator 實作出來

Coroutines in Python
========================================

- `Improve Your Python: 'yield' and Generators Explained <http://www.jeffknupp.com/blog/2013/04/07/improve-your-python-yield-and-generators-explained/>`_
- `Tasks and coroutines <http://docs.python.org/3.4/library/asyncio-task.html>`_

Reference
========================================

- `Coroutine: 入門篇 <https://electronic-blue.herokuapp.com/blog/2012/06/coroutine-an-introduction/>`_
- `使用 Coroutine 實作 Iterator <https://electronic-blue.herokuapp.com/blog/2012/06/implement-iterators-by-coroutine/>`_
- `使用 Coroutine 改寫狀態機 <https://electronic-blue.herokuapp.com/blog/2012/06/rewrite-state-machines-by-coroutine/>`_
- `使用 Coroutine 改寫狀態機－續 <https://electronic-blue.herokuapp.com/blog/2012/06/rewrite-state-machines-by-coroutine-part-2/>`_
- `使用 coroutine 實做 user-level thread <http://blog.linux.org.tw/~jserv/archives/001848.html>`_
- `Coroutine - wikipedia <https://en.wikipedia.org/wiki/Coroutine>`_
