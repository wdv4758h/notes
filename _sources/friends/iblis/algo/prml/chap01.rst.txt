Introduction
===============================================================================

- pattern recognition 聚焦在 自動 discover rules, regularities of data.


- Common symbol

    - data point :math:`\vec{x}`

    - target vector :math:`\vec{t}`

    - result of ML algo :math:`\vec{y}(\vec{x})`

- `generalization`: 分辨的成功率

- `feature extraction`: data pre-processing.

- deal with *over-fitting*
    - 用 Regularization term
    - 提高資料量
    - 導入 Bayesian approach


Regularization
----------------------------------------------------------------------

One of technique to control over-fitting. Simply add a penalty term to
the error function.

.. math::

    E(\vec{w}) = \text{square error} + \text{regularization}


.. math::

    \text{regularization} = \frac{\lambda}{2} \| \vec{w} \|^2

通常會忽略 w_0, w_0 圖上位移的常數。

- L2 Norm
- 上述做法統計學上叫做 *shrinkage*
- Neuro network 裡叫做 *weight decay*


Probability Theorem
----------------------------------------------------------------------

- random variable is a *function*, e.g `X`, output can be `foo` or `bar`.

- Two rules:

    - sum rule: 即 :ref:`prob-total-prob`

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

or

.. math::

    P(X \cap Y)

e.g.

.. math::

    p(X=x_a, Y=y_{bar}) = \frac{n_{a-bar}}{N}

即出現 `a` ，同時出現 `bar` 之機率。
:math:`X` 與 :math:`Y` 可能是兩個獨立的事件。


:marginal probability: or says *sum rule*

.. math::

    p(X=x_i) = \sum_j p(X=x_i, Y=y_j)


Condition Probability
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

.. note::

    原本的離散的 :math:`p(x)` 稱為 *probability mass function*


Transformation of Probability Densities
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

運用在微積分上變數代換的技巧。

令 :math:`x = g(y)` 是 :math:`x` 與 :math:`y` 之間的非線性轉換

.. math::

    \begin{align}
        p_y(y) dy & = p_x(x) dx \\
        p_y(y)    & = p_x(x) \frac{dx}{dy} \\
                  & = p_x(x) g'(y) \\
                  & = p_x(g(y)) g'(y)
    \end{align}

ref: https://www.cl.cam.ac.uk/teaching/2003/Probability/prob11.pdf


Cummulative Distribution Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:math:`p(x)` 拿去積分是 :math:`P(x)` ，換句話說 :math:`P'(x)` 是 :math:`p(x)`

.. math::

    P(z) = \int_{-\infty}^z p(x) dx


Multi-variable
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

推廣到多變量 :math:`\vec{x} = [x_1, x_2, \dots, x_D]` 都是
continueous variable

現在這個叫做 *join probability density function*:

.. math::

    p(\vec{x}) = p(x_1, \dots, x_D)

仍要滿足機率公理:

.. math::

    p(\vec{x}) \ge 0

.. math::

    \int p(\vec{x}) d\vec{x} = 1

Sum Rule and Product Rule:

.. math::

    \begin{align}
        p(x)    & = \int p(x, y) dy \\
        p(x, y) & = p(y|x)p(x)
    \end{align}

證明需透過 *measure theory*


Expectation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

目的是計算 加權平均。

首先我們有 function :math:`f(x)`,
計算 :math:`f(x)` under :math:`p(x)` 的加權平均。

discrete 版本:

.. math::

    \mathbb{E}[f] = \sum_x p(x) f(x)


continueous 版本:

.. math::

    \mathbb{E}[f] = \int p(x) f(x) dx

在 continueous 的 probability density function 取點 N 點做近似。
想象一下，取越多點，原來 :math:`p(x)` 比較高的 :math:`x` 就會比較多:

.. math::

    \mathbb{E}[f] \simeq \frac{1}{N} \sum_{n=1}^N f(x_n)


multi-variable 是用下標代表對哪個變數做加權平均(積分)，
在下面的例子中， :math:`x` 會被積分掉，所以下式實際上積分後是個 y 的 function:

.. math::

    \mathbb{E}_x[f(x, y)]


