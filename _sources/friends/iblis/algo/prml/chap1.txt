Introduction
===============================================================================

- pattern recognition 聚焦在 自動 discover rules, regularities of data.


- Common symbol

    - data point :math:`\vec{x}`

    - target vector :math:`\vec{t}`

    - result of ML algo :math:`\vec{y}(\vec{x})`

- `generalization`: 分辨的成功率

- `feature extraction`: data pre-processing.


Regularization
----------------------------------------------------------------------

One of technique to control over-fitting. Simply add a penalty term to
the error function.

.. math::

    E(\vec{w}) = \text{square error} + \text{regularization}


.. math::

    \text{regularization} = \frac{\lambda}{2} \| \vec{w} \|^2

通常會忽略 w_0, w_0 圖上位移的常數。

- 上述做法統計學上叫做 *shrinkage*
- Neuro network 裡叫做 *weight decay*


Probability Theorem
----------------------------------------------------------------------

- random variable is a *function*, e.g `X`, output can be `foo` or `bar`.

- Two rules:

    - sum rule

    - product rule

.. math::

    p(X=foo) -> 0.4;
    p(X=bar) -> 0.6.

    p(foo) + P(bar) = 1.


Joint Probability
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

發生 :math:`X` 且 :math:`Y` 的機率。

:X: a random var, possibile outcome is :math:`\{ a, b, c \}`

:Y: a random var, :math:`\{ foo, bar, baz \}`

:N: total number of trails

:math:`n_{ij}`: the number of :math:`X_i` + # of :math:`Y_j`

:joint probability:

.. math::

    p(X=x_i, Y=y_j) = \frac{n_{ij}}{N}

e.g.

.. math::

    p(X=x_a, Y=y_{bar}) = \frac{n_{a-bar}}{N}

即出現 `a` ，同時出現 `bar` 之機率。
:math:`X` 與 :math:`Y` 可能是兩個獨立的事件。


:marginal probability: or says *sum rule*

.. math::

    p(X=x_i) = \sum_j p(X=x_i, Y=y_j)


Condiction Probability
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Given :math:`X = x_i`

.. math::

    p(Y=y_j|X=x_i) = \frac{n_{ij}}{n_i}


Product Rule
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    p(X=x_i, Y=y_j) & = p(Y=y_j|X=x_i) p(X=x_i) \\
                    & = p(X=x_i|Y=y_j) p(Y=y_j)


Bayes' Theorem
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

兩個 joint probability 相等的結論。

.. math::

    p(Y|X) = \frac{p(X|Y)p(Y)}{p(X)}

- 分母已知而且是 const, 可以視為一個 normalization term 。
  讓所有 :math:`p(y_i|X)` 符合機率公設。


.. math::

    \because
    p(X, Y) & = p(Y, X)
    \\
    p(Y|X)p(X) & = p(X|Y)p(Y)
    \\
    \therefore
    p(Y|X) & = \frac{p(X|Y)p(Y)}{p(X)}


Example
**************************************************

有個實驗有兩個參數 :math:`X \& Y` （或想象成兩個步驟）。
假設給定 :math:`x_i` 是實驗中的已知（想象成 :math:`X` 會比較早拿到）。
我們關心 :math:`Y` 的結果。

:prior probability: 事前機率。
    在還沒實驗之前，我們還沒有拿到任何已知( :math:`x_i` )時，
    我們所關心的那個 :math:`Y` 的機率。

.. math::

    p(Y)

:posterior probability: 事後機率。
    在實驗中我們觀察到了 :math:`x_i`

.. math::

    p(Y|x_i)


Likelihood
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    Likelihood = p(x_i|y_j)

:math:`x_i` 為已知的。
這個 Likelihood function 的值越大，我們會認為「在 :math:`y_j` 的條件下，
觀察到 :math:`x_i` 是很合理的」

e.g.

.. math::

    Likelihood = p(我沒中樂透|樂透中獎率=10^{-8}) -> 極大

所以 「我沒中樂透」 這個觀測結果很合理。


Probability Density
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

如果我們的 outcome 從原本離散的事件變成 連續的實數。
則 :math:`p(x \in (a, b))` 之間 是面積。

.. math::

    p(x \in (a, b)) = \int_a^b p(x) dx


Cummulative Distribution Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    P(z) = \int_{-\infty}^z p(x) dx


Condictional Expectation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    E[f|y] = \sum_x p(x|y)f(x)


Variance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


.. math::

    var[x] = E[x^2] - E[x]^2


Covariance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    cov[x, y] = E_{x, y}[xy] - E[x]E[y]

Matrix version:

.. math::

    cov[X, Y] = E_{X, Y}[XY^T] - E[X]E[Y^T]


Bayesian Probability
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Aka, Subjective Probability.

