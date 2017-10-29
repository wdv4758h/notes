Neural Networks
===============================================================================


Raidial Based Function Networks
----------------------------------------------------------------------

常用 :ref:`gaussian-func` 。

這裡通常為了方便就取 gaussian function 的 :math:`\alpha = 1`

再來我們要決定 :math:`\beta,\ \gamma` ，實際上就是 :math:`\mu,\ \sigma` ，
決定的方法通常就是先透過分群 e.g. 最直白的 k-means 得到每一群的 :math:`\mu,\ \sigma`

假設我們取 :math:`k = 10` 群，則 RBF neuron 的 vector 長度為 :math:`k` 。

單一一個 RBF neuron 就是個 gaussian function 。

簡單的結構如：

- input vector 維度為 2，e.g. :math:`(x_1, x_2)`

- RBF neuron vector 維度為 10

- 一個 input 經過了 RBF neuron 之後就會得到 10 個值，有點像是 coding，
  其中一個最高，其餘的會指數下降。

- RBF 的 output 後面再去接 full connected NN 做分類。