Conditional Expectation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    \mathbb{E}[f|y] = \sum_x p(x|y)f(x)


Variance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

variance of :math:`f(x)`


.. math::

    var[f] = \mathbb{E}[(f(x) - \mathbb{E}[f(x)])^2]

即 :math:`value - mean` 是差量，差量平方的 mean


Covariance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

有兩 random variables :math:`x, y`

.. math::

    cov[x, y] = \mathbb{E}_{x, y}[xy] - \mathbb{E}[x]E[y]

Matrix version:

.. math::

    cov[X, Y] = \mathbb{E}_{X, Y}[XY^T] - \mathbb{E}[X]E[Y^T]


Bayesian Probability
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Aka, Subjective Probability.

當一個事件的機率不能用 觀察頻率 而得到時，我們會選擇用 Bayesian probability
來解釋。 e.g. 某人被雷打中的機率，這個機率顯然不能透過觀測頻率而得到。

:Curve fitting problem:
    在原本是用 frequentist 的方法。
    而這裡我們希望 model parameter :math:`w` 的 uncertainty

    觀察是從 prior probability 到 posterior probability 的過程。

    我們有多項式參數 :math:`\vec{w}` 跟一些已知的 data point
    :math:`\mathcal{D} = \{t_1, t_2, \dots, t_n \}` 。
    在這個 curve fitting 的問題中，我們關心的是 :math:`\vec{w}`

:posterior probability:
    在我們觀察到 :math:`\mathcal{D}` 之後所得。

    一個 隨機事件 (Event) 的 posterior probability 是給出相關證據後的條件機率。

.. math::

    p(\vec{w}|\mathcal{D}) = \frac{p(\mathcal{D}|\vec{w})p(\vec{w})}{p(\mathcal{D})}

其中，上述 right-hand side 的 :math:`p(\mathcal{D}|\vec{w})` 被稱為
`likelihood function` ，這個 likelihood function 的 hyperparameter 為
:math:`\vec{w}` 。
其表達了 :math:`\mathcal{D}` 對於每一組 :math:`\vec{w}` 的合理程度
（原文用： probable）。

我們可以得到

.. math::

    \text{posterior} \propto \text{likelihood} \times \text{prior}


上式中所有 function 都是 :math:`\vec{w}` 的 function 。
只有分母 :math:`p(\mathcal{D})` 是作為 normalization constant 用的。
分母是為了讓 :math:`p(\vec{w}|\mathcal{D})` sum 起來是 1 。
觀察:

.. math::

    \begin{alignat}{2}
    & & \int p(\vec{w}|\mathcal{D}) d\vec{w} & =
        \int \frac{p(\mathcal{D}|\vec{w}) p(\vec{w})}{p(\mathcal{D})} d\vec{w} \\
    & \Rightarrow & 1 & =
        \int \frac{p(\mathcal{D}|\vec{w}) p(\vec{w})}{p(\mathcal{D})} d\vec{w} \\
    & \Rightarrow & 1 & =
        \frac{1}{p(\mathcal{D})}\int p(\mathcal{D}|\vec{w}) p(\vec{w}) d\vec{w} \\
    & \Rightarrow & p(\mathcal{D}) & =
        \int p(\mathcal{D}|\vec{w}) p(\vec{w}) d\vec{w}
    \end{alignat}

這個分母可以透過 *likelihood function* 對 :math:`\vec{w}` 積分，
:math:`\vec{w}` 會被積分掉，
整個 :math:`p(\mathcal{D})` 中就沒有 :math:`\vec{w}` 。
觀察上式的 :math:`p(\vec{w})` 是個 distribution ，
想象一下有各種的 :math:`\vec{w}` ，
:math:`\vec{w}` 有各種可能性、不確定性 (uncertainty) ；
比起 frequentist 是使用的 fixed parameter
，是透過估算 error 來決定 :math:`\vec{w}` 。


:maximum likelihood:
    frequentist 的技術： 最大化 likelihood function 的函數值

    * ref: https://stats.stackexchange.com/questions/74082/
    * ref: https://stats.stackexchange.com/questions/180420/

    要導入整個 data set 下去得到一個 error function 的 outcome

