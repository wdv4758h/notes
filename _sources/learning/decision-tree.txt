========================================
決策樹學習 （Decision Tree）
========================================

:學習種類: 監督式學習
:使用領域: 分類、回歸
:優點:
    * 容易理解、視覺化
    * 需要的資料前處理較少
    * 使用上的時間複雜度是 ``O(log(n))``
    * 可以處理數值型、類別型資料
:缺點:
    * 可能會 overfitting 造成決策樹過於複雜
    * 找到最佳的決策樹是 NP-complete 的問題
    * 有些問題很難用決策樹解決（例如 XOR、多工問題）
    * 如果資料被某些種類佔據大部份，建出來的決策樹會有偏差，建議事先平衡資料


.. contents:: 目錄


決策樹的種類
========================================

* 分類樹 （Classification tree）
* 回歸樹 （Regression tree）


決策樹建立技巧（通常被稱為 ``ensemble methods`` ）（建立不只一棵決策樹）：

* Bagging
* Random Forest
* Boosted Trees
* Rotation Forest


度量 （Metrics）
========================================

類似決策樹的 cost functions


* Shannon Entropy
* Gini Impurity
* Chi-Square Test


Shannon Entropy
------------------------------

:重要觀念:
    * 信息的產生是隨機的
    * 發生機率愈小，信息量愈大


信息的產生是隨機的
++++++++++++++++++++

如果信息的產生不是隨機的話，
那就可以事先得知，
而此時因為這件事變成已知，
所以接下來的訊息對這個接收者而言就毫無訊息量。
例如，告訴一位正躺在室外曬日光浴的人「現在出太陽」，
對他而言這是已知的事情，
因此這句話毫無訊息量，形同廢話。


發生機率愈小，信息量愈大
++++++++++++++++++++++++

假如發生機率是百分之百，
那就是已知的事情，
也就是毫無訊息量。
相反的，如果發生的機率很小，
那麼這件事的訊息量就會很大。
例如，你中了樂透頭獎，這件事對你的訊息量就很大。


觀念融入公式
++++++++++++++++++++

1. 把信息資料用隨機變數 S 表示：

::

    S = {s0, s1, s2, ..., sM-1}

2. 其機率為：

::

    pi = p(si)

3. 機率合必為 1

::

    sum(pi) = 1

4. 自我資訊量 （self-information）

::

    I(sk) = log(1/pk) = - log pk


百分之百會發生的事情信息量為零

::

    I(sk) = log 1 = 0


任何事情發生都有信息量

::

    I(sk) >= 0

愈不容易發生的事情，消息量愈大

::

    I(sk) >= I(si), pk <= pi

兩個獨立事件的信息量可以相加

::
    I(sk) + I(si) = log(1/pk) + log(1/pi)
                  = log(1/(pk * pi))
                  = I(sk si)

5. 信息量期望值

::

    H(S) = E[I(sk)]
         = sum(pk * log(1/pk))


6. 極值

::

    0 ≤ H(S) ≤ log M

    log(2, e) = 0.6931471805599453
    log(2, 2) = 1


資訊獲利
++++++++++++++++++++

（以 Entropy 作為亂度的度量方式，Entropy 愈低，亂度愈低，分辨的愈好）


資訊獲利（選擇資訊獲利高的路） ::

    IG(T, a) = H(T) - H(T|a)



簡單的 Entropy 計算：

