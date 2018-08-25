Linear Model for Regression
===============================================================================

Linear Basis Function Models
----------------------------------------------------------------------

原始的出發點是簡單的 polynomial

.. math::

    y(\vec{x}, \vec{w}) & = w_0 + w_1 x_1 + \dots + w_D x_D \\
                        & = \vec{w} \cdot \vec{x}

Extend 這個 model 成

.. math::

    y(\vec{x}, \vec{w}) & = w_0 + w_1 \phi_1(\vec{x}) + \dots + w_D \phi_D(\vec{x}) \\
                        & = w_0 + \sum_{i=1}^D w_i \phi_i (\vec{x})

在化簡單一點，
let :math:`\phi_0 (\vec{x}) = 1`

.. math::

    y(\vec{x}, \vec{w}) = \vec{w} \cdot \vec{\phi}(\vec{x})

對比一開始最簡單的 linear model，
x 是 scalar，還不是 vector ，
就是 let :math:`\phi_i(x) = x^i` 的結果。

所以整個 model 對 :math:`\vec{w}` 而言就是 basis function 的
linear combination，才稱為 linear model。

這個 :math:`\phi_i` 即為 `basis function` ，
對於你的問題，可以任意取。e.g.

.. math::

    \phi_i(x) = e^{- \frac{(x - \mu_i)^2}{2s^2}}

想象上面的 basis function 的 :math:`\mu_i` 可以調控每個 basis function 的 value
在哪裡附近， :math:`s` 調控寬度的 scale。
上面這個例子就是 Gaussian basis functions。
在這裡我們不在乎機率相關的解釋，或是 normalization 相關的作用，
因為我們的 :math:`y` 在使用這些 basis function 時還會乘上 :math:`w` 來調整。

再看一個例子，sigmoid basis function:

.. math::

    \phi_i(x) = \sigma \Big( \frac{x - \mu_i}{s} \Big)

where :math:`\sigma` is the logistic function:

.. math::

    \sigma(x) = \frac{1}{1 + e^{-x}}

:math:`\therefore`

.. math::

    \phi_i(x) = \frac{1}{1 + e^{- \frac{x - \mu_i}{s}}}

同理，也可以用 :math:`\tanh`

.. math::

    \tanh(x) = 2 \sigma(x) - 1

看到這裡
選用 :math:`\tanh` 作為 basis function 的效果其實會跟 :math:`\sigma` 一樣，
因為是 linear combination。

還有很多知名的 basis，如 `Fourier` basis。


Maximum Likelihood and Least Squares
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


