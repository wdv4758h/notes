Batch Reinforce Learning
===============================================================================


Pure Batch RL
----------------------------------------------------------------------

Three phase

#. 在探索階段，蒐集 experience

    - purely random action

    - 視為 agent 不跟環境互動

    - experience set :math:`\mathcal F = \{(s, a, r', s') \dots\}`
      一堆 experience

#. Learning stage

    - experience set 的大小固定，且導入 prior

    - 根據 experience set 得出 optimal policy


#. Application


問題

    用 purely random (uniformed policy) 的效果不好，
    容易忽略掉 `重要` 的 state，如，在 goal state 附近的 states。


Growing Batch RL
----------------------------------------------------------------------

Modern batch RL 會在 pure batch 跟 pure online 之間找平衡點。


Foundations of Batch RL Algorithms
----------------------------------------------------------------------

原先的 Q-Learning 遇到的問題是，
Q 在小的 learning system，小的問題底下適用，
但是 Q 的 Q table 是 discrete，遇到較大的 state space 或是連續的 state space
無法應用。

大致上來說，遇到的瓶頸有三種：

- exploration overhead

- stochastic approximation 沒效率

- function approximation 不好收斂


Experience Replay
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

在原本 pure online 的 Q-Learning，會在 current optimal action
跟 exploration 之間選擇，像是 ϵ-greedy。
然後在觀測到下一個 state 之後，Q table 就馬上更新，這樣是 greedy 的，
得到的是 greedy policy。
往後的演算法中就忘了 transition tuple :math:`(s, a, r, s')`
（只看 update 後的 :math:`Q'(s, a)` table）。這是 "local" update

`experience replay` 的提出就是為了解決 `exploration overhead`.

這個 experience replay 的技術，雖然簡單，但被視為第一個用來解決 growing batch
problem 的技術。目的是為了加速收斂。

可以對於 experience，我們留多留少都可以，反正就設定個數字，
然後在跟系統的每一個互動後，我們有 n 跟 experience，那麼就 apply update rule
n 次（iter 過每個 experience）
這樣有 back-propagate 的意義在。


Stability Issues
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Idea of `Fitting`

Online RL 用 `asynchronous` updates，而且我們只更新我們目前的 state，
其他以前看過的 state 都不會動到。

Q table 是個 discrete case，我們 update 了某個 state-action pair，
而其他的都不會動到。

Idea of `Fitting` 是用 function approximation

.. math::

    f'(s, a) & = f(s, a) + \alpha(r + \max_{a' \in A} f(a', s') - f(s, a)) \\
             & = f(s, a) + \alpha(\bar{q}_{s, a} - f(s, a))

但是這個的收斂條件建立在特定的 update structure，e.g reward 的形式...etc。
這個吃工程上的經驗。

Fitting 的做法則是對 update rule 做改變。

Stable Function Approximation in Dynamic Programming
****************************************************

有些 function approximator 適合 TD methods 有些不適合，
這篇用 K-nearest-nieghbor, linear interpolation(?),
跟一些 local weight averaging 來做 approximation。
而且是有條件才收斂。

Algo:

#. 先抽 a set of :math:`s \in S` (state space)，先稱這個 set 為 :math:`A`.
   這些 :math:`s` 要具有代表性，能夠涵蓋整個 distribution。
   sampling 的原因是 state space 太大，要降低問題的難度。
   這些 sampling 出來的點稱為 `supports`.

#. Initial guess 的 value function :math:`V_0`

#. :math:`M_A` 是 learning algorithm，使用了 training set :math:`A`
   然後 :math:`f(A)` 是這個 training set 的 labels。

   .. math::

       M_A(f(A), A) \rightarrow \hat{f}

   :math:`M_A` 吃了 label 跟 training data 得到了一個 function approximator
   (e.g. a neural nets) :math:`\hat{f}`

#. 收斂的過程，上標是 iteration：

   .. math::

       V^0 & \\
       V^1 & \leftarrow M_A(V^0, A^0) & \\
       A^1 & \leftarrow T_A(V^1)      & \text{ (sampling)} \\
       V^2 & \leftarrow M_A(V^1, A^1) & \\
       \dots


