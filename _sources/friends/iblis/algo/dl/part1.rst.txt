Part I
===============================================================================

Math basic

Machine Learning
----------------------------------------------------------------------

Problem setting:

#. 已知有 meta-rule ，但 meta-rule 難以量化或是量化過程繁雜。
   e.g. 人臉辨識；人腦能夠辨識，有 meta-rule ，但人們難以敘述此 meta-rule

#. 我們相信 :math:`x` 為 :math:`y` 的成因之一。希望透過 learning 的
   optimization 來得到關係。
    e.g. DNS and cancer


Linear Model
----------------------------------------------------------------------

* 經典的 XOR 問題，無法用 linear model 解。需要做高維度的 feature extraction
  或是 NN 的轉換 座標空間 來解。


Linear Regression
----------------------------------------------------------------------

Multivariate Linear Regression:

.. math::

    h_{\vec{\theta}}(\vec{x}) = \theta^T \vec{x}

* 常用 MSE 作為 cost function

.. math::

    J(\vec{\theta}) = \frac{1}{2m} \sum_i^m (h_{\vec{\theta}}(\vec{x}) - y)^2

這個 cost function 是由 :math:`X = \{ \vec{x_1}, \dots, \vec{x_m} \}`
決定； data set :math:`X` 要先給定才有 :math:`J(\theta)` 。即，給不同的
data set 會有不同的 :math:`J(\theta)` ， :math:`\theta`
前面的常數項會不同，但都是二次式。

* 這個 cost function 有 close form solution, 可使用 :ref:`normal-equation-method`
  求解，但是在高維度會用 GD， why ?

    * http://stats.stackexchange.com/questions/23128

    * inverse matrix 的計算量是 :math:`O(n^3)`


Univariable Linear Regression
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

* Univariable -> 單變數

Assume:

.. math::

    h_{\theta_0, \theta_1}(x) = \theta_0 + \theta_1 x

The cost function will be:

.. math::

    J(\theta_0, \theta_1) =
    \frac{1}{2m} \sum_i^m (h_{\theta_0, \theta_1}(x_i) - y_i)^2


Then, if we simplify :math:`h`, let :math:`\theta_0 = 0`,

.. math::

    \begin{align}
        J(\theta_1) & = \frac{1}{2m} \sum_i^m (h_{\theta_1}(x_i) - y_i)^2 \\
                    & = \frac{1}{2m} \sum_i^m (\theta_1 x_i - y_i)^2
    \end{align}

Objective function:

.. math::

    arg\min_{\theta_1} J(\theta_1)

It looks like this:

.. image:: ./img/uni_linreg_cost.png

This objective function is *convex* and has a close form solution.


Polynomial Regression
----------------------------------------------------------------------

Change linear to higher-order ploynomial model

e.g.

.. math::

    h(x) = \theta_0 + \theta_1 x_1 + \theta_2 x_2 +
           \theta_3 x_1^2 + \theta_4 x_2^2


Gradian Descent
----------------------------------------------------------------------

* learning rate :math:`\eta` 對 linear regression 的影響：

  * 在接近 minimum 而且 :math:`\eta` 過大時，下一次 iteration 會穿過 minimum
    然後 cost function 的微分量可能會更大，若更大會造成後續 iteration 發散。

* Batch Gradian Descent, 對所有的 training set 都考慮後的計算。

* http://mccormickml.com/2014/03/04/gradient-descent-derivation/


Logistic Regression
----------------------------------------------------------------------

實際上是 classifcation algo.

outcome

.. math::

    0 \leq h(x) \leq 1

Sigmoid function (logistic function):

.. math::

    \sigma(z) = \frac{1}{1 + e^{-z}}

.. image:: ./img/sigmoid.png

Model

.. math::

    \begin{align}
        h_{\vec{\theta}}(\vec{x}) & = \sigma(\theta^T \vec{x}) \\
            & = \frac{1}{1 + e^{-\theta^T \vec{x}}}
    \end{align}


Logistic Regression with MSE
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

If we select MSE as cost function,
we will obtain non-convex cost function.

.. image:: ./img/logistic-mse.png

在上圖中會看到 :math:`< 0` 附近的點出現了 local optima；
在 :math:`> 0` 附近的點有 global optima 。

所以顯然 MSE 在 Logistic Regression 身上不上很好的選擇。


Logistic Regression Cost Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    J(\theta) = \frac{1}{m} \sum_i^m Cost(h_\theta(x_i), y_i)

