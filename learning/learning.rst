========================================
Learning
========================================

Dimensionality Reduction
========================================

t-SNE
------------------------------

t-distribution (Student's t-distribution) 在少量資料 (< 30) 時，
仍可以接近 normal distribution，
而且適用 population variance 不知道的情況。

* 期望把資料從高維度轉到低維度後，仍然可以保持資料間的相似性
* 把大量的資料 (global) 圈出數個 local，對 local (較小量的資料) 做處理
* 使用 Kullback–Leibler divergence 作為轉換前和轉換後之間相似度的 error function
* 使用 Gradient Descent 來找到最小的 Kullback–Leibler divergence
* 結果保留 local 內資料的相似性
    - 例如： ``7`` 和 ``9`` 在七段顯示器的模式下只差了一個 bit，t-SNE 可以把它區分出來，但是仍然會在相近的區域，不會離太遠

* `Wikipedia - t-distributed stochastic neighbor embedding <https://en.wikipedia.org/wiki/T-distributed_stochastic_neighbor_embedding>`_
* `Wikipedia - Heavy-tailed distribution <https://en.wikipedia.org/wiki/Heavy-tailed_distribution>`_
    - 開頭跟結尾的分佈機率比 normal distribution 重一些
* `Wikipedia - Kullback–Leibler divergence <https://en.wikipedia.org/wiki/Kullback%E2%80%93Leibler_divergence>`_
* `Understanding the t-distribution and its normal approximation <http://rpsychologist.com/d3/tdist/>`_
    - 用 D3.js 畫範例
* `Visualizing Data Using t-SNE <https://www.youtube.com/watch?v=RJVL80Gg3lA>`_
* `scikit-learn - Manifold learning <http://scikit-learn.org/stable/modules/manifold.html>`_



Todo
========================================

* degree of freedom
* more different distribution
* PCA
