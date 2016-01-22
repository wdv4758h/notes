========================================
Object Safety
========================================


Polymorphism (多型)
========================================

Introduction
------------------------------

Polymorphism 的概念是「為不同的 type 提供單一的介面」。

在 Polymorphism 的概念底下可以延伸好幾種不同的方式，
分別為：

* Ad hoc polymorphism
    - function 為許多種 type 實作了客製化的版本
    - 在大部分的語言中，通常是由 function overloading 來支援
* Parametric polymorphism
    - code 在撰寫時沒有提及任何特定的 type，因此可以被任何新 type 使用
    - 在 OOP 社群中通常被稱為 generics 或 generic programming
    - 在 functional programming 社群中通常直接被稱為 polymorphism
* Subtyping (subtype polymorphism, inclusion polymorphism)
    - code 在撰寫時告知由許多不同的 class 來組成
    - 在 OOP 社群中通常直接被稱為 polymorphism
* Polytypism


parametric polymorphism 和 subtyping 之間的互動會產生出 **variance** 和 **bounded quantification** 兩個概念。

C++ Template 是 Parametric 跟 Ad hoc 並行，
programmers 可以把 type 的部份做保留，
也可以針對特定的 type 自己實作客製化版本來 function overloading。


Polymorphism in Rust
------------------------------

trait 有兩種方式來達到 polymorphic，
分別是：

* monomorphisation
* trait objects

Monomorphisation
++++++++++++++++++++

Monomorphisation 為最常使用的作法，
compiler 為不同 type 生出 generic function 的特製版，
例如 C++ 的 Template 或是 Rust 中 ``fn func<T: Foo>(x: &T)`` 的寫法，
優點是可以做 static dispatching，
甚至透過 inline 來增加 performance，
缺點是需要特製許多版本，
或造成 binary 變大。

特點：

* 有各自特製化的版本，速度比較快
* 可以使用 static dispatch
* binary size 會因許多特製化而變大

Trait Objects
++++++++++++++++++++

特點：

* dynamic dispatch
* 不會有許多特製化的版本


Traits v.s. Interface v.s. Mixin
========================================


Reference
========================================

* `Rust - Frequently Asked Questions <https://www.rust-lang.org/faq.html>`_

* `Rust Book - Generics <https://doc.rust-lang.org/book/generics.html>`_
* `Rust Book - Traits <https://doc.rust-lang.org/book/traits.html>`_
* `Rust Book - Trait Objects <https://doc.rust-lang.org/book/trait-objects.html>`_

* `Rust RFCs - 0255 - Object Safety <https://github.com/rust-lang/rfcs/blob/master/text/0255-object-safety.md>`_

* `Wikipedia - Object-oriented programming <https://en.wikipedia.org/wiki/Object-oriented_programming>`_
* `Wikipedia - Polymorphism (computer science) <https://en.wikipedia.org/wiki/Polymorphism_%28computer_science%29>`_
* `Wikipedia - Mixin <https://en.wikipedia.org/wiki/Mixin>`_
* `Wikipedia - Trait (computer programming) <https://en.wikipedia.org/wiki/Trait_%28computer_programming%29>`_
* `Wikipedia - Protocol (a.k.a Interface) (object-oriented programming) <https://en.wikipedia.org/wiki/Protocol_%28object-oriented_programming%29>`_
* `Wikipedia - Parametric polymorphism <https://en.wikipedia.org/wiki/Parametric_polymorphism>`_
* `Wikipedia - Generic programming <https://en.wikipedia.org/wiki/Generic_programming>`_
* `Wikipedia - Julia (programming language) <https://en.wikipedia.org/wiki/Julia_%28programming_language%29>`_

* [Swift] `Mixins and Traits in Swift 2.0 <http://matthijshollemans.com/2015/07/22/mixins-and-traits-in-swift-2/>`_
* [Rust] `Peeking inside Trait Objects <http://huonw.github.io/blog/2015/01/peeking-inside-trait-objects/>`_
* [Julia] `Julia - Types <http://docs.julialang.org/en/latest/manual/types/>`_
* [Julia] `Julia: A Fast Dynamic Language for Technical Computing <http://arxiv.org/pdf/1209.5145.pdf>`_

* `Rosetta Code - Parametric polymorphism <http://rosettacode.org/wiki/Parametric_polymorphism>`_

* [GitHub] `traits - Optional type-checking, data dependencies, and event notifications for Python <https://github.com/enthought/traits>`_
