Overview
===============================================================================

我們關心 agent 跟環境的互動。
在 OR 領域， LR 被稱為 *approximate dynamic programming* 。
在 ML 才是 LR。 在 economic 用於對 有限理性(bounded rationality) 的研究。

在 ML 中，許多技術採用 Markov decision process (MDP), 這與 dynamic programming
的技術有關。


Reinforcement Learning and Markov Decision Processes
----------------------------------------------------------------------

#. 介於 supervised learning 與 unsupervised learning

#. 處理 sequential decision making problem

#. environment 用來控制 system state ，其通常被表示成 actions + states 的集合。

#. "sequential decision making can be viewed as instances of MDPs."

#. `policy` a function maps state into actions.

#. 各種對 decision making problem 的解法
   * rule base -- 全部 programming 出來，窮舉

   * search and planning

   * probabilistic planning algorithms

   * learning

#. Online -- 拿個實際的環境來操作

#. Offline -- 使用 *simulator*


Credit Assignment
----------------------------------------------------------------------

我的機器做了個決定，但是這個決定對後面影響大；
整個 training 過程可能要到結束你才會知道 credit 。
可能前面的決定 contribute 比較多。
我能不能先給 credit ?

*temporal credit assignment* problem

*structural credit assignment* problem (?)
agent 的 policy 可以用 任意 function 表示時， e.g. NN 的 params
這個時候 如何 update NN 的參數便是 structural credit assignment problem


Exploration-Exploitation Trade-off
----------------------------------------------------------------------

Exploration 為了找到新招

Exploitation 有招之後的優化


Performance
----------------------------------------------------------------------


- RL 的 performance measurement 是 stochastic, policy 一直 update

  *concept drift*

- supervised/unsupervised learning 的 data prior distribution 你都知道。

- 注意 subgoals


Markov Decision Process
----------------------------------------------------------------------

- 可以被視為 stochastic extension of finite automata

- 雖然廣義上的 MDP 是 infinit

- key componement

    - states

    - actions

    - transitions

    - reward function


States
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A finite set :math:`S = \{s^1, \dots, s^N\}`

The size of set space is :math:`N`. :math:`\| S \| = N`

use `features` to describe a `state`


Actions
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A finite set :math:`A = \{a^1, \dots, a^K\}`

:math:`\| A \| = K`

Actions can control the system states.

一坨 action 對某個 state 操作: :math:`A(s)`

描述 action `order`, 使用 `global clock` :math:`t = 1, 2, \dots`


Transitions
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Apply action :math:`a` in a state :math:`s`, make a transitions
from :math:`s` to new state :math:`s'`

Transition function :math:`T` define as
:math:`S \times A \times S \rightarrow [0, 1]`

Notation: 現在是 :math:`s`, apply :math:`a` action, 得到 :math:`s'`

