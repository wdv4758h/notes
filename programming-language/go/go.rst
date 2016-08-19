========================================
Go
========================================

官方的 Go compiler 用了很多 escape analysis，
所以有些 heap allocation 會被轉而長在 stack 上。

Go 的 GC 在 1.5 後又會修正一些 latency 的問題，
待之後研究。


* `Go 1.7 <https://blog.golang.org/go1.7>`_
    - SSA (Static single assignment form)
    - Bounds-checking elimination
    - CSE (Common subexpression elimination)


Reference
========================================

* `Go - Frequently Asked Questions (FAQ) <http://golang.org/doc/faq>`_
* `Wikipedia - Go <https://en.wikipedia.org/wiki/Go_%28programming_language%29>`_
* `Go GC: Solving the Latency Problem in Go 1.5 <https://sourcegraph.com/blog/live/gophercon2015/123574706480>`_
    - `HackerNews <https://news.ycombinator.com/item?id=9854408>`_

* `Go by Example <https://gobyexample.com/>`_
