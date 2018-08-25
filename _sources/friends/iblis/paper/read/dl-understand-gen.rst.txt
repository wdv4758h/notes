Understand Deep Learning Requires Rethinking Generalization
===============================================================================

ref:
https://openreview.net/forum?id=Sy8gdB9xx&noteId=Sy8gdB9xx

Abstract
----------------------------------------------------------------------

DNN 成功的展示了相當好的 generalization， 即小的 train/test performance 差異。
以前傳統常識上會把好的 generalization 歸功與好的 model 性質或是好的
regularization 技術。

透過大量系統性的實驗，我們證明傳統的手法不能解釋為何 large NN 的 generalization
好。更精確的說，實驗中使用 state-of-the-art CNN for img classification


Intro
----------------------------------------------------------------------

DNN 常常參數量遠大於 data points 。但是，某些 model 仍然有低的
generalization error ( :math:`train error - test error` ).
然而
