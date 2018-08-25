.. _dl-regularization:

Regularization
===============================================================================

* :math:`L^0, L^1, L^2` regularization:
  透過 penalty term 對 loss function 下手

* Data Augmented: 對 data 加入 noise 達到 model 的 robustness

* Share Weight

* Bigging, boosting

* DropOut: for NN
  http://cs.nyu.edu/~wanli/dropc/


Single Hidden Layer MLP
----------------------------------------------------------------------

給定 Input tuple 的數量，用到足夠數量的 hidden layer node *必定* 可以切開
所有 sample，這個效果在 input domain -> label domain 的 space 上看起來像是
隔出蜂窩狀的格子。概念上接近建立巨大 dictionary table，這個巨大的 table
正可能造成 overfitting。

而這樣的參數量 (w) 大， generalization 並不好，


Data Augmented
----------------------------------------------------------------------

* Image deformation: 加入了旋轉、抖動等 noise
    * :ref:`deep-nn-mnist`


Share Weight
----------------------------------------------------------------------

降低 parameter (or weight in NN context) 來避免 overfitting。
如： CNN
