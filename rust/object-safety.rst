========================================
Object Safety
========================================

.. contents:: Table of Contents


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


Variance
------------------------------

假設有個 type 叫作 ``Animal`` ，
另外有個繼承自 ``Animal`` 的 type 叫 ``Cat`` ，
那對於他們的 array 分別可以有幾種不同的關係：

* Covariant: ``Cat[]`` 是 ``Animal[]``
* Contravariant: ``Animal[]`` 是 ``Cat[]``
* Invariant:  ``Animal[]`` 不是 ``Cat[]`` ， ``Cat[]`` 不是 ``Animal[]``


+---------------------+---------------+-------------+
|                     | Argument Type | Return Type |
+=====================+===============+=============+
| C++, Java, Scala, D | Invariant     | Covariant   |
+---------------------+---------------+-------------+
| C#                  | Invariant     | Invariant   |
+---------------------+---------------+-------------+
| Sather              | Contravariant | Covariant   |
+---------------------+---------------+-------------+
| Eiffel              | Covariant     | Covariant   |
+---------------------+---------------+-------------+


Bounded Quantification (Bounded Polymorphism)
---------------------------------------------

在原先沒有 polymorphism 的狀況下，
一個 function 名稱只能吃固定的 type 當參數並回傳固定的 type。
有了 polymorphism 後可以吃各種不同的 type 當參數並回傳各種不同的 type。
但是其中又想在這樣的彈性中加上一些限制來確保 code 在使用時一定有特定的實作可以用呢？

Bounded Quantification 就是要利用 subtyping
來對原本沒有限制 type 的 parametric polymorphism 做一些限制，
藉此保留可以使用任意 type 的彈性又確保該 type 含有特定的性質。


Rust - Bounds (trait restrictions)
++++++++++++++++++++++++++++++++++

.. code-block:: rust

    trait MyTrait {
        fn func(&self, i32) -> i32;
    }

    impl MyTrait for i32 {
        fn func(&self, data: i32) -> i32 {
            return self + data;
        }
    }

    // Bounds, type "T" must have implmentation of "MyTrait"
    fn f<T: MyTrait>(data: T) {
        println!("{}", data.func(100));
    }

    fn main() {
        f(30_i32);   // pass, 130
        f(30_i64);   // fail, "MyTrait" is not implemented for the type "i64", can not call "f"
    }



C++ CRTP
++++++++++++++++++++

C++ 中使用到的 CRTP 技巧即是 Bounded Quantification，
其稱為 F-bounded quantification 或是 recursively bounded quantification，
範例：

.. code-block:: cpp

    // The Curiously Recurring Template Pattern (CRTP)
    template<class T>
    class Base {
        // methods within Base can use template to access members of Derived
    };
    class Derived : public Base<Derived> {  // Here !!!
        // ...
    };


Julia - ``<:`` operator
+++++++++++++++++++++++

.. code-block:: julia

    type X
        data::Int32
        func::Function

        function X()
            instance = new()
            instance.data = 42
            instance.func = function ()
                return instance.data + 42
            end
            return instance
        end
    end

    function f{T<:X}(data::T)   # T must be subtype of X
        return data.func()
    end


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

* Rust
    - `Rust - Frequently Asked Questions <https://www.rust-lang.org/faq.html>`_

    - `Rust Book - Generics <https://doc.rust-lang.org/book/generics.html>`_
    - `Rust Book - Traits <https://doc.rust-lang.org/book/traits.html>`_
    - `Rust Book - Trait Objects <https://doc.rust-lang.org/book/trait-objects.html>`_
    - `Rust Book - Trait bounds on generic functions <https://doc.rust-lang.org/book/traits.html#trait-bounds-on-generic-functions>`_
    - `Rust by Example - Bounds <http://rustbyexample.com/trait/bounds.html>`_
    - `Visualizing Rust's type-system <http://jadpole.github.io/rust/type-system/>`_

    - `Rust RFCs - 0255 - Object Safety <https://github.com/rust-lang/rfcs/blob/master/text/0255-object-safety.md>`_

    - [Rust] `Peeking inside Trait Objects <http://huonw.github.io/blog/2015/01/peeking-inside-trait-objects/>`_

* Julia
    - `Julia - Types <http://docs.julialang.org/en/latest/manual/types/>`_
    - `Julia: A Fast Dynamic Language for Technical Computing <http://arxiv.org/pdf/1209.5145.pdf>`_
    - `Wikibooks - Introducing Julia/Types <https://en.wikibooks.org/wiki/Introducing_Julia/Types>`_
    - `Learn Julia in Y Minutes <https://learnxinyminutes.com/docs/julia/>`_
    - `Julia By Example <http://samuelcolvin.github.io/JuliaByExample/>`_
    - `Wikipedia - Julia (programming language) <https://en.wikipedia.org/wiki/Julia_%28programming_language%29>`_

* Wikipedia
    - `Wikipedia - Object-oriented programming <https://en.wikipedia.org/wiki/Object-oriented_programming>`_
    - `Wikipedia - Polymorphism (computer science) <https://en.wikipedia.org/wiki/Polymorphism_%28computer_science%29>`_
    - `Wikipedia - Mixin <https://en.wikipedia.org/wiki/Mixin>`_
    - `Wikipedia - Trait (computer programming) <https://en.wikipedia.org/wiki/Trait_%28computer_programming%29>`_
    - `Wikipedia - Protocol (a.k.a Interface) (object-oriented programming) <https://en.wikipedia.org/wiki/Protocol_%28object-oriented_programming%29>`_
    - `Wikipedia - Parametric polymorphism <https://en.wikipedia.org/wiki/Parametric_polymorphism>`_
    - `Wikipedia - Covariance and contravariance (computer science) <https://en.wikipedia.org/wiki/Covariance_and_contravariance_%28computer_science%29>`_
    - `Wikipedia - Bounded quantification <https://en.wikipedia.org/wiki/Bounded_quantification>`_
    - `Wikipedia - System F (a.k.a Polymorphic Lambda Calculus) <https://en.wikipedia.org/wiki/System_F>`_
    - `Wikipedia - Lambda cube <https://en.wikipedia.org/wiki/Lambda_cube>`_
    - `Wikipedia - System F-sub <https://en.wikipedia.org/wiki/System_F-sub>`_
    - `Wikipedia - Generic programming <https://en.wikipedia.org/wiki/Generic_programming>`_
    - `Wikipedia - Julia (programming language) <https://en.wikipedia.org/wiki/Julia_%28programming_language%29>`_
    - `Wikipedia - Late binding <https://en.wikipedia.org/wiki/Late_binding>`_

* Others
    - [Swift] `Mixins and Traits in Swift 2.0 <http://matthijshollemans.com/2015/07/22/mixins-and-traits-in-swift-2/>`_

    - `Rosetta Code - Parametric polymorphism <http://rosettacode.org/wiki/Parametric_polymorphism>`_

    - [GitHub] `traits - Optional type-checking, data dependencies, and event notifications for Python <https://github.com/enthought/traits>`_