.. code-block:: python

    from math import log

    def entropy(possibility, base=2):
        '''
        entropy of single condition
        '''
        if possibility in (0, 1):
            return 0
        return - possibility * log(possibility, base)


    def total_entropy_of_bool(possibility, base=2):
        '''
        total entropy of all conditions with two possibility in random variable

        S = {s1, s2}
        p(s2) = 1 - p(s1)

        >>> total_entropy_of_bool(9/19)
        0.9980008838722995
        '''
        return entropy(possibility, base) + entropy(1-possibility, base)


    def total_entropy_of_split(class1=(0, 0), class2=(0, 0)):
        '''
        weighted average entropy

        >>> total_entropy_of_split((5, 4), (4, 6))
        0.9804837096363519
        >>> total_entropy_of_split((6, 0), (3, 10))
        0.5332393623577425
        '''
        total1 = sum(class1)
        total2 = sum(class2)
        total = total1 + total2
        return total1/total * total_entropy_of_bool(class1[0]/total1) + \
               total2/total * total_entropy_of_bool(class2[0]/total2)


    def information_gain(class1=(0, 0), class2=(0, 0)):
        '''
        >>> information_gain((5, 4), (4, 6))
        0.017517174235947564
        >>> information_gain((6, 0), (3, 10))
        0.46476152151455696
        '''
        positive = class1[0] + class2[0]
        negative = class1[1] + class2[1]
        total = positive + negative
        old_entropy = total_entropy_of_bool(positive/total)
        new_entropy = total_entropy_of_split(class1, class2)
        return old_entropy - new_entropy


    def gain_ratio():
        pass



.. image:: /images/learning/entropy.png


.. code-block:: python

    import matplotlib.pyplot as plt
    import numpy as np

    f = np.vectorize(total_entropy_of_bool)
    x = np.linspace(0.001, 1, 100)
    y = f(x)
    function_label = plt.plot(x, y, label="H (total entropy for two possibility)")
    plt.legend(handles=function_label)
    plt.xlabel('x')
    plt.ylabel('y')


    # x = np.linspace(0, 1, 100)
    # y = f(x)          # all 0, bug ?
    # y = f(x[1:])      # fine


獲利比率
++++++++++++++++++++

::

    GainRatio(A) = Gain(S, A) / SplitInfo(S, A)


Gini Impurity
------------------------------

::

    Gini(D) = 1 - sum(pi**2)


簡單的 Gini 計算：

.. code-block:: python

    from fractions import Fraction

    def gini(all_possibility=(Fraction(0, 1), Fraction(1, 1)), laplace=False):
        '''
        >>> gini()
        Fraction(0, 1)
        >>> gini((Fraction(3, 5), Fraction(2, 5)))
        Fraction(12, 25)
        >>> gini((Fraction(3, 5), Fraction(2, 5)), True)
        Fraction(24, 49)
        '''
        total = 1
        for i in all_possibility:
            if laplace:
                i = laplace_correction(i)
            total -= i**2
        return total


    def gini_of_bool(possibility, laplace=False):
        '''
        gini of all conditions with two possibility in random variable

        S = {s1, s2}
        p(s2) = 1 - p(s1)

        >>> gini_of_bool(Fraction(3, 5))
        Fraction(12, 25)
        >>> gini_of_bool(Fraction(3, 5), True)
        Fraction(24, 49)
        '''
        print(possibility)
        return gini((possibility, 1-possibility), laplace)


    def gini_of_split(class1=(0, 0), class2=(0, 0), laplace=False):
        '''
        weighted gini

        >>> gini_of_split((1, 1), (1, 2), True)
        Fraction(61, 125)
        '''
        total1 = sum(class1)
        total2 = sum(class2)
        total = total1 + total2
        return Fraction(total1, total) \
                    * gini_of_bool(Fraction(class1[0], total1), laplace) + \
               Fraction(total2, total) \
                    * gini_of_bool(Fraction(class2[0], total2), laplace)

    def gini_gain(class1=(0, 0), class2=(0, 0), laplace=False):
        '''
        >>> gini_gain((6, 2), (3, 3))
        -0.030612244897959162
        '''
        positive = class1[0] + class2[0]
        negative = class1[1] + class2[1]
        total = positive + negative
        old_gini = gini_of_bool(Fraction(positive, total), laplace)
        new_gini = gini_of_split(class1, class2, laplace)
        return new_gini - old_gini

    def laplace_correction(number: Fraction):
        return Fraction(number.numerator+1,
                        number.denominator+2)

