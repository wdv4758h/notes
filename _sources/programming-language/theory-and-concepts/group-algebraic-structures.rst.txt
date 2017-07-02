========================================
群論
========================================


.. contents:: 目錄


Identity Element
========================================

Identity (Empty) Element 是在定義「空」（emptiness）的概念。


rule ::

    x ⊕ e = x
    e ⊕ x = x

::

    pour(emptyGlass, x) = x
    pour(x, emptyGlass) = x

::

    add(0, x) = x
    add(x, 0) = x

::

    concat("", x) = x
    concat(x, "") = x

::

    min(∞, x) = x
    min(x, ∞) = x

::

    mul(1, x) = x
    mul(x, 1) = x

::

    f ∘ id = f
    id ∘ f = f



Semigroup
========================================

composition

rule ::

    a ⊕ (b ⊕ c) = (a ⊕ b) ⊕ c



Monoid
========================================

Monoid = Identity Element + Semigroup

rule ::

    x ⊗ e = x
    e ⊗ x = x
    x ⊗ (y ⊗ z) = (x ⊗ y) ⊗ z


monoid ``(Number, +, 0)`` ::

    fold([]) = 0
    fold([1]) = 1
    fold([5, 6, 3, 1])
      = 5 + 6 + 3 + 1
      = 15


monoid ``(Number, max, -∞)`` ::

    fold([]) = -Infinity
    fold([10]) = 10
    fold([9, 6, 5, 12])
      = 9 max 6 max 5 max 12
      = 12



Monoid Morphisms
========================================

rule ::

    h(e) = f
    h(a ⊕ b) = h(a) ⊗ h(b)

::

    sort([]) = []
    sort(xs ++ ys) = sort(xs) ⊙ sort(ys)

::

    exp(0) = 1
    exp(b + c) = exp(b) ∗ exp(c)

::

    !true = false
    !(a && b) = !a || !b



性質表
========================================

+-----------+----------+---------------+----------+
|           | Totality | Associativity | Identity |
+===========+==========+===============+==========+
| Semigroup | Required | Required      | Unneeded |
+-----------+----------+---------------+----------+
| Monoid    | Required | Required      | Required |
+-----------+----------+---------------+----------+



相關主題
========================================

* 範疇論（Category Theory）



參考
========================================

* `Algebraic patterns - Identity element <https://philipnilsson.github.io/Badness10k/posts/2016-06-29-functional-patterns-identity-element.html>`_
* `Algebraic patterns - Semigroup <https://philipnilsson.github.io/Badness10k/posts/2016-07-14-functional-patterns-semigroup.html>`_
* `Algebraic Patterns - Monoid morphisms <https://philipnilsson.github.io/Badness10k/posts/2016-08-10-functional-patterns-monoid-morphism.html>`_

* `Wikipedia - Monoid <https://en.wikipedia.org/wiki/Monoid>`_
