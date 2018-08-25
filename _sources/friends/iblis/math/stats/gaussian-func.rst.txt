.. _gaussian-func:

Gaussian Function
===============================================================================

在圖上看起來就是個對稱的 `bell curve`

Def
----------------------------------------------------------------------

Generic univariable form:

.. math::

    f(x) = \alpha e^{- \frac{(x - \beta)^2}{2 \gamma^2}}

Where :math:`\alpha,\ \beta,\ \gamma \in \mathbb{R}`

- :math:`\alpha` 控制整個 curve 的 peak

- :math:`\beta` 控制 peak 的發生點

- :math:`\gamma` (standard diviation) 控制整個 bell 的寬度


Examples
----------------------------------------------------------------------

.. code-block:: julia

    function f(a, b, c)
        x -> a * e^(-((x - b)^2) / (2c^2))
    end

    using UnicodePlots

    lineplot(f(2, 0, 3), -10, 10)


Probility Density Function
----------------------------------------------------------------------

.. math::

    \mathcal{N}(x) = \frac{1}{\sigma \sqrt{2\pi}} e^{-\frac{(x - \mu)^2}{2\sigma^2}}


因為，根據機率公理

.. math::

    \int f(x) & = 1 \\
    \int_{-\infty}^{\infty} \alpha e^{-\frac{(x - \beta)^2}{2\gamma^2}} dx & = 1


D-dimensional form:

.. math::

    \mathcal{N}(x) = \frac{1}{(2\pi)^{\frac{D}{2}} | \Sigma | ^{\frac{1}{2}} }
        e^{- \frac{ (\vec{x} - \vec{\mu})^T \Sigma^{-1} (\vec{x} - \vec{\mu})}{2}}

where :math:`\Sigma` is the covariance matrix


Density Estimation
----------------------------------------------------------------------

假設我們有 dataset :math:`\mathcal{D}` 。
假設 data distribution 是 gaussian 但 :math:`\mu,\ \sigma` 未知，
且 dataset 裡面每個 observation 都是 i.i.d.

.. math::

    p(\mathcal{D} | \mu, \sigma) = \prod_{x \in \mathcal{D}} \mathcal{N} (x | \mu, \sigma)

觀察 :math:`\mathcal{N}(x | \mu, \sigma)` 這個其實就是 likelihood function
:math:`\mathcal{L}(data | model)`

所以簡單的 maximum likelihood，就可以得到 :math:`\mu, \sigma` ，
就可以完成 density function 的估測。

實際上會用 log likelihood function，避免計算上的 underflow
(多個機率連乘造成的)。

.. math::

    \begin{alignat}{2}
    & & p(\mathcal{D} | \mu, \sigma) & = \prod \mathcal{N}(x | \mu, \sigma) \\
    & \Rightarrow & \ln p(\mathcal{D} | \mu, \sigma) & =
        \ln \prod \mathcal{N}(x | \mu, \sigma) \\
    & \Rightarrow & & =
        \sum \ln \mathcal{N}(x | \mu, \sigma) \\
    & \Rightarrow & & =
        \sum \ln \Big(
            \frac{1}{\sigma \sqrt{2\pi}} e ^{- \frac{(x - \mu)^2}{2 \sigma^2}}
        \Big) \\
    & \Rightarrow & & = \sum \Big\{
            - \frac{(x - \mu)^2}{2 \sigma^2} + \ln \frac{1}{\sigma \sqrt{2\pi}}
        \Big\} \\
    & \Rightarrow & & = - \sum \frac{(x - \mu)^2}{2 \sigma^2} -
        N \ln \sigma \sqrt{2\pi} \\
    & \Rightarrow & & = - \sum \frac{(x - \mu)^2}{2 \sigma^2} -
        N \ln \sigma - \frac{N}{2} \ln 2\pi
    \end{alignat}

然後 maximum log likelihood 得

.. math::

    \mu_{ML} = \frac{1}{N} \sum_n^N x_n

發現就是對 data 做 `simple mean`

.. math::

    \sigma^2_{ML} = \frac{1}{N} \sum_n^N (x_n - \mu_{ML})^2

就是 `simple variance`

但是 :math:`\sigma_{ML}` 是被低估的，需要修正為

.. math::

    \frac{1}{N - 1} \sum_n^N (x_n - \mu_{ML})^2


Reference
----------------------------------------------------------------------

- https://en.wikipedia.org/wiki/Gaussian_function