極值：

``0 ≦ Gini ≦ 1``

* 有事情百分之百會發生時，Gini 會是下限 ``0``
* Gini 的上限為 ``1``

    假設有 M 種可能性，每種可能性發生的機率都相同，
    那麼機率都會是 ``1/M`` ，
    此時 Gini 的值為 ``1 - M * (1/M)**2 = 1 - 1/M`` ，
    當 M 愈大時，Gini 就愈大，
    當 M 趨近無限大時，M 就趨近於 ``1``


Laplace Correction (Laplace Estimate)
+++++++++++++++++++++++++++++++++++++

「機率理論可用於衡量一句話的可信度」

連續法則（Rule of Succession）

如果成功了 m 次，失敗了 n 次，
那下次成功的機率為 ``(m+1)/(m+n+2)``



範例
++++++++++++++++++++

已知案例（N 代表正常，D 代表有疾病）：

+------+--------+--------+--------+------+
| 病患 | 症狀 1 | 症狀 2 | 症狀 3 | 結果 |
+======+========+========+========+======+
| 1    | V2     | V1     | V1     | D    |
+------+--------+--------+--------+------+
| 2    | V1     | V1     | V2     | N    |
+------+--------+--------+--------+------+
| 3    | V1     | V2     | V1     | D    |
+------+--------+--------+--------+------+
| 4    | V2     | V2     | V2     | N    |
+------+--------+--------+--------+------+
| 5    | V2     | V2     | V1     | N    |
+------+--------+--------+--------+------+


欲判斷的病患：

+------+--------+--------+--------+------+
| 病患 | 症狀 1 | 症狀 2 | 症狀 3 | 結果 |
+======+========+========+========+======+
| 6    | V2     | V1     | V2     | ?    |
+------+--------+--------+--------+------+


第一次分辨
~~~~~~~~~~

建立決策樹：

::

    Gini(D) = 1 - ((3+1)/(5+2))**2 - ((2+1)/(5+2))**2 = 24/49 = 0.4849
    Gini(D, 症狀1) = 2/5 * Gini(D11) + 3/5 * Gini(D12)
    Gini(D, 症狀2) = 0.488


.. code-block:: python

    gini_of_bool(Fraction(3, 5), True)      # 24/49 = 0.4897959183673469
    gini_of_bool(Fraction(2, 5), True)      # 24/49 = 0.4897959183673469

    # 用「症狀 1」區分
    # (D, N)
    gini_of_split((1, 1), (1, 2), True)     # 61/125 = 0.488

    # 用「症狀 2」區分
    # (D, N)
    gini_of_split((1, 1), (1, 2), True)     # 61/125 = 0.488

    # 用「症狀 3」區分
    # (D, N)
    gini_of_split((2, 1), (2, 0), True)     # Fraction(524, 1125), desired: Fraction(219, 500)
                                            # 0.4657777777777778, desired: 0.438
                                            # 2/2 會太早被化簡為 1/1 ...

    # 用「症狀 3」區分（選擇 Gini 小的）
    # (D, N)
    gini_gain((2, 1), (2, 0), True)         # float: 0.057614512471655326, desired: 0.0518


第二次分辨
~~~~~~~~~~

已知案例－類別一（症狀 3 為 V2）（結果都一樣，不需再分）：

+------+--------+------+
| 病患 | 症狀 3 | 結果 |
+======+========+======+
| 2    | V2     | N    |
+------+--------+------+
| 4    | V2     | N    |
+------+--------+------+

已知案例－類別二（症狀 3 為 V1）：

+------+--------+--------+------+
| 病患 | 症狀 1 | 症狀 2 | 結果 |
+======+========+========+======+
| 1    | V2     | V1     | D    |
+------+--------+--------+------+
| 3    | V1     | V2     | D    |
+------+--------+--------+------+
| 5    | V2     | V2     | N    |
+------+--------+--------+------+


欲判斷的病患：