Replace Inefficient Stochastic Approximation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

接下來就是用了前面 fitting 的想法，
發展出了 `model-free-sample-based`

Ormoneit (2002) 建議不要用 random sampling 出來的 `supports` 來算
:math:`\hat{f}` ，
而用 sampled transition + kernel-based approximator 來求 :math:`\hat{f}`

簡單來說就是，我們只用 已觀測到的 transition samples
(a set of state-action pair)，
(given current state)然後用附近的 transition 求近似的 value，
e.g. 對附近的 transition 的 value 做 averaging (or kernel-based averaging)

這個做法可以想象成 Ormoneit 透過 averaging，估測了 transition model，
this implies from random sampling to the true distribution.


Batch RL Algorithms
----------------------------------------------------------------------

Ormoneit 提出了 kernel-based framework。

`kernel-based approximate dynamic programming` (KADP)

內含：

* experience replay

* fitting

* kernel-based self-approximation (sample-based)


Kernel-Based Approximate Dynamic Programming
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

去解 Bellman equation 的近似 function。

.. math::

    V = HV

變成

.. math::

    \hat{V} = \hat{H} \hat{V}

這裡的 :math:`H` 就是 DP-operator

Iteration process, where :math:`\hat{V}^0` is the initial guess:

.. math::

    \hat{V}^{i+1} & = \hat{H} \hat{V}^i \\
    \text{where } \hat{H} & = H_{max} \hat{H}^a_{dp} \\
    \therefore
    \hat{V}^{i+1} & = H_{max} \hat{H}^a_{dp} \hat{V}^i \\

with a given exp set

.. math::

    \mathscr{F} = \{(s_t, a_t, r_{t+1}, s_{t+1}) | t = 1 \dots p\}

先看方程式的後半 :math:`\hat{H}^a_{dp} \hat{V}^i` 的部分。