.. math::

    \begin{align}
        Cost(h_\theta(x), y) & =
        \begin{cases}
            - \log(h_\theta(x)),     & \text{if $y = 1$} \\
            - \log(1 - h_\theta(x)), & \text{if $y = 0$}
        \end{cases} \\
        & = -y \log(h_\theta(x)) - (1 - y) \log(1 - h_\theta(x))
    \end{align}

In case of :math:`y = 1`

.. image:: ./img/logistic-cost-1.png

此圖橫軸為 :math:`h_\theta(x)` , 而 :math:`h_\theta(x)` 的值域為
:math:`(0, 1)` ， 所以在此圖的 Domain 為 :math:`(0, 1)` ，
而對於 0 到 1 的數值取 負 log 得到 convex function

In case of :math:`y = 0`

.. image:: ./img/logistic-cost-2.png


Differentiation
    長得跟 Linear Regression with MSE 一樣
    why?


.. _normal-equation-method:

Normal Equation Method
----------------------------------------------------------------------

.. math::

    \vec{\theta} = (X^TX)^{-1} X^T \vec{y}

Julia code:

.. code-block:: julia

    pinv(X' * X) * X' * y


Example
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

給定 (x, y) = (1, 2), (2, 4), (3, 6)

人腦可直觀看出 :math:`y = 2x`

.. code-block:: julia

	julia> X = A[:, 1:2]
	3×2 Array{Int64,2}:
	1  1
	2  1
	3  1

	julia> Y = A[:, 3]
	3-element Array{Int64,1}:
	2
	4
	6

	julia> pinv(X' * X) * X' * Y
	2-element Array{Float64,1}:
	2.0
	-1.02141e-14


If Non-interible
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

* ``pinv`` vs ``inv`` 的差別？

    * ``pinv`` -- psudo-inverse

causes:

    * Redundant feature -- linear dependent (?)
        * e.g. :math:`x_1 = 3 x_2`

        * 如果這個發生在 GD 上面？
          還是可以得到 cost function :math:`J` ，照算

    * Too many feature
        * 換句話說， training 的 data 筆數不夠。

        * 在 linear regression 之下， feature 數目即 :math:`\theta` 的量，
          在 parameter 過多之下需要 :ref:`dl-regularization`


ReLU
----------------------------------------------------------------------

.. code-block:: julia

    relu(x) = (x > 0) ? x : 0


https://en.wikipedia.org/wiki/Rectifier_(neural_networks)

- low computational cost. 但我認為這不是決定性的因素

- 對於 deep 的 MLP 在做 back propagation 的時候， sigmoid function or ``tanh``
  容易造成在經過多次微分後，在前面的的 layer 的變動量很小，收斂效果差。
  sigmoid 跟 ``tanh`` 的 upper / lower bound 在 deep MLP 底下反而是收斂的阻礙。

- ReLU 在 x 輸出是 0 的部分，造成了某種 topology 的選擇，
  如果採用 fully connected NN ， outcome 為 0 的部分可以想象成把 connection
  拔掉。


Feature Scaling
----------------------------------------------------------------------

Linear Regression:
    Linear Regression 的 MSE 做 GD ，如果你的 feature 之間的 scale 差太多，
    cost function 會出現很扁的山谷，使 GD 收斂效果差。 Rescaling 之後可以是
    cost function 接近圓，而 GD 收斂比較好。


Mean Normalization
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    x' = \frac{x - \mu}{x_{max} - x_{min}}

或是分母亦可以用 standard deviation

.. math::

    x' = \frac{x - \mu}{\sigma}

model 使用上，必須用當時的 :math:`\sigma, \mu` 進行還原得到最後的結果。


Data 量的問題
----------------------------------------------------------------------

* 以 face detection 舉例：
    * 我的資料中給你整張臉，這個資料量很充足，做 learning 沒問題。

    * 資料有缺損，給你半張臉，或許還是 learn 的出來。

    * 資料中，只給你兩根頭髮，這根本無法 learning ，前提不足。

    * 那麼 financial data 的資料量完整性足夠嗎？


Learning Rate Selection
----------------------------------------------------------------------

Learning rate :math:`\eta` 是個 hyper parameter，必須在啟動 algo 之前就決定。
而在 linear regression 之下使用 fixed learning rate 已可以使 GD 收斂。
過大過過小的 :math:`\eta` 都會造成發散。建議透過觀測 cost function 在
iteration/epoch 的 plotting 來調整 learning rate。