+------+--------+--------+--------+------+
| 病患 | 症狀 1 | 症狀 2 | 症狀 3 | 結果 |
+======+========+========+========+======+
| 6    | V2     | V1     | V2     | ?    |
+------+--------+--------+--------+------+


建立決策樹：

::

    Gini(D') = 1 - ((1+1)/(3+2))**2 - ((2+1)/(3+2))**2 = 12/25 = 0.48
    Gini(D', 症狀1) = 1/3 * Gini(D'11) + 2/3 * Gini(D'12) = 0.4815
    Gini(D', 症狀2) = 0.4815
    Gini(D') - Gini(D', 症狀2) = 0.48 - 0.4815 = - 0.0015
    => 不需要再擴增子樹


結果
~~~~~~~~~~

決策樹：

::

    +-----------------+
    | 症狀 3 為 V2 ？ |
    +-----------------+
         /      \
        /        \
     是 |        | 否
        v        v
    +------+  +--------+
    | 正常 |  | 有疾病 |
    +------+  +--------+


根據建完的決策樹，第六個病患會被判斷為「正常」。


Chi-Square Test
------------------------------


建立決策樹的演算法
========================================

+-----------------+--------+
| 成本函數        | 使用者 |
+=================+========+
| Shannon Entropy | * ID3  |
|                 | * C4.5 |
|                 | * C5.0 |
+-----------------+--------+
| Gini Impurity   | * CART |
+-----------------+--------+


Pseudocode ： （重點在 ``PickBestFeature`` ）

::

    BuildTree(Data)
        if all elements of Data have the same y value, then
            MakeLeafNode(y)
        else
            feature := PickBestFeature(Data)
            MakeInternalNode(feature,
                             BuildTree(SelectFalse(Data, feature)),
                             BuildTree(SelectTrue(Data, feature)))




* ID3 （Iterative Dichotomiser 3）
* C4.5 （ID3 的後繼者）
* C5.0 （C4.5 的後繼者）

* CART （Classification And Regression Tree）

* CHAID （CHi-squared Automatic Interaction Detector）
* MARS: extends decision trees to handle numerical data better.
* Conditional Inference Trees


::

    ID3 ---> C4.5 ---> C5.0



ID3
------------------------------

C4.5
------------------------------

C5.0
------------------------------

CART
------------------------------

CHAID
------------------------------

Decision Stump
------------------------------

Conditional Decision Tree
------------------------------

M5
------------------------------

M5P
------------------------------


Ensemble Methods
========================================

Ensemble Methods 的目標是把多個基本的估計合起來使用，
以增加功能性。

Ensemble Methods 大致可以分成兩種：

* 平均：把數個各自建立的估計方式平均起來使用，以獲得比單一估計方式要好的結果或減少偏差。
    - Bagging
    - Random Forests
* 加速：把數個依序建立的估計方式和起來使用，以結合數個弱方法產生較好的結果。
    - AdaBoost
    - Gradient Tree Boosting


Bagging
------------------------------

選出訓練資料的數個任意子集合來建立數個估計方法，
最後結合各估計方法的結果。
此作法常用來減少單一估計方法的偏差（減少 overfitting 的影響）。
此方法通常適合使用在強而複雜的模型，
另一方面加速類型的 Ensemble Methods 則通常適合使用在弱的模型。


Random Forests
------------------------------

從所有的特徵中隨機選取一部份來建立估計，
建立好數個估計方法後和起來使用，
最後的出綜合的結論。
和 Bagging 很大的差異就是 Random Forests 不會用所有的特徵去建立模型，
所以除了和 Bagging 一樣去指定要建多少個模型外，
還會指定每次要用多少特徵去建模型。

使用案例：Microsoft 在 2011 年發的論文
「Real-Time Human Pose Recognition in Parts from Single Depth Images」中，
就有描述到在 Kinect 中使用 Randome Forests 來幫忙判斷人體的姿勢，
而該篇論文則被 CVPR 選為該年年度最佳論文。


AdaBoost
------------------------------

AdaBoost 為 1995 年由 Freund 和 Schapire 發表的作法。
AdaBoost 的概念為把一系列的弱分類器（只比亂猜好一點點，例如很小的決策樹）
利用權重和投票機制組起來，
形成最後的決定。
各弱分類器的權重一開始是平均的，
在經過一連串的訓練後會得到不一樣的權重分佈，
最後重要特徵的弱分類器就會拿到比較高的權重。


使用案例：在電腦視覺領域有使用 AdaBoost 的知名例子，
就是於 2001 年發表的「Viola–Jones object detection framework」，
其利用 AdaBoost 來把數個弱分類器組起來形成強分類器，
藉此在分類品質跟執行速度間取得了不錯的平衡。
該篇在即時物件偵測是一個極為重要的貢獻，
現在可以在 OpenCV 之類的專案看到基於該作法的實作，
可應用在人臉偵測之類的地方。
（之前修電腦視覺課程時，我跟朋友的期末專題剛好就在看這個 XD）


Gradient Tree Boosting (Gradient Boosted Regression Trees) (GBRT)
-----------------------------------------------------------------

GBRT 會利用 Gradient Descent 的方式降低給定 cost function 的值，
因此選用不同的 cost function 可以產生初步同的結果。
GBRT 常用於像是網頁搜尋排名之類的領域。


Stacked Generalization (Blending)
---------------------------------


決策樹的優點
========================================

決策樹的缺點
========================================


混用
========================================

Decision Tree + Naive Bayes
------------------------------



實作現況
========================================

Library 現況：

+--------------+--------------+
| Library      | 實作的演算法 |
+==============+==============+
| Orange       | C4.5         |
+--------------+--------------+
| scikit-learn | CART         |
+--------------+--------------+


* `SciPy - scipy.stats.entropy <https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.entropy.html>`_



使用範例
========================================


參考
========================================

* `Wikipedia - Decision tree learning <https://en.wikipedia.org/wiki/Decision_tree_learning>`_
* `Wikipedia - Information gain in decision trees <https://en.wikipedia.org/wiki/Information_gain_in_decision_trees>`_
* `Wikipedia - Information gain ratio <https://en.wikipedia.org/wiki/Information_gain_ratio>`_
* `Wikipedia - Rule of succession <https://en.wikipedia.org/wiki/Rule_of_succession>`_
* `Wikipedia - Additive smoothing <https://en.wikipedia.org/wiki/Additive_smoothing>`_
* `Wikipedia - Sunrise problem <https://en.wikipedia.org/wiki/Sunrise_problem>`_
* `Building Decision Trees in Python <http://www.onlamp.com/pub/a/python/2006/02/09/ai_decision_trees.html>`_
* `scikit-learn - Decision Trees <http://scikit-learn.org/stable/modules/tree.html>`_
* `scikit-learn - Ensemble methods <http://scikit-learn.org/stable/modules/ensemble.html>`_
* `Different decision tree algorithms with comparison of complexity or performance <http://stackoverflow.com/a/9996741>`_
* `熵 (Entropy) <http://episte.math.ntu.edu.tw/articles/mm/mm_13_3_01/>`_
* `What are the differences between ID3, C4.5 and CART? <https://www.quora.com/What-are-the-differences-between-ID3-C4-5-and-CART>`_
* `Machine Learning by Pedro Domingos <https://class.coursera.org/machlearning-001/lecture>`_

* `拉普拉斯 Pierre-Simon Laplace <http://highscope.ch.ntu.edu.tw/wordpress/?p=34550>`_
* `【科學史上的今天】3/23 - 拉普拉斯誕辰（Pierre-Simon Laplace, 1749－1827） <http://history.pansci.asia/post/114321504880/科學史上的今天323拉普拉斯誕辰pierre-simon-laplace>`_
* `機率歷史 (The History of Probability) <http://highscope.ch.ntu.edu.tw/wordpress/?p=39287>`_
