.. _double-q:

Double Q-learning
===============================================================================

Abstract
----------------------------------------------------------------------

原本 Q-learning 的 max operator 會造成 value 被 overestimate，
不好的影響是 outlier 讓 value 提高之後，會給 convergence 有不好的影響。

理解原本的 Q function 的 max operator 成 single estimater。
那麼這篇提出 double estimater，減輕 overestimate 的問題。

Algorithm
----------------------------------------------------------------------

.. pseudo-code::

    \state init $Q^A, Q^B, s$
    \forall{$s$}
        \state observe $r$, $s'$
        \state action selection $a$, base on $\frac{Q^A(s, \cdot) + Q^B(s, \cdot)}{2}$
        \state Choose (e.g. random) either $Q^A$ or $Q^B$ to update
        \if{update $Q^A$}
            \state Define $a^* = \arg \max_a Q^A(s', a)$
            \state $Q^A(s, a) \leftarrow Q^A(s,a) + \alpha(s, a)(r + \gamma Q^B(s', a^*) - Q^A(s, a))$
        \elsif{update $Q^B$}
            \state Define $a^* = \arg \max_a Q^B(s', a)$
            \state $Q^B(s, a) \leftarrow Q^B(s,a) + \alpha(s, a)(r + \gamma Q^A(s', a^*) - Q^B(s, a))$
        \endif
    \endfor

Line 5 選 update 的動作，某種程度上算是把 experience 切成兩部分，各自 update。
