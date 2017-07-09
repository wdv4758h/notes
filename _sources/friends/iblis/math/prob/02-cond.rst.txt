Conditional Probability
===============================================================================

機率反應對事情的瞭解程度。選擇題從機率變邏輯。

在瞭解（觀測）到某些情報後， Sample Space 會改變，機率改變了。


:math:`P` of :math:`o_i` given :math:`Y` :

.. math::

    \begin{align}
        Y & = \{o_1, \dots, o_n\} \\
        P(o_i|Y) & = \frac{P(o_i)}{P(o_1) + \dots + P(o_n)} \\
          & = \frac{P(o_i)}{P(Y)}
    \end{align}


:math:`P` of :math:`X` given :math:`Y` :

.. math::

    \begin{align}
        X & = \{o_1, o_2, q_1, q_2\} \\
        Y & = \{o_1, o_2, o_3\} \\
        P(X|Y) & = P(o_1|Y) + P(o_2|Y) \\
          & = \frac{P(X \cap Y)}{P(Y)} \\
        P(q_1|Y) & = 0
    \end{align}


Product Rule

.. math::

    \begin{align}
        P(X \cap Y) & = P(X|Y) P(Y) \\
                    & = P(Y|X) P(X)
    \end{align}


Properties
----------------------------------------------------------------------

#.

    .. math::

        P(X|Y) = \frac{P(X \cap Y)}{P(Y)} \ge 0

#.

    .. math::

        P(Y|Y) = \frac{P(Y \cap Y)}{P(Y)} = 1

#. :math:`A,B` Mutual Exclude

    .. math::

        P(A \cup B|Y) = \frac{P(A)}{P(Y)} + \frac{P(B)}{P(Y)} = P(A|Y) + P(B|Y)


.. _prob-total-prob:

Total Probability 定理
----------------------------------------------------------------------

全機率定理

從 :ref:`prob-axioms-prop` (6) 衍生

.. math::

    \begin{align}
        P(A) & = P(A \cap C_1) + P(A \cap C_2) + \dots + P(A \cap C_n) \\
             & = P(A|C_1)P(C_1) + P(A|C_2)P(C_2) + \dots + P(A|C_n)P(C_n)
    \end{align}


Bayes' Rule
----------------------------------------------------------------------

可以讓我們關心的條件互換、改變。

.. math::

    P(C_j|A) = \frac{P(A|C_j)P(C_j)}{P(A|C_1)P(C_1) + \dots + P(A|C_n)P(C_n)}


proof:

.. math::

    \begin{align}
        P(C_j|A) & = \frac{P(C_j \cap A)}{P(A)} \\
                 & = \frac{P(A \cap C_j)}{P(A)} \\
                 & = \frac{P(A|C_j)P(C_j)}{P(A)} \\
        \text{By Total Probability}
                 & = \frac{P(A|C_j)P(C_j)}{\sum_{i=1}^n P(A|C_i)P(C_i)}
    \end{align}
