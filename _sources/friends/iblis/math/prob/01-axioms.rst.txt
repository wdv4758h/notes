Probability Axioms
===============================================================================

統計在建立機率模型；機率在運用機率模型


Terms
----------------------------------------------------------------------

.. math::

    P(A) = 0.6

Input
    Event

Domain
    定義域即 Event Space , Event 是離散的

Output
    0 - 1 之間的值

Event
    自己定義的敘述。
    一個 *Set*, 內容是 0 or more samples

Sample
    一次實驗的 outcome

Sample Space
    所有可能的 outcome 形成的 *Set* :math:`S`, 且 :math:`P(S) = 1`

Event Space
    一種 sample(s) 組合 形成一種 *Event* 。
    所有 sample(s) 組合 形成 Event Space。

    e.g. Sample Space :math:`S = \{ foo, bar, baz \}`
    其中一個 Event :math:`\{ foo, baz \}`
    而此 Event Space 中有 8 個 Event， 即 :math:`2^3 = 8`
    ，每個 sample 視為 boolen ，選或不選。


Axioms
----------------------------------------------------------------------

#.
    .. math::

        \forall \  \text{Event $A$,} \  P(A) \ge 0

#.
    .. math::

        P(S) = 1

#. 在講獨立事件
    .. math::

        \text{Event $A_1$, $A_2$, $\dots$ Mutual Exclude, then }

        P(A_1 \cup A_2 \cup \dots)
        = P(A_1) + P(A_2) + \dots


.. _prob-axioms-prop:

Properties
----------------------------------------------------------------------

#. from axiom 3

    .. math::

        \begin{align}
            E & = \{ o_1, o_2, \dots, n \} \\
              & = \{ o_1 \} \cup \{ o_2 \} \cup \dots \cup \{ o_n \} \\
            P(E) & = P(\{ o_1 \}) + P(\{ o_2 \}) + \dots + P(\{ o_n \}) \\
        \end{align}

#. 做實驗沒結果的機率？不可能

    .. math::

       P(\phi) = 0


    .. math::

       \because S \cap \phi = \phi
       \therefore S , \phi \text{ is Mutual Exclude}


#.

    .. math::

        P(A) = 1 - P(A^c)


#.

    .. math::

        P(A) = P(A - B) + P(A \cap B)

#.

    .. math::

        P(A \cup B) = P(A) + P(B) - P(A \cap B)

#. 只要找得到 :math:`S` 的切割方法， :math:`A` 的機率就有算法

    .. math::

        C_1, C_2, \dots, C_n \text{ Mutual Exclude, and }

        C_2 \cup C_2 \cup \dots \cup C_n = S

        \forall \text{ Event $A$ }

        P(A) = P(A \cap C_1) + P(A \cap C_2) + \dots + P(A \cap C_n)

#.

    .. math::

        A \subset B, \text{ then } P(A) < P(B)


#. Boole's 不等式。對任意事件 :math:`A_i`

    .. math::

        P(\cup_{i=1}^n A_i) \le \sum_{i=1}^n P(A_i)


#. Bonferroni's 不等式。對任意事件 :math:`A_i`

    .. math::

        P(\cap_{i=1}^n A_i) \ge 1 - \sum_{i=1}^n P(A^c_i)