:error function:
    通常是將 likelihood function 的函數值取負號作為 error function。
    而為了計算上方便，會先取 log 在負號。

    maximizing likelihood 相當於 minimizing error function 。

    為何取 log ?
    在計算 :math:`p(\mathcal{D}|\vec{w})` 時，其中 D 是多次的實驗結果
    :math:`\{t_1, \dots. t_n\}` 。

    .. math::

        p(D|\vec{w}) = \frac{p(D=t_1) p(D=t_2) \dots p(D=t_n)}{p(\vec{w})}

    取 log 會使得分子的連乘改為連加， log function 是 monotonically decreasing
    function, imply convex, 而且 maximum likelihood 的意義不變。

以 Bayesian 的觀點，會把 prior 考慮進來，而不只有 likelihood 。
可以解決 overfitting 的問題。
舉例來說，我們丟了 3 次公正的硬幣，但剛好都是 head，
這時如果只 maximum likelihood 會得到 :math:`p(head) = 1` 這是 overfitting。
而相對的 Bayesian 加上了些 prior，會比單純 maximum likelihood 好。

但是 frequentist 跟 Bayesian 的爭論一直很多。像是 Bayesian 有時候選擇 prior
是為了數學上的方便，而不一定是與事實有關。

:hyperparameter: :math:`\vec{w}` 是 model, 而決定 model 的 parameter 稱為
                hyperparameter.

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

其他 frequentist 的手法

:Original data set:
    :math:`X = \{ x_1, \dots, x_N \}`

:New data set:
    :math:`X_B` 透過 random sampling with replacement。
    e.g.: 箱子中 10 顆骰子，抽出 original data set 的其中 3 個，再放回，
    抽到 10 個為止，即形成 :math:`X_B`


Curve fitting Re-visited
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

再次來看看 curve fitting 問題，前面我們用 polynomial 與 frequentist 的
maximum likelihood 的技術來得到我們的 model。

Probabilistic perspective，我們用
「單一一個 target value 現在是個 distribution」來表達 uncertainty。

舉例來說，現在我們假設，（在給定 :math:`x` 之下） :math:`t` 的值 是一個
gaussian distribution，而且這個 distribution :math:`\mu = y(x, \vec{w})`

我們現在是要做 curve fitting，就是求曲線 :math:`y(x, \vec{w})` ,
所以想象成這曲線上有無限多個 target 就有 無限多個 distribution。

每個 distribution 寫成

.. math::

    p(t | x, \vec{w}, \beta) & = \mathcal{N}(t | \mu, \beta^{-1}) \\
                             & = \mathcal{N}(t | y(x, \vec{w}), \beta^{-1})

Where the precision :math:`\beta^{-1} = \sigma^2`

然後用 training data :math:`\{\vec{x}, \vec{t}\}` maximum likelihood
來決定 :math:`\vec{w},\ \beta` ，
加上 i.i.d 的假設，得 likelihood function

.. math::

    p(\vec{t} | \vec{x}, \vec{w}, \beta) =
        \prod_n^N \mathcal{N} (t_n | y(x_n, \vec{w}), \beta^{-1})

再用 :ref:`gaussian-func` 得出的 log likelihood form

.. math::

    \ln p(\vec{t} | \vec{x}, \vec{w}, \beta) =
        - \frac{\beta}{2} \sum \big( y(x_n, \vec{w}) - t_n \big)^2 +
        \frac{N}{2} \ln \beta - \frac{N}{2} ln (2\pi)

現在我們要 maximum log likelihood with respect with :math:`\vec{w}` ，
上面式子中後面兩項與 :math:`\vec{w}` 無關，省略掉。
而第一項中的 :math:`\beta` 可以視為常數；得

.. math::

    & & \max - & \frac{1}{2} \sum \big( y(x_n, \vec{w}) - t_n \big)^2 \\
    & \Rightarrow & \min & \frac{1}{2} \sum_n^N \big( y(x_n, \vec{w}) - t_n \big)^2

這就是 `sum-of-square error function` 。
`sum-of-square error function` 正是基於 Gaussian noise distribution 的假設，
執行 maximum likelihood 的結果。

