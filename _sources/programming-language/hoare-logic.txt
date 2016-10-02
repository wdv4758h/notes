========================================
Hoare Logic (霍爾邏輯)
========================================


.. contents:: 目錄


歷史
========================================

Hoare Logic 是由英國的計算機及邏輯學家「Tony Hoare」於 1969 年所提出的 Formal System，
該系統使用邏輯規則來驗證電腦程式的正確性。



Hoare triple
========================================

::

    {P} C {Q}

P 和 Q 為 ``assertions`` ，C 是 ``command`` 。
P 是前條件，Q 是後條件。

只要 C 執行前 P 成立，則 C 執行後 Q 就成立。
注意一個點是 C 可以不終止，若 C 不終止也就沒有後面的 Q。
可以用 Q 為假來表示 C 不終止，這種情況稱為「部份正確」。
如果 C 終止而且 Q 為真，則稱為「完全正確」。


::

    (P, f, Q)

    P(σ) → Q(f(σ))



實際案例
========================================

加法
------------------------------

.. code-block:: rust

    a += 2;

::

    {a = 4} a ← a + 2 {a = 6}


沒有副作用
------------------------------

::

    {P} S {P}


Composition
------------------------------

::

    {P} S {Q}, {Q} T {R} => {P} S;T {R}



相關主題
========================================

* SMT Solver



參考
========================================

* `Wikipedia - Hoare logic <https://en.wikipedia.org/wiki/Hoare_logic>`_
* `A Hoare Logic for Rust <https://ticki.github.io/blog/a-hoare-logic-for-rust/>`_
* [HackerNews] `A Hoare Logic for Rust <https://news.ycombinator.com/item?id=12612856>`_
