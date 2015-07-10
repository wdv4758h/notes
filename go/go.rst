========================================
Go
========================================

官方的 Go compiler 用了很多 escape analysis，
所以有些 heap allocation 會被轉而長在 stack 上。

Go 的 GC 在 1.5 後又會修正 latency 的問題，之後研究裡面做的事：

* `Go GC: Solving the Latency Problem in Go 1.5 <https://sourcegraph.com/blog/live/gophercon2015/123574706480>`_
* https://news.ycombinator.com/item?id=9854408

Reference
========================================

* `Go - Frequently Asked Questions (FAQ) <http://golang.org/doc/faq>`_
* `Wikipedia - Go <https://en.wikipedia.org/wiki/Go_%28programming_language%29>`_