同理，求 precision

.. math::

    \frac{1}{\beta} = \frac{1}{N} \sum_n^N \big( y(x_n, \vec{w_{ML}}) - t_n \big)^2

有了 :math:`\vec{w_{ML}},\ \beta_{ML}` ，以下給了 :math:`x`
被稱為 predictive distribution

.. math::

    p(t | x, \vec{w_{ML}}, \beta_{ML}) = \mathcal{N}(t | y(x, \vec{w_{ML}}), \beta_{ML}^{-1})

接下來我們導入 Bayes' theorem 中的 prior，recall this

.. math::

    posterior \propto likelihood \times prior

假設我們的 model :math:`\vec{w}` 的 distribution 是個 D-dimension Gaussian

.. math::

    p(\vec{w} | \alpha)a & = \mathcal{N}(\vec{w} | \vec{0}, \alpha^{-1} I) \\
        & = \Big( \frac{\alpha}{2\pi} \Big)^{\frac{M+1}{2}} e^{-\frac{\alpha}{2} \vec{w}^T \vec{w}}

where :math:`\alpha` is the precision (:math:`\alpha^{-1} = \sigma^2`)

然後我們求 :math:`\vec{w}` 透過 maximum posterior，
取 log posterior，會得到 likelihood 的 exp 與 prior 的 exp 相加。

.. math::

    & & \frac{\beta}{2} \sum_n^N \big( y(x_n, \vec{w}) - t_n \big)^2 +
    \frac{\alpha}{2} \vec{w}^T \vec{w} \\
    & = & \frac{1}{2} \sum_n^N \big( y(x_n, \vec{w}) - t_n \big)^2 +
    \frac{\alpha}{2\beta} \vec{w}^T \vec{w} \\
    & = & \frac{1}{2} \sum_n^N \big( y(x_n, \vec{w}) - t_n \big)^2 +
    \frac{\lambda}{2} \vec{w}^T \vec{w}

這個就是 `sum-of-square error function with regularization term`, given
:math:`\lambda = \frac{\alpha}{\beta}`

導入的 prior 的 maximum posterior 就會得到 regularization term，可以對抗
over-fitting problem。但這個是 Gaussian distribution 的假設之下。


Bayesian curve fitting
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

即使我們導入了 prior distribution :math:`p(\vec{w} | \alpha)` 做了 maximum
posterior，但這些目前都是對 :math:`\vec{w}` 做點估計（定值估計），
還不是 Bayesian 的角度。在 Bayesian 的方法之下，會使用 product rule and
sum rules，也就是會對 :math:`\vec{w}` 積分。
這種積分的手法 (marginalization) 是 Bayesian method 的核心。

現在考慮 predictive distribution 的拆解，裡面有 posterior

.. math::

    p(t | x, \vec{x}, \vec{t}) = p(t | x, \mathcal{D}) =
    \int p(t | x, \vec{w}) p(\vec{w} | \mathcal{D}) d \vec{w}

實際上還有 :math:`\alpha,\ \beta` 是 hyperparameter，省略了沒寫。
上式中 :math:`p(\vec{w} | \mathcal{D})` 為 posterior。

我們之前假設了 posterior 為 Gaussian ，而現在的 predictive distribution
也將會是 Gaussian

.. math::

    p(t | x, \vec{x}, \vec{t}) = \mathcal{N}(t | m(x), s^2(x))

然後 :math:`m(x),\ s^2(x)` 長得很奇怪，我們之後再證明。


Model Selection
----------------------------------------------------------------------

假設 model 為 order :math:`M` ploynomial model

.. math::

    y = p(x)

而 :math:`M` 的覺得也是個 hyperparameter。

:math:`M` 太大就容易有 over-fitting 的問題。


Cross-Validation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

可用於檢驗 over-fitting

舉例，所有的 data point 是 100%， 拆成

- train set

- validation set

- test set

通常先拆成 8:2 = (train + validation):test

而 train + validation 裡面在拆，如 4:1

在 4:1 的 case，這個部分的 data 有 5 段，
就會做 5 個 training run，每次 run 都選一段作為 validation set。

