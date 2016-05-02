========================================
Higher-Kinded Type (HKT)
========================================

普通的 Type 稱為「Proper Type」（例如 ``int`` 、 ``bool`` 之類的）。

一個 Type 的 Type 稱作為「Kind」，
Proper Type 的 Kind 通常標記為 ``*`` 。

Proper Type 的 Type Constructor 的 Kind 為 ``* -> *`` ，
像是 ``List<T>`` 就不是 Proper Type，
它需要 Type Parameters 來建立 Concrete Type，
這種基於另外的 Proper Type 抽象化而成的 Type 稱為「First-Order Type」，
接受一個 Type Parameter 的 First-Order Type 標為 ``* -> *`` ，
接受兩個 Type Parameters 的 First-Order Type 標為 ``* -> * -> *`` 。

基於 First-Order Type 抽象化而成的 Type 就稱為「Second-Order Type」，
Type 高於 First-Order 的就都稱為「Higher-Kinded Type」，
一個簡單的 Higher-Kinded Type 標記： ``(* -> *) -> *`` （例如 ``List<List<T>>`` ）。


概念
========================================

* `Generics of a Higher Kind <http://adriaanm.github.io/files/higher.pdf>`_
* `Scala: Types of a higher kind <http://blogs.atlassian.com/2013/09/scala-types-of-a-higher-kind/>`_
* `Higher-rank and higher-kinded types <https://www.stephanboyer.com/post/115/higher-rank-and-higher-kinded-types>`_
* `Wikipedia - Kind (type theory) <https://en.wikipedia.org/wiki/Kind_%28type_theory%29>`_



Rust
========================================

* `Higher-Kinded Polymorphism <http://www.hydrocodedesign.com/2014/04/02/higher-kinded-types/>`_
* `Rust - Higher kinded polyorphism #324 <https://github.com/rust-lang/rfcs/issues/324>`_
* `Rust/Haskell: Higher-Kinded Types (HKT) <https://gist.github.com/CMCDragonkai/a5638f50c87d49f815b8>`_