.. math::

    \hat{H}^a_{dp} \hat{V}^i & =
        \sum_{(s,a,r,s') \in \mathscr{F}_a} k(s, \sigma) \big(r + \gamma \hat{V}^i(s') \big) \\
    \implies \hat{Q}_a^{i+1}(\sigma) & =
        \sum_{(s,a,r,s') \in \mathscr{F}_a} k(s, \sigma)
        \big(r + \gamma \max_{a' \in A} \hat{Q}^i(s', a') \big) \\

這裡的 :math:`\mathscr{F}_a` 是 given :math:`a` 之後的 set。
同理 :math:`\hat{Q}_a^{i+1}` 是 given :math:`a` 。

然後把 Bellman equation 前半部的 max operator 合起來

.. math::

    \hat{V}^{i+1}(s) & = H_{max} \hat{Q}^{i+1}_a (s) \\
        & = \max_{a \in A} \hat{Q}^{i+1}_a (s)

那麼 policy 和之前一樣就是做 `argmax`

.. math::

    \pi(s) = \arg \max_{a \in A} \hat{V}^{i+1} (s)

這裡就會把 policy update rule 寫成

.. math::

    \pi^{i+1}(\sigma)
    & = \arg \max_{a \in A} \hat{V}^{i+1}(\sigma)
    \\
    & = \arg \max_{a \in A}
        \sum_{(s,a,r,s') \in \mathscr{F}_a} k(s, \sigma)
        \big(r + \gamma \max_{a' \in A} \hat{Q}^i(s', a') \big)

Constrain from kernel:

.. math::

    \sum_{\mathscr{F}_a} k(s, \sigma) = 1, \ \forall \sigma \in S


Kernel-Based Reinforcement Learning
**************************************************

- Ormoneit (2002)

在 continuous state-space 的 TD 用了 parametric function approximator
(e.g neural nets, linear regression) 很難收斂。
本篇提出的方法是對 Bellman equation 做近似，無論怎樣的 initialization value。
本篇發現 bias 對 reinforcement learning algorithm 的影響很大，
e.g 比 bias 在 regression problem 之中的影響還大。


Bias-variance tradeoff

    - bias: underfitting

    - variance: overfitting


- discounted-cost problem：本篇討論的

- average-cost problem：Ormoneit & Glynn (2002)


Kernel-based averaging (inspired by idea of local averaging).

MDP setting
    - discrete time steps :math:`t = 1, 2, \dots T`


Fitted Q Iteration
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Ernst (2005) Tree-Based Batch Mode Reinforcement Learning

Q-learning of batch RL

Algo:

#. Initialization:

   給定 Fixed experience set
   :math:`\mathscr{F} = \{(s_t, a_t, r, s_{t+1}) | t = 1, \dot, p\}`
   這個 set 裡面有 :math:`p` 個 transition tuple :math:`(s, a, r, s')`

   Initial Q value: :math:`q^{-0} = 0`

   Initial Q function

   .. math::

       \hat{Q}^0 (s, a) = 0,\ \forall (s, a) \in S \times A

   這個 :math:`\hat{Q}(s, a)` 即 :math:`Q(s, a)` 的 approximation

#. Iteration 過整個 :math:`\mathscr{F}`
   得出 training patter set :math:`P^{i+1}`:

   .. pseudo-code::

       \state $P^{i+1} \leftarrow \{\}$
       \forall{$(s, a, r, s') \in$ ℱ}
           \state $q_{s,a}^{-i+1} = r + \gamma \max_{a' \in A} \hat{Q}^{i}(s', a')$
           \state $P^{i+1} \leftarrow P^{i+1} \cup {(s,a,q_{s,a}^{-i+1})}$
       \endfor


#. 對 pattern set :math:`P^{i+1}` supervise learning 得出 :math:`\hat{Q}^{i+1}`

   .. math::

       \hat{Q}^{i+1} (s, a) = M(P^{i+1})

   where :math:`M` is the learning algorithm.

#. Derive policy function

   .. math::

       \pi^{i+1}(s) = \arg \max_{a \in A} \hat{Q}^{i+1}(s, a)


原始 paper 中使用 randomized tree。
如果導入的 kernel-based 的方式，
最後一部分估測 :math:`\hat{Q}^{i+1}` 的部分就直接變成：

.. math::

    \hat{Q}^{i+1}_a (\sigma) = \sum_{(s,a,q_{s,a}^{-i+1})} k(s, \sigma) q_{s,a}^{-i+1}

KADP 跟 FQI 的關係就是透過這樣連起來的。

注意這個方法中的是對每個 discrete action :math:`a \in A`
都算出一個 :math:`\hat{Q}_a^{i+1}(s)` ，是對每個 action 獨立的 approximation。
然後概念上是可以合併出 :math:`\hat{Q}^{i+1}(s,a)` ，
實作上就是對 action 做 table 即可。
然後 Ernst 有提出 continuous action space 的版本。

對 continuous action space 是 single function approximator。
discrete action space 是一堆 function approximator。


Least-Squares Policy Iteration
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A.k.a. `LSPI`

Lagoudakis and Parr (2003)

？
    LSPI explicitly embeds the task of solving
    control problems into the framework of policy iteration.

Parametric linear approximation
    用 k 個 `pre-defined basis function` ；
    我理解的是用 k 個不調整的 function，這 k 個 function 是 hyper parameter；
    所形成的 set。裡面每個 function 長這樣:

    .. math::

        \phi_i: S \times A

    除了這些 functions，
    外加一個 weight vector :math:`\vec{w} = (w_1, \dots, w_k)^T`

所以 :math:`\hat{Q}` 長這樣

.. math::

    \hat{Q}(s, a; \vec{w}) = \sum_i^k \phi_i (s, a) w_i = \Phi \vec{w}

用在 TD 上面就稱為 LSQ/LSTDQ。
實際上的 learning 就是調 :math:`\vec{w}`


Identifying Batch RL
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

`online`, `offline`, `semi-batch`, `batch`


Theory of Batch RL
----------------------------------------------------------------------

兩個追求的目標

#. Stability: guaranteed converge

#. Solution quality

Gordon 用 `averager` 用在 discounted reward 上，
`self-weighted` 在 non-discounted reward


Batch RL in Practice
----------------------------------------------------------------------


Neural Fitted Q Iteration (NFQ)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Riedmiller (2005)


.. .. pseudo-code::
..
..     \require $(s, a, r, s') \in $ ℱ
..     \state $Q \leftarrow$ init network
..     \loop
..         \state test
..     \endloop

導入的額外的處理：

    #. Scaling input and target

    #. Adding artificial training patterns
        - 理解成 prior

        - so-called `hint-to-goal`

    #. Normalized Q value (Riedmiller 2011): Qmin-heuristic

        - 第二種手法是，平移；所有的 training Q value 減掉其中最小的值。

    #. A smooth immediate cost-function
        - immediate 是指這個 function 就直接看你的 target state

        - immediate cost-function:
          e.g. 在非 target region 的 training pattern 的 cost 都是
          positive cost；target region 直接就是 0。

        - 然後做 smooth


Batch RL in Multi-agent Systems
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Batch methods for cooperative multi-agent，就多 agent 合作。

裡面其中一個 agent 得到的 transition experience 很大程度會受其他 agent 影響。
這意味著 transition 受外部的因子的影響，像是其他人 agent 的 policy。
所以這裡就有對 batch experience 的資訊量做改進，因為以前的 transition tuple
能夠表示的資訊太少。

Decentralized Markov decision process (DEC-(PO)MDP) 這個 framework 用在
多個獨立的 agents，這些 agent 只能拿到 local state 的相關資訊，沒有
global state。這些 agent 的獨立性包含 action and learning。
實際上的 goal 就是找這麼多 agent 的 joint policies。
這裡會用 local state value function :math:`Q_k: S_k \times A_k`
for each :math:`k` ，用於 local action 的選擇。

最簡單的方法就是，各自 train 各自的 :math:`Q_k` 用 NFQ，
但很明顯這樣會 underestimate。

Riedmiller (2008) 有做改進。
inter-agent coordination + FQI。
基本想法就是先假設其他 agent 做的 action 是 optimal
（雖然顯然不是，因為 exploration ），然後只在作出比目前都好的 joint action 時
才 update。這種 coordination 方法受到 noise 的影響很嚴重，
所以在蒐集 transitions experience :math:`(s, a, s')` 的 :math:`s'` 要仔細篩選。

?
    which is why determinism in the DEC-MDP’s state transitions must be assumed
    during the phase of collecting transitions. However, this assumption can be
    dropped when applying the policies learned.


FQI 的 algo 在蒐集 transition 階段要修改成每個 agent 各自有各自的
experience set :math:`\mathscr{F}_k = \{(s_k, a_k, r_k, s'_k), \dots\}`
每個 agents 蒐集 optimistic (因為假設其他人都是 optimal)
local training pattern set :math:`\mathscr{O}_k`


Deep Fitted Q Iteration
----------------------------------------------------------------------

Riedmiller (2010)

A.k.a `DFQ`

:math:`s \in R^n` hight-dimensional state space

先拿 data :math:`\mathscr{F}` learn 出
:math:`\phi: R^n \rightarrow R^m,\ \text{where}\ m \ll n`

然後得出

.. math::

    \mathscr{F}_\phi = \{\phi(s), a, r, \phi(s') | (s, a, r, s') \in \mathscr{F}\}


對於 growing batch RL。
有新的 collection，新的 state，
去更新 feature extraction mapping （這裡是 unsuppervise）

之後就用 target value 去更新 network:

.. math::

    q_{\phi'(s), a} = r + \gamma max_{a' \in A} \hat{Q}^\phi_{a'} (\phi(s))

從原有的 :math:`\phi` 算 target value，成為 :math:`\phi'` 的 :math:`q`

Riedmiller (2010) 在 feature extraction 是用 deep autoencoder