但是這樣的缺點是每個 :math:`M` 的 computation 量都增加 5 倍。


Akaike Information Criterion (AIC)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

我們覺得 cross-validation 的計算量增加太多了。

.. math::

    \ln p(\mathcal{D} | \vec{w}_{ML}) - M

我們有好多個 :math:`M` 要選一個。
每個 :math:`M` 都有自己的 max likelihood 的那個 :math:`\vec{w}` 。


Gaussian Distribution
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

See :ref:`gaussian-func`


Decision Theory
----------------------------------------------------------------------

Make optimal decisions in situations involving uncertainty
(with probability theorem)

:input value: :math:`\vec{x}`

:target value: :math:`\vec{t}`

:joint probability distribution:
    :math:`p(\vec{x}, \vec{t})` 是對於這兩個變數 summary of the uncertainty.

:inference:
    決定 *joint probability distribution* 就是 `inference` 的其中一種實作方法
    ( :math:`p(\vec{x}, \vec{t})` from training data set).
    但這是個很困難的問題。


Minimizing the misclassification rate
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

假設我們現在在做兩個 class :math:`C_1, C_2` 的 classification，
input dataset :math:`X = {\vec{x_1}, \dots, \vec{x_n}}`
每個 data 都是 feature vector :math:`\vec{x_i}`

objective function 就是要 minimizing misclassification rate，
或是其對偶問題 maximizing correct rate

.. math::

    p(mistake) & = p(\vec{x} \in R_1, C_2) + p(\vec{x} \in R_2, C_1) \\
               & = \int_{R_1} p(\vec{x}, C_2) d\vec{x} + \int_{R_2} p(\vec{x}, C_1) d\vec{x}

Where :math:`R_1,\ R_2` 是 decision region，就是我們畫的。

在 minimizing 完之後要做 decision，拿一個 input :math:`\vec{x}`
就直接比較
:math:`p(\vec{x}, C_1)` vs :math:`p(\vec{x}, C_2)`

在比較的時候，可以寫成
:math:`p(C_1|\vec{x})p(\vec{x})` vs :math:`p(C_2|\vec{x})p(\vec{x})`
然後拿掉 :math:`p(\vec{x})` 就就是直接比較 posterior。

在類別很多的時候，會需要列出太多 misclassification。
e.g. 有 4 類，要寫 1 v {2, 3, 4}, 2 vs {3, 4}, 3 vs {4}。
但是換成 maximizing :math:`p(correct)` 則只有 4 項

.. math::

    p(correct) = \sum_{k=1}^4 \int_{R_k} p(\vec{x}, C_k) d\vec{x}

是對偶。


Minimizing the expected loss
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

很多時候我們的 Type I error vs Type II error 有不同的嚴重程度。
所以我們希望有不同的 loss 權重。

e.g. 是 癌症 但是判定成 健康，這個很嚴重；是 健康 判定成 癌症，這還好

.. math::

    E(L) = \sum_k \sum_j \int_{R_j} L_{kj} p(\vec{x}, C_k) d\vec{x}

這是 expected loss。

:math:`L_{kj}` 就是 k 類但判成 j 的 loss，
當然 :math:`k = j` 時 :math:`L_{kj} = 0`

然而實際上給定了一個 input :math:`\vec{x}` 之後，這個 :math:`\vec{x}` 只會坐落
在其中一個 :math:`R_j` ，所以我們只要求

.. math::

    & & \sum_k L_{kj} p(\vec{x}, C_k) \\
    & = & \sum_k L_{kj} p(C_k | \vec{x}) p(\vec{x}) \\
    & \Rightarrow & \sum_j L_{kj} p(C_k | \vec{x})

因為做 minimizing 所以 :math:`p(\vec{x})` 就拿掉了，結果不變。


Inference and decision
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

解決一個 classification 的問題需要兩個 stage:

#. `inference`: 用 training dataset 得出 :math:`p(C_k | \vec{x})` 的 model

#. `decision`: 用剛剛得到的 posterior distribution 去做 testing，選出個 class

解 decision problem 的三大方法，照複雜度排序：