當一個事件的機率不能用 觀察頻率 而得到時，我們會選擇用 Bayesian probability
來解釋。 e.g. 某人被雷打中的機率，這個機率顯然不能透過觀測頻率而得到。

:Curve fitting problem:
    我們有多項式參數 :math:`\vec{w}` 跟一些已知的 data point
    :math:`D = \{t_1, t_2, \dots, t_n \}` 。
    在這個 curve fitting 的問題中，我們關心的是 :math:`\vec{w}`

:posterior probability:
    在我們觀察到 :math:`D` 之後所得。

    一個 隨機事件 (Event) 的 posterior probability 是給出相關證據後的條件機率。

.. math::

    p(\vec{w}|D) = \frac{p(D|\vec{w})p(w)}{p(D)}

其中，上述 right-hand side 的 :math:`p(D|\vec{w})` 被稱為
`likelihood function` ，這個 function 的 parameter 為 :math:`\vec{w}` 。
其表達了 :math:`D` 對於不同 :math:`\vec{w}` 的合理程度（原文用： probable）。

我們可以得到

.. math::

    \text{posterior} \propto \text{likelihood} \times \text{prior}

:maximum likelihood:
    最大化 likelihood function 的函數值

:error function:
    通常是將 likelihood function 的函數值取負號作為 error function。
    而為了計算上方便，會先取 log 在負號。

    為何取 log ? 在計算 :math:`p(D|\vec{w})` 時，其中 D 是多次的實驗結果
    :math:`\{t_1, \dots. t_n\}` 。

    .. math::

        p(D|\vec{w}) = \frac{p(D=t_1) p(D=t_2) \dots p(D=t_n)}{p(\vec{w})}

    取 log 會使得分子的連乘改為連加，且意義不變。

:hyperparamter: :math:`\vec{w}` 是 model, 而決定 model 的 parameter 稱為
                hyperparamter.

    .. math::

        p(\vec{w}|\alpha)
        \text{, where } \alpha \text{ is the precision of the distribution.}

:predictive distribution:
    我們透過 maximum likelihood 找到了 :math:`\vec{w_{ML}}` ，
    再得到 :math:`\beta_{ML}` 後，我們建立了 probabilistic model ，可以在給定
    一個 :math:`x` 來做預測。

    .. math::

        p(t|x, \vec{w_{ML}}, \beta_{ML}) =
            \mathcal{N}(t|y(x, \vec{w_{ML}}), \beta_{ML}^{-1})


Data Sets Bootstrap
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Original data set:
    :math:`X = \{ x_1, \dots, x_N \}`

:New data set:
    :math:`X_B` 透過 random sampling with replacement。
    e.g.: 箱子中 10 顆骰子，抽出 original data set 的其中 3 個，再放回，
    抽到 10 個為止，即形成 :math:`X_B`


Decision Theory
----------------------------------------------------------------------

Make optimal decisions in situations involving uncertainty
(with probability theorem)

:input value: :math:`\vec{x}`

:target value: :math:`\vec{t}`

:joint probability distribution:
    :math:`p(\vec{x}, \vec{t})` 是對於這兩個變數 summary of the uncertainty.

:inference:
    Determine the *joint probability distribution*
    ( :math:`p(\vec{x}, \vec{t})` ) from training data set.


Information Theory
----------------------------------------------------------------------

資訊量怎麼計算？

假設我們有個 discrete random variable :math:`x` , 代表資訊.

資訊量被視為不一樣的程度，觀測 :math:`x` 若長得很不一樣，
就是有新的資訊，資訊量高，反之亦然。

假設有 probability distribution :math:`p(x)`
代表資訊的分佈（資訊出現頻率各有高低）,
我們想要尋找一個 `Monotonic function`_ :math:`h(x)` 來代表觀測 x 後，有多少的
information gain ，或是說有多 suprise

先想象，假設 :math:`x, y` 為獨立的 random variable, :math:`h(x, y)` 應該長成:

.. math::

    h(x, y) = h(x) + h(y)

而根據獨立的這個假設，知道:

.. math::

    p(x, y) = p(x)p(y)


從上面的關係我們可以定出:

.. math::

    h(x) = - \log_2 p(x)

而且 :math:`h(x) >= 0` 。

對於所有可能的 :math:`x` , 他們的平均資訊量用 期望值表示:

.. math::

    H(x) & = \sum_x p(x) h(x) \\
         & = - \sum_x p(x) \log_2 p(x)

此為 :math:`entropy` 的定義。


.. _Monotonic function: https://en.wikipedia.org/wiki/Monotonic_function


Continueous Var
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

將 :math:`entropy` 推廣到 Continueous variable 上得：

.. math::

    H(\vec{x}) = - \int p(\vec{x}) \ln p(\vec{x}) d\vec{x}

上式稱為 :math:`differential entropy`
