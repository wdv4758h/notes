==============================================
樸素貝葉斯分類器 （Naïve Bayesian Classifier）
==============================================


機率知識
========================================

基本介紹
------------------------------

* Prior Probability （事前機率）
    - 猜測跟某高斯分佈很像（猜參數），為一開始的估計值
* Likelihood Probability
    - 根據實際數據計算模型
* Posterior Probability （事後機率）
    - 由 Prior 和 Likelihood 修正後的猜測值，預期其為和資料背後的模型成正比的模型


貝氏定理： ::

    Posterior = (Likelihood * Prior) / Evidence


* Test
    - 衡量拿到的資料跟高斯分佈有多像
    - 根據不同的資料量、分佈，選用不同的 test



範例
------------------------------

假設我們有手機和筆電兩種裝置，
手機和筆電的 CPU 都有 Intel 和 ARM 兩種類型。
已知一臺裝置為 Intel CPU，則其為筆電的機率為何？

::

    P(筆電 | Intel) = P(Intel | 筆電) * P(筆電) / P(Intel)

其中，

* ``P(筆電)`` 為 ``事前機率（Prior）`` ，在我們觀察到裝置是 Intel CPU 前的機率
* ``P(筆電 | Intel)`` 為 ``事後機率（Posterior）`` ，在我們觀察到裝置是 Intel CPU 後的機率
* ``P(Intel)`` 為 ``Evidence`` ，裝置是 Intel CPU 是已知的事實，這是我們得到這事實的機率
* ``P(Intel | 筆電)`` 為 ``Likelihood`` ，當我們的裝置是筆電時，裝置也是 Intel CPU 的機率




事後機率 （Posterior Probability）
=============================================

::

    P(A | B) = P(A ∩ B) / P(B) = P(B | A) P(A) / P(B)

    P(A | B ∩ C) = P(A ∩ B ∩ C) / P(B ∩ C) = P(B ∩ C | A) P(A) / P(B ∩ C)

    ---------------------------------

    Assuming Conditional Independence

    P(A | B ∩ C) = P(A ∩ B ∩ C) / P(B ∩ C) = P(B ∩ C | A) P(A) / P(B ∩ C)
                 = P(B | A) P(C | A) / P(B ∩ C)

    f(i) = P(B | A) P(C | A) P(A)
    P(A | B ∩ C) = f(i)/sum(f(j))



事前機率 （Prior Probability）
=============================================


演算法
========================================

Naive Bayesian
------------------------------

Gaussian Naive Bayesian
------------------------------

Multinomial Naive Bayesian
------------------------------

Bayesian Network (BN)
------------------------------

Bayesian Belief Network (BBF)
------------------------------

Averaged One-Dependence Estimators (AODE)
-----------------------------------------


參考
========================================

* `Wikipedia - Naive Bayes classifier <https://en.wikipedia.org/wiki/Naive_Bayes_classifier>`_
* `scikit-learn - Naive Bayes <http://scikit-learn.org/stable/modules/naive_bayes.html>`_