#. 先解 class-conditional densities :math:`p(\vec{x} | C_k)` ，
   class 有 k 個就個別解 k 次。同樣的還要找 prior :math:`p(C_k)` ，
   然後用 Bayes' Theorem 算出所有的 posterior probabilities

   .. math::

       p(C_k | \vec{x}) & = \frac{p(\vec{x} | C_k) p(C_k)}{p(\vec{x})} \\
                        & = \frac{p(\vec{x} | C_k) p(C_k)}{\sum_k p(\vec{x} | C_k) p(C_k)}

   或是直接 model joint distribution :math:`p(x, C_k)` 然後 normalize 後
   就會得到 posterior。

   在找到 posterior probabilities 之後，就把 input :math:`\vec{x}` 丟入所有的
   posterior probabilities 算算誰的值大，決定一下 class。

   這種 model input 跟 output 的 distribution 的方法被稱作 `generative models`，
   因為有 distribution 就可以 sampling 出 synthetic data point。

#. 直接去 model :math:`p(C_k | \vec{x})` ，
   這個 posterior 可能裡面就是用個 approximator。然後我們就可以用 decision stage
   得到答案。這個被稱為 `discriminative models`

#. 直接找一個 function :math:`f(\vec{x})` （被稱為 discriminant function）。
   這個 function 的 output 就直接是 class。整個過程沒有機率。

`generative models` 的優點在於我們會算出 :math:`p(x)` ，我們可以拿著這個
:math:`p(x)` 來看看 new data 是不是 outlier
(`outlier detection and novelty detection`)。

相對的，如果我們只想做 classification，就只需要 posterior，那麼
`discriminative models` 所需要的計算量比較小。

最後，`discriminant function` 是直接用 data 求這個 function，
直接結合 `inference` 跟 `decision` stage 成為單一的 learning problem。
像是直接拿到一個 function，這個 function 是個切平面，平面的兩邊就是兩個 class。
這裡就都看不到 posterior 了。

然而這裡提一下 posterior 的好處：

Minimizing risk
    考慮一下，如果你的 loss matrix 會一直變動
    (maybe in financial applications)。
    手上有 posterior 的話，loss function (objective function)
    就可以隨時改完算出來。如果是 discriminant function 的話，整個 model
    要重新 training。

Reject option
    有 posterior 就可以設定個 threshold :math:`\theta` 來處理兩個 posterior
    接近的狀況。


Compensating form class priors
    可以對 unbalance dataset 做處理。想象兩個 class 在 training dataset 的
    數量是 :math:`1:1000` 。
    首先 :math:`posterior \propto prior` 這個 prior 就是 :math:`p(C_k)` 就是
    training class 的各個百分比。
    那麼我們現在製作一組 balance 的 dataset 這個 prior
    就會是 :math:`\frac{1}{K}` 。我們在這個 balance dataset 裡面求完
    posterior 之後，只要 :math:`posterior \times K \times original\ prior`
    然後在做 normalization，就能完成這種 unbalance 的 training。
    不然直接 training 的 generalization 很差，因為 :math:`1:1000` 。

Combining models
    假設我們希望把問題的 size 縮小，拆成兩個問題。
    e.g. 原本我們做 cancer detection 的 input 有 X-ray imgage 與 血液資訊。
    那麼現在我們把 input vector :math:`\vec{x}` 拆成
    :math:`\vec{x_I},\ \vec{x_B}` 。

    現在我們做個很強烈的假設：這兩個 input vectors 是 independent。
    得

    .. math::

        p(\vec{x_I}, \vec{x_B} | C_k) = p(\vec{x_I} | C_k) p(\vec{x_B} | C_k)

    因為我們假設了 independent，joint probability 就是相乘，上面這個是
    `conditional independence`

    得 posterior:

    .. math::

        p(C_k | \vec{x_I}, \vec{x_B}) & \propto p(\vec{x_I}, \vec{x_B})p(C_k) \\
            & \propto p(\vec{x_I}|C_k) p(\vec{x_B}|C_k) p(C_k) \\
            & \propto \frac{p(\vec{x_I}|C_k) p(C_k) p(\vec{x_B}|C_k) p(C_k)}{p(C_k)} \\
            & \propto \frac{p(C_k|\vec{x_I}) p(C_k | \vec{x_B})}{p(C_k)}

    整個問題的 posterior 會正比於 兩個 posterior 相乘後處以
    training data 的比例 (:math:`p(C_k)`)。最後做 normalization 就可以得到
    精確的 posterior。

    這是個 `naive Bayesian model` 的例子。
    後面的章節會介紹不需要這個 conditional independent 假設的方法。


