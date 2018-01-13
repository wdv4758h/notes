========================================
回歸 (Regression)
========================================


.. contents:: 目錄


演算法
========================================

Linear Regression
------------------------------

* OLS (Ordinary Least Squares) (普通最小平方) (Linear Least Squres)
* Ridge
* Lasso
* Elastic Net
* LARS (Least Angle Regression)
* LARS Lasso
* OMP (Orthogonal Matching Pursuit)
* Bayesian
* Logistic
* SGD (Stochastic Gradient Descent)
* Perceptron
* Passive Aggressive Algorithms
* Robustness
		- RANSAC (Random Sample Consensus)
		- Theil-Sen estimator: generalized-median-based estimator
		- Huber Regression
* Polynomial



最早的回歸作法是 1805 年 Legendre 和 1809 年 Gauss 提出的 Least Squares，
並套用到天文學上。

其後在 1821 年，Gauss 提出了 Least Squares 更進一步的使用，
包含 Gauss–Markov theorem。


OLS:

.. image:: /images/machine-learning/technique/ols-formula.png
.. image:: /images/machine-learning/technique/ols-plot.png


OLS 的 overfit 問題：

  TODO: https://ithelp.ithome.com.tw/articles/10186402

  > This method computes the least squares solution using a singular value decomposition of X.
  > If X is a matrix of size (n, p) this method has a cost of O(n p^2), assuming that n >= p.


為了解決 OLS 回歸的 overfit 問題，
其後發展出懲罰線性迴歸，
例如 Ridge 和 Lasso。



Ridge 加入了係數大小作為懲罰，
藉此來調整回歸的狀況，
複雜度則是和 OLS 相同。
（Ridge = Regression + L2 Regularization）

.. image:: /images/machine-learning/technique/ridge-formula.png



Lasso 也是在 OLS 上加入額外的懲罰來調整，
藉此傾向於使用較少的參數來解決手上的問題。
（Lasso = Regression + L1 Regularization）

.. image:: /images/machine-learning/technique/lasso-formula.png


Multi-task Lasso: TODO



Elastic Net


LARS

LARS Lasso

OMP (Orthogonal Matching Pursuit)

Bayesian

Logistic


SGD (Stochastic Gradient Descent)

Perceptron

Passive Aggressive Algorithms

Robustness
	RANSAC: RANdom SAmple Consensus
	Theil-Sen estimator: generalized-median-based estimator
	Huber Regression

Polynomial




Ordinary Least Squares Regression (OLSR)
----------------------------------------

Stepwise Regression
------------------------------

Multivariate Adaptive Regression Splines (MARS)
-----------------------------------------------

Locally Estimated Scatterplot Smoothing (LOESS)
-----------------------------------------------

Logistic Regression
------------------------------


參考
========================================

* An Empirical Comparison of Supervised Learning
* An Empirical Evaluation of Supervised Learning in High Dimensions
* `Wikipedia - Regression analysis <https://en.wikipedia.org/wiki/Regression_analysis>`_
* `Wikipedia - Ordinary Least Squares <https://en.wikipedia.org/wiki/Ordinary_least_squares>`_
* `Wikipedia - Ridge regression (Tikhonov regularization) <https://en.wikipedia.org/wiki/Tikhonov_regularization>`_
* `Wikipedia - Lasso (statistics) <https://en.wikipedia.org/wiki/Lasso_(statistics)>`_
* `scikit-learn - Generalized Linear Models <http://scikit-learn.org/stable/modules/linear_model.html>`_
		- 除介紹如何使用 scikit-learn 裡面的那些 regression 外，也有不少背景知識介紹
