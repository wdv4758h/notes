Batch Normalization: Accelerating Deep Network Training by Reducing Internal Covariate Shift
============================================================================================

在 train DNN 的時候，每個 layer 的 input 都來自上個 layer，
但是這些 input 在每次 training 的 distribution 都長的不一樣。
造成遇到 activation function 的 output 很 non-linear 的狀況不好 train
（e.g. 我用 relu，但資料一堆 negative，造成 zero，很 non-linear）
；遇到我的 input 造成充滿 non-linear 的 case 會不好 train。
這個現象是 `internal covariate shift`
所以前人在 train 都要用 low learning rate，
加上精心設計的 parameters initialization。
這個 Batch Normalization 可以用比較大的 learning rate、能接受比較不好的
parameters initialization。
Batch Normalization 的角色比較像是 regularizer，有時候就因此不需要 Dropout

Whiten
    - "linearly transformed to have zero means and unit variances"
      像是 PCA


Ref
----------------------------------------------------------------------

https://arxiv.org/pdf/1502.03167.pdf