Loss functions for regression
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


.. math::

    E(L) = \int \int L(t, y(\vec{x})) p(\vec{x}, t) d\vec{x} dt

看到 :math:`\int \int f(\cdot) d\vec{x} dt` 的意義就是：
排列組合所有的 :math:`d\vec{x}` 跟 :math:`dt` ，每個排列組合都乘上
:math:`f(\cdot)`

舉個例子是 :math:`L(t, y(\vec{x})) = (y(\vec{x}) - t)^2` square lose function

.. math::

    E(L) = \int \int (y(\vec{x}) - t)^2 p(\vec{x}, t) d\vec{x} dt

我們的目標時 minimizing 後選出 :math:`y(x)` (model)。


Information Theory
----------------------------------------------------------------------

資訊量怎麼計算？

假設我們有個 discrete random variable :math:`x` , 代表資訊.

資訊量被視為不一樣的程度，觀測 :math:`x` 若長得很不一樣，
就是有新的資訊，資訊量高，反之亦然。

假設有 probability distribution :math:`p(x)`
代表資訊的分佈（資訊出現頻率各有高低，
或是說有 n 個 state 這些 state 出現的機率）,
我們想要尋找一個 `Monotonic function`_ :math:`h(x)` 來代表觀測 x 後，有多少的
information gain ，或是說有多 suprise

E.g. state space :math:`{a, b, c, d}` 但不是 uniform distribution，
可以是 :math:`{0.2, 0.4, 0.3, 0.1}`.

先想象，假設 :math:`x, y` 為獨立 (independent) 的 random variable,
:math:`h(x, y)` 應該長成:

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

對於比較集中的 distribution，:math:`H` 的值就比較低，代表 entropy 低。
反之，比較散開的 distribution，:math:`H` 就高，亂度高。

.. _Monotonic function: https://en.wikipedia.org/wiki/Monotonic_function


Continueous Var
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

將 :math:`entropy` 推廣到 Continueous variable 上得：

.. math::

    H(\vec{x}) = - \int p(\vec{x}) \ln p(\vec{x}) d\vec{x}

上式稱為 `differential entropy`


Relative Entropy
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A.k.a `KL divergence`, `information divergence`, `information gain`.

首先有 unknown (true) distribution :math:`p(\vec{x})` ，
而我們有近似、model 出來的 distribution :math:`q(\vec{x})`

而 KL divergence 的意義是，當我們用近似的 coding :math:`q(\vec{x})` 去表示資料
(random variable :math:`\vec{x}` 的 state) 時，
平均上來說，還缺多少資訊量、coding 量，才能精確表達？

.. math::

    KL(p \| q)
      & = \int p(\vec{x}) \hat{h}(\vec{x}) \, d\vec{x} -
          \int p(\vec{x}) h(\vec{x}) \, d\vec{x} \\
      & = \Big( - \int p(\vec{x}) \ln q(\vec{x}) \, d\vec{x} \Big) -
          \Big( - \int p(\vec{x}) \ln p(\vec{x}) \, d\vec{x} \Big) \\
      & = - \int p(\vec{x}) \ln \frac{q(\vec{x})}{p(\vec{x})} \, d\vec{x} \ge 0

- KL divergence equals to 0 if and only if :math:`q(\vec{x}) = p(\vec{x})`

- :math:`KL(p \| q) \neq KL(q \| p)`

- Data compression 跟 density estimation
  (modelling 一個 distribution) 有密不可分的關係。
  過多或過少的 coding 都會讓 KL divergence != 0

