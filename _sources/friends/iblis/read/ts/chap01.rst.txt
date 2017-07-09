Intro
===============================================================================

`Assets Returns`
    Scale-free feature.
    return series 比 price series 具有更多良好的統計特性。但是有各種
    return definitions.

`Simple Gross Return`

    Single period return.

    .. math::

        1 + R_t = \frac{P_t}{P_{t-1}}

    上面的公式完全等同於 `相對前一個 period 的漲跌幅` , 即一階微分。


`Multiperiod Simple Return`

    Hold :math:`k` period. A.k.a compound return.

    .. math::

        \begin{align*}
            1 + R_t[k] & = \frac{P_t}{P_{t-k}} \\
                    & = \frac{P_t}{P_{t-1}} \times \frac{P_{t-1}}{P_{t-2}}
                    \times \dots \times \frac{P_{t-k+1}}{P_{t-k}} \\
                    & = (1 + R_t)(1 + R_{t-1}) \dots (1 + R_{t-k+1}) \\
                    & = \prod_{i=0}^{k-1} (1 + R_{t-i})
        \end{align*}


    所以 Multiperiod 實際上就是 single period 的連乘。

`Annualized Returns`

    If we hold :math:`k` years.

    .. math::

        Annualized\{R_t[k]\} = (R_t[k])^{\frac{1}{k}} - 1

    上式可以理解成 :math:`R_t[k]` 開根號是去做 geometric mean, 因為
    multiperiod 可以寫成每個 period 連乘。

    整理後得

    .. math::

        Annualized\{R_t[k]\} =
            \exp \Bigg[ \frac{1}{k} \sum_{i=0}^{k-1} \ln{1 + R_{t-i}} \Bigg] - 1

    用 Taylor expansion 做近似 (but why?)

    .. math::

        Annualized\{R_t[k]\} = \frac{1}{k} \sum_{i=1}^{k-1} R_{t-j}


`Countinuous Compounding`

    * `proof <http://www-stat.wharton.upenn.edu/~waterman/Teaching/IntroMath99/Class04/Notes/node13.htm>`_

    Net value of a asset :math:`A`

    .. math::

        \begin{align*}
            A & = C e^{rm} \\
            C & = A e^{-rm} & \text{(present value)}
        \end{align*}

    where :math:`r` is the interest rate per annum,
    :math:`C` is the initial capital.

    *present value* 的想法是， 5 年後的 100 元，現在是多少？ 肯定小於 100 元


`Continuously Compounded Return`

    :def: natural logarithm of the simple gross return
    :A.k.a.: log return

    In one-period:

    .. math::

        r_t = \ln(1 + R_t) = \ln \frac{P_t}{P_{t-1}}

    Extend to Multiperiod:

    .. math::

        \begin{align*}
            r_t[k] & = \ln(1 + R_t[k]) \\
                   & = \ln \Bigg[ \prod_{i=0}^{k-1} (1 + R_{t-i}) \Bigg] \\
                   & = \sum_{i=0}^{k-1} \ln (1 + R_{t-i}) \\
                   & = \sum_{i=0}^{k-1} r_{t-i}
        \end{align*}

    所以 multiperiod 就是把 one-period sum 起來。


`Portfolio Return`

    simple portfolio return 直接計算 simple return 的 weighting 得。

    continuously compounded protfolio return 只有近似
    :math:`r_{p, t} \approx \sum w_i r_{it}`,
    且有 assumption: "simple returns Rit are all small in magnitude" (?)

`Excess Return`

    相對對於 risk free asset 的 return

    也可以理解成 long asset + short risk free asset 的 total return
