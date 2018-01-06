Least-Squares Methods for Policy Iteration
===============================================================================

`Approximate RL` 用了 function approximator 是為了解 large state space 跟
continuous state-action space。
本章的方法是 Approximate RL 的其中一個分支：
`least-squares methods for policy iteration`

- Least-Squares TD

- Least-Squares policy evaluation

- Bellman residual minimization

Central idea: `approximate policy iteration`


Classic Policy Iteration
----------------------------------------------------------------------

基本上的演算法就是兩個步驟

Let :math:`k` is iteration number.

.. math::

    & \text{find}\ Q^{\pi_0}(s, a) \\
    & \pi_1 \leftarrow \arg \max_{a \in A} Q^{\pi_0}(s, a),\ \forall s \in S \\
    & \text{find}\ Q^{\pi_1}(s, a) \\
    & \pi_2 \leftarrow \arg \max_{a \in A} Q^{\pi_1}(s, a),\ \forall s \in S \\
    & \dots

直到 converge。
這裡的找 Q 的動作就是 `policy evaluation` ；
找 :math:`\pi_{k+1}` 就是 `policy improvement`

`policy evaluation` 的操作可以是用 Bellman equation

.. math::

    Q^\pi = B^\pi_Q(Q^\pi)

:math:`B^\pi_Q` 是 Bellman mapping (a.k.a backup operator)，定義如下

.. math::

    [B^\pi_Q(Q^\pi)](s, a) = E[R(s, a, s') + \gamma Q(s', \pi(s'))]

同理，對 :math:`V` function 的 Bellman equation

.. math::

    V^\pi = B^\pi_V(V^\pi)

Where Bellman mapping for :math:`V` function:

.. math::

    [B^\pi_V(V^\pi)](s) = E[R(s, \pi(s), s') + \gamma V(s)]


Classic Policy Iteration 需要明確的寫出 value function，
在 state space 炸開的時候，就會窒礙難行。
而人們才會找 approximator。


Least-Squares Method for Approximate Policy Iteration
----------------------------------------------------------------------

主要有兩個分支

    - projected policy iteration

        - one-shot: least-squares TD

        - iterative: least-squares policy evaluation

    - Bellman residual minimization, BRM


General 的 idea 是用一堆 basis functions 來做 approximator
（我覺得這是 parametric 的方法，在開始看到資料之前，
我們有假設了 basis，這代表我們假設了 data distribution 的 shape）

.. math::

    \hat{Q}(s, a) = \sum_i^d \vec{\phi}^T(s, a) \vec{\theta}

Where :math:`\vec{\phi}(s, a) = [\phi_1(s, a), \dots, \phi_d(s, a)]^T`

就是一堆 basis function。

想像這些 basis function 有 d 個，也稱為 feature。

:math:`\vec{\theta}` 是 d 維度的 parameter vector。
即 linear basis model 中的 :math:`\vec{w}`。



Weighted Euclidean Norm
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

給定 :math:`\rho` 是 weight function

.. math::

    \rho: S \times A \rightarrow [0, 1]

Norm of Q function defined as:

.. math::

    \| Q \|^2_\rho = \sum_i \sum_j \rho(s_i, a_j) | Q(s_i, a_j) | ^2

雖然上面有平方，不過比較常用。


Projected Policy Iteration
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

我們想要找一個 :math:`\hat{Q}` ，這個 :math:`\hat{Q}` 要近似於
自己的 backup version :math:`B^\pi_Q(\hat{Q})`

會導入一個 :math:`\Pi`
這個 :math:`\Pi` 就是 mapping function space 到另一個 function space，
用 basis function 就可以做出 mapping
（就如同 vector space 用 basis vectors 做 vector space 的轉換）

.. math::

    \Pi: \mathscr{Q} \rightarrow \mathscr{\hat{Q}}


Projection

.. math::

    \hat{Q} \approx \Pi(B^\pi_Q(\hat{Q}))

解上面整個 :math:`\approx` 的方程式，就是做最佳化:

.. math::

    min_{\hat{Q} \in \mathscr{\hat{Q}}} \|\| \hat{Q} - \Pi(B^\pi_Q(\hat{Q})) \|\|

這裡的 norm 就是用上面 Euclidean norm 來定義。

如果我們是要解這個 projection function :math:`\Pi`

.. math::

    \vec{\phi} \vec{\theta} = \Pi((B^\pi_Q(\vec{\phi} \vec{\theta}))