若能夠從 unknown distribution :math:`p(\vec{x})` 拿到 data/sample。
那麼可以用 parametric distribution :math:`p(\vec{x} | \vec{\theta})`
e.g. multivariate Gaussian。那麼 optimize :math:`\vec{\theta}` 的
方法就可以是 minimizing KL divergence of :math:`p(\vec{x})` and
:math:`q(\vec{x} | \vec{\theta})` w.r.t. :math:`\vec{\theta}`.
然而，因爲不知道 :math:`p(\vec{x})` 所以無法直接進行 optimization，
只能用 finite sum 來表示 :math:`p(\vec{x})` 的期望值。

.. math::

    KL(p \| q) & \simeq
    \sum_n^N \Big( - \ln \frac{q(\vec{x_n} | \vec{\theta})}{p(\vec{x_n})} \Big) \\
    & \simeq
    \sum_n^N \Big( - \ln q(\vec{x_n} | \vec{\theta}) + \ln p(\vec{x_n}) \Big) \\

這裡可以看到，right-hand side 跟 :math:`\vec{\theta}` 無關。
left-hand side 的第一項可以視爲 under :math:`\vec{\theta}` ，
對 training data 的 negative log likelihood。
所以得到，minimizing KL divergence 等價於 maximizing likelihood function。

實作上會看到

.. math::

    KL(p \| q) \simeq \sum_n^N \ln \frac{p(\vec{x_n})}{q(\vec{x_n} | \vec{\theta})}


Convex function
**************************************************

.. math::

    f(a + (1 - \lambda)b) \le \lambda f(a) + (1 - \lambda) f(b)

where :math:`0 \le \lambda \le 1`


Jensen's inequality
**************************************************

對上面 convex function 性質的推廣

.. math::

    f \Big( \sum_i \lambda_i x_i \Big) \le \sum_i \lambda_i f(x_i)

此時，視 :math:`\lambda_i` 為 probability :math:`p(x_i)`

.. math::

    f(E(x)) \le E(f(x))

若是 continueous variable

.. math::

    f\Big( \int \vec{x} p(\vec{x}) \, d\vec{x} \Big) \le
    \int f(\vec{x}) p(\vec{x}) \, d\vec{x}

Proof of :math:`KL(p \| q) \ge 0`

#. 先找一 convex function :math:`f(t) = - \ln t`

#. 因為 convex, 所以可以 Jensen's inequality 成立

   .. math::

       f\Big( \int \vec{x} p(\vec{x}) \, d\vec{x} \Big)
       & \le
       \int f(\vec{x}) p(\vec{x}) \, d\vec{x} \\
       \Rightarrow - \ln \Big( \int \vec{x} p(\vec{x}) \, d\vec{x} \Big)
       & \le
       - \int \ln \vec{x} p(\vec{x}) \, d\vec{x} \\

#. 上面的 :math:`\vec{x}` 代換成 :math:`\frac{q(\vec{x})}{p(\vec{x})}`

   .. math::

       - \ln \Big( \int \frac{q(\vec{x})}{p(\vec{x})} p(\vec{x}) \, d\vec{x} \Big)
       & \le
       - \int \ln \frac{q(\vec{x})}{p(\vec{x})} p(\vec{x}) \, d\vec{x} \\
       \Rightarrow
       - \ln \Big( \int q(\vec{x}) \, d\vec{x} \Big)
       & \le
       - \int \ln \frac{q(\vec{x})}{p(\vec{x})} p(\vec{x}) \, d\vec{x} \\
       \Rightarrow
       - \ln 1 & \le KL(p \| q) \\
       \Rightarrow
       0 & \le KL(p \| q) \\


Mutual Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

描述兩份資訊（兩個 random variables）dependent 的多寡。

換句話說，量測兩個 random variables 之間 share 了多少資訊。
讓我們在已知其中一個的狀態下，可以去除多少另一個 variable 的不確定選項。

.. math::

    I(X; Y) = \sum_{x \in X} \sum_{y \in Y} p(x, y)
        \log \Big( \frac{p(x, y)}{p(x)p(y)} \Big)

如果 random variable 為 independent 則

.. math::

    \log \Big( \frac{p(x, y)}{p(x)p(y)} \Big) =
    \log \Big( \frac{p(x)p(y)}{p(x)p(y)} \Big) = \log 1 = 0