.. math::

    T(s, a, s')

:math:`T` 形成機率分佈, `probability distribution over possible next states`

(如果是離散的也可以想成是一張表)

.. math::

    \sum_{s' \in S} T(s, a, s') = 1


Reward Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

在某個 state 上，我有多少 reward

.. math::

    R: S \rightarrow \mathbb{R}

通常有 :math:`\gamma \in [0, 1]` 作為 discount factor,
離某 :math:`s` 越遠的 reward discount 越多。


Initial State distribution
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Initial state 落在哪裡的表

.. math::

    I: S \rightarrow [0, 1]


Model
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

即 :math:`T` 跟 :math:`R`


Task
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- finite, fixed horizon task

- infinite horizon task

- continuous task


Policy
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- deterministic policy: 就直接的 mapping

.. math::

    \pi: S \rightarrow A

- stochastic policy: 給 :math:`s,\ a` output 機率

.. math::

    \pi: S \times A \rightarrow [0, 1]


在整個 process 中，如果 policy function 都沒變動，那麼就是 stationary


Optimality
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

agent 的目的是啥、想要啥形狀的 reward，average 平穩的 or ？
通常是獲得儘可能多的 rewards, 且夠有效率。

optimality 是 整個 process reward 的期望值, reward 的算法可以直接 sum,
導入 discount, 或是採用 一個 process 的 average rewards.

Finite horizon: 我希望在 h 步之內(即 finite horizon) 有最大的 rewards.
`h-step optimal action`

.. math::

    E[ \sum_{t=0}^h r_t ]

導入 discount 的 finite horizon:

.. math::

    E[ \sum_{t=0}^h \gamma^t r_t ]

Sepcial case of discount finite horizon model: Immediate reward

.. math::

    \text{Let}\ \gamma = 0

    E[r_t]


導入 discount 的 infinite horizon:

.. math::

    E[ \sum_{t=0}^\infty \gamma^t r_t ]


Value Function
----------------------------------------------------------------------

link `optimality` and `policy`.

algo learning target:

* value function, aka criti-based algorithms

    * Q-Learning

    * TD-Learning

* actor-based algorithms

當我的 agent 停在某個 state 時，多好？ (`how good` in certain state)

`多好` 這件事情用 optimality criterion 表達， e.g. average rewords
    "The notion of how good is expressed in terms of an optimality criterion,
    i.e. in terms of the expected return."

所以 :math:`\pi` 是 hyper parameter? 要先給定
    "Value functions are defined for particular policies."

input 是 :math:`s` ， :math:`\pi` 是已知
    "value of a state :math:`s` under policy :math:`\pi`"

.. math::

    V^\pi(s)

e.g. 假設 optimality 是 finite-horizon, discounted model,
given policy :math:`\pi`, 且正在 state :math:`s`

.. math::

    V^\pi(s) = E_{\pi}[ \sum_{k=0}^h \gamma^k r_{t+k} | s_t = s ] \tag{v.1}

看到 :math:`r_{t+k}` 代表前面已經過了 :math:`t` ，前面就不管了。
我們只關心往後的 :math:`k` 步


`state-action value function` :math:`Q: S \times A \rightarrow \mathbb{R}`

從 state :math:`s`, 根據 :math:`\pi` 採取 :math:`a`

.. math::

    Q^\pi(s, a) = E_{\pi}[ \sum_{k=0}^h \gamma^k r_{t+k} | s_t = s, a_t = a ]


Bellman Equation
----------------------------------------------------------------------

Aka. Dynamic Programming Equation

用在 discrete-time 的問題

e.g. 對 :math:`(v.1)` 的 sum 展開，再寫成 Bellman Equation

.. math::

    \begin{align}
        V^\pi(s) & = E_\pi[ r_t + \gamma r_{t+1} + \gamma^2 r_{t+2} + \dots | s_t = t] \\
                 & = E_\pi[ r_t + \gamma V^\pi(s_{t+1}) | s_t = s] \\
                 & = \sum_{s'} T(s, \pi(s), s') \bigg( R(s, a, s') + \gamma V^\pi (s') \bigg)
    \end{align}

Expectation 就是乘上 transition probabilistic 後 sum 起來。
觀察：這個 Expectation 被定義成 Immediate reward + value of next step

:optimal :math:`\pi`: :math:`\pi^*`

:optimal :math:`V`: :math:`V^{\pi^*} = V^*`

`Bellman optimality equation`

.. math::

    V^*(x) = \max_{a \in A} \sum_{s' \in S}
             T(s, \pi(s), s') \bigg( R(s, a, s') + \gamma V^\pi (s') \bigg)

.. math::

    \pi^*(s) = \arg \max_a \sum_{s' \in S}
             T(s, \pi(s), s') \bigg( R(s, a, s') + \gamma V^\pi (s') \bigg)

上面這個 policy 是 `greedy policy` 、是 deterministic。
直接用 value function 去選 best action。

想對應的 optimal state-action value function:

.. math::

    Q^*(s, a) = \sum_{s'} T(s, a, s')
                \bigg( R(s, a, s') + \gamma \max_{a'} Q^*(s', a') \bigg)

這裡 state-action 的 policy 是 stochastic policy。
裡面 :math:`\max_{a'} Q^*` 的部分，是要選使 :math:`Q` 最大的 next action。

.. math::

    \because \sum_{a' \in A} \pi(s', a') = 1

是 stochastic 的形狀。

Model-based and Model-free
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Model 是指 model of MDP，而 MDP 裡面的參數有 :math:`(S, A, T, R)` ，
而 :math:`T` 跟 :math:`R` 是構成 environment 的主要參數。

:Model-based algorithms:
    "Model-based algorithms exist under the general name of DP."
    「一般來說，以 DP 之名」
    可能有些 prior ，用 agent 去蒐集 env 的 data，得到 model。
    基本上在有 model 後會用 DP，去最佳化 Bellman Equation，
    得到 optimal policy。

:Model-free algorithms:
    "Model-free algorithms, under the general name of RL"
    我們沒有完整的 model （如： :math:`T,\ R` ），就會直接丟 agent 下去
    用 policy 戳環境，看看 :math:`T,\ R` 跑出啥。

        "a simulation of the policy thereby generating samples of state transitions and
        rewards."

    然後我們就可以估測 state-action function (e.g. Q-function)


Q function 是 model-free approach。
`T` 跟 `R` 是環境，而我們可能根本不知道這個環境的 model，
若不需要 `T` 跟 `R` 的 method 稱為 model-free algorithms。
    "Q-functions are useful because they make the weighted summation over different
    alternatives (such as in Equation v.1) using the transition function unnecessary.
    This is the reason that in model-free approaches, i.e. in case T and R are
    unknown, Q-functions are learned instead of V-functions."

如果有 `T` 跟 `R` ，在 MDP framework 之下，可以直接算出最好的 policy，
而不用丟出 agent 去嘗試。


Relation between :math:`Q^*` and :math:`V^*`
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    V^*(s) = \max_a Q^*(s, a)

.. math::

    Q^*(s, a) = \sum_{s'} T(s, a, s')
                \bigg( R(s, a, s') + \gamma V^*(s') \bigg)

.. math::

    \pi^*(s) = \arg \max_a Q^*(s, a)


Generalized Policy Iteration (GPI)
----------------------------------------------------------------------

Two steps:

* `policy evaluation`: 根據目前的 :math:`\pi` 得出 :math:`V^\pi`

* `policy improvement`:
  在這個階段，我們已經蒐集了各種 state 跟 action 的結果。
  去看看目前 :math:`\pi` 在每個 states 給出的 action 如何？
  可能在某個 state 之下， :math:`\pi` 給出的 action 有改進的空間。

  用 :math:`V^\pi` 來 improve :math:`\pi` 得到 :math:`\pi'`


我們可以只有 value function 被明確定義，
policy 可以根據每個 state 需要時再生出來。
這種 case 對 model-free 很常見(?)；反之亦然。

    "Note that it is also possible to have an `implicit` representation of the policy,
    which means that only the value function is stored, and a policy is computed
    on-the-fly for each state based on the value function when needed."

另外 value function 不需要特別精確，只需要能夠有鑑別度，
能明確的分出最好跟次好是有差的。

Reference
----------------------------------------------------------------------

* https://en.wikipedia.org/wiki/Reinforcement_learning

* https://www.quora.com/What-is-the-difference-between-model-based-and-model-free-reinforcement-learning
