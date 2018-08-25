Positive-definite Matrix
===============================================================================

Linear algebra 中，有一 square, symmetric, real matrix (對稱的實數方陣)
:math:`A` 。
如果這個 scalar

.. math::


    \vec{x}^\mathsf{T} A \vec{x} > 0, \,\forall \vec{x} \neq \vec{0}`

Where :math:`\vec{x}` is a column vector.


條件改成 :math:`\geq` 就是 `positive-semidefinite`


Julia 有::

    isposdef


判定
----------------------------------------------------------------------

好多種等價的判定方法。

#. :math:`A` 所有 eigen values :math:`\lambda_i` 都是正的


#. 左上角的 sub-matrix :math:`1 \times 1` 到 :math:`n \times n`
   的行列式都是正的


Ref
----------------------------------------------------------------------

- https://en.wikipedia.org/wiki/Positive-definite_matrix
