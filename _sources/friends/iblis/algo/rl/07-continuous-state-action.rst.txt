Reinforcement Learning of Continuous State and Action Spaces
===============================================================================

本章主要介紹
    - 直接 update value function `representation` 的方法

    - 直接 update policy function `representation` 的方法

對於 function representation 的選擇有各種考量，然後選好 representation 後
還有 update (optimization) 的方法 -- gradient-based and gradient-free method。

    - gradient-based TD learning

    - evolutionary

    - policy-gradient

    - actor-critic


Intro.
----------------------------------------------------------------------

Problem setting: sequential decision making in
    - continuous domain
    - delayed reward


MDP in Continuous Spaces
----------------------------------------------------------------------

假設我們的 state space :math:`S` 是 infinitely large

Transition probability 的 PDF，就是對 :math:`s'` 積分

.. math::

    \int T(s, a, s') d s' = P(s' | s, a)

也有另一種 form：

.. math::

    s' = T(s, a) + \omega_T(s, a)

這裡的 :math:`T` 訂成一個 deterministic function
:math:`T: S \times A \rightarrow S`,
:math:`\omega_T` 是個 zero-mean 的 noise vector。
上面這種新式的物理意義是，
我可以從「以 :math:`T(s, a)` 為中心的 Gaussian」 sample 出 :math:`s'`
然後我的 reward function 也可以加上 noise：

.. math::

    r' = R(s, a, s') + \omega_R(s, a, s')

上面 :math:`T` 跟 :math:`R` 帶著 :math:`\omega_T` 、 :math:`\omega_R` 的形式，
是 general form；如果 :math:`\omega` 在所有的 timestamps 中都是 0。
那麼整個 MDP 就是 deterministic，反之為 stochastic。

如果 :math:`T` 跟 :math:`R` 有 time-dependent，要導入 t 做考慮，
那麼這個 MDP 是 non-stationary。

Case I: action space 是離散的
    只有 state space 是 continuous。
    Policy :math:`\pi: S \times A \rightarrow [0, 1]` 長這樣：

    .. math::

        \pi(s, a) & = P(a | s) \\
        \sum_{a \in A} \pi(s, a) & = 1

Case II: action space 是 continuous
    用 :math:`\pi(s)` 的 PDF，從 :math:`\pi(s, a)` 對 action 積分，
    積出來的 function 就是在 action space 上的 PDF。

Value function 的目的是 predict `future discounted reward` 。
而 optimality 就是 最大化 reward。

:math:`B^\pi` 是 Dynamic Programming Operator，
given :math:`\pi` 後 :math:`B^\pi: \mathscr{V} -> \mathscr{V}`
where :math:`\mathscr{V}` is the space of value function。
這個 operator 吃一個舊的 value function 會吐出新的 value function。

.. math::

    (B^{\pi_i} V)(s) & = \int_A \pi(s, a)
        \Big( \int_S T(s, a, s') (R(s, a, s') + \gamma V(s')) ds' \Big) da \\
    \therefore \lim_{i \to \infty} (B^{\pi_i}V)(s) & = \\
    (B^* V)(s) & = \max_a \int_S T(s, a, s') (R(s, a, s') + \gamma V(s')) ds'


用 Q function 的話

.. math::

    Q^*(s, a) = \int_S T(s, a, s') (R(s, a, s') + \gamma \max_{a'} Q^*(s', a')) ds'


Methodologies to Solve a Continuous MDP
----------------------------------------------------------------------

Model Approximation

    去 approximate MDP model，然後拿估測出來的 approximation 算 :math:`\pi`.
    主要是估測 :math:`T`, :math:`R`, 因為 :math:`S, A, \gamma` 姑且都知道，
    或觀測得到。
    因為 Markov property 的假設，這些 function 只 depend on local data，
    算是在 sequence 上作出 iid 的效果。
    然後 model 的估測就變成 supervise learning problem。

    最經典的兩個方法 *value iteration* 跟 *policy interation*
    是拿 approximate model 算 value function。
    Model-based algorithm 對 continuous state MDP 的問題是 generalization，
    各種 state 的可能性，state space 可以無限大，
    難以在 build model 的時候全面的涵蓋。因此 model 的精確程度是備受質疑的。

    只有在 :math:`T(s, a, s')` 的 :math:`s'` 是個夠小的集合的時候，
    model approximation 才是可行的，在往後因 space 的因素，本章不會再討論
    更多 model approximation。

Value Approximation

    這類的方法是直接 approximate :math:`V^*, Q^*`

Policy Approximation

    這裡的 algorithm 直接 使用/update policy function。上面的 Value approximate
    是先有 value function 然後在需要的時候生出 policy。
    `direct policy-search` and `actor only` algorithms。


Function Approximation
----------------------------------------------------------------------

在 value-based RL 中，target data 不想是原本的 supervise learning 確定是答案，
而 RL 的 target value 可能來自於觀測到的 state 等，所以不是所有的
supervise learning 都適用。所以 approximation 的選擇是有條件的。


Linear Function Approximation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Feature extraction function :math:`\phi: S \rightarrow \Phi`
會把 state space map 到 feature space :math:`\Phi`

.. math::

    V_t(s) = \theta^T_t \phi(s)

在給定的假設下，有文獻證明 linear approximation 在 RL 的收斂性。
