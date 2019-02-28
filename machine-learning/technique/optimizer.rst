========================================
優化器 (Optimizer)
========================================


.. contents:: 目錄


介紹
========================================

優化器的任務：更新函式參數，讓誤差減小


Gradient Descent 是在討論誤差優化時最容易先考慮的作法，
此作法是種嘗試錯誤 (Trial and Error) 的學習過程，
根據梯度 (Gradient) 所引導的方向前進，
逐漸往誤差較小的地方走。
但是每一步的大小不一定，
選太大會發散，找不到最小值。
選太小會太慢，花很多時間才找到最小值。


在實務上，Gradient Decent 需要較多的計算量，
當資料量大時就需要不少訓練時間，
因此出現許多 Gradient Descent 的改版，
在參數更新的準確度以及訓練速度之間做取捨。



基本的 Gradient Decent 作法：

* Batch Gradient Decent (Vanilla Gradienet Decent)
    - 計算成本函數 (cost function) 在整份訓練資料的梯度
    - 每次參數更新都需要用整份訓練資料做大量計算
    - 不支援線上更新 (Online Training)
    - 收斂狀況：對於誤差函式為凸面體的狀況保證會找到全域最小值，對於誤差函式為非凸面體的狀況則可能為局部最小值
    - 運算需求：大，隨訓練資料而大幅上升

* SGD (Stochastic Gradient Decent)
    - 跟 Batch Gradient Decent 的差異在於一次只做一個更新，不用拿整份資料算梯度
    - SGD 利用 Stochastic Approximation (加入了些隨機性) 來取得夠好的 Stochastic Gradient，不需要最完美的 Gradient，只要在相對少很多計算量的狀況下取得足以應用的 Stochastic Gradient 即可
    - SGD 的缺點是為了節省計算而採用這種作法會引入一些 Gradient Noise
    - 支援線上更新
    - 收斂狀況：較 Batch Gradient Decent 複雜，不太容易穩定地停在某個最小值，但是有機會在誤差函式為非凸面體的狀況跳開局部最小值。如果逐漸降低學習速率的話，SGD 的收斂狀況會逐漸趨近於 Batch Gradient Decent
    - 運算需求：比 Batch Gradient Decent 低很多

* Mini-batch Gradient Decent
    - 混合 Batch Gradient Decent 和 SGD 的優點，分小量進行
    - 現今在討論 SGD 時，通常使用的其實是 Mini-batch 的版本
    - 現今的深度學習套件大多有提供 Automatic Differentiation 來有效率地計算梯度，因此 Mini-batch 的梯度計算也相對有效率
    - 收斂狀況：較 SGD 穩定



挑戰：

* 如何選擇學習速率？
    - 學習速率太低會很慢才收斂，學習速率太高會阻礙收斂甚至發散
* 如何調整學習速率計畫？
    - 嘗試在訓練過程中調整學習速率
* 所有參數都使用同樣的學習速率嗎？
* 如何避免訓練被卡在局部最小值或鞍點？



基於 Gradient Decent 的改版演算法：

* [1986] Momentum
    - 針對 SGD 在陡峭狀況的改善
* [1983] NAG (Nesterov Accelerated Gradient)
    - 避免一昧地根據坡度加速，在進入爬升斜坡前先緩下來
* [2011] Adagrad
    - 針對比較常出現的特徵給予較小的學習速率，針對比較少出現的特徵給予叫大的學習速率
    - 適合鬆散的資料
    - 這大幅提升 SGD 的能力
    - 這作法也去除了手動調整學習速率的需求
    - 會不斷累積過去的梯度的平方來調整學習速率
    - 缺點在於 Adagrad 的作法讓學習速率下降太快，可能造成無法找到合適的結果
* [2012] Adadelta
    - 改善 Adagrad 學習速率下降太快的問題
    - 只保留過去 N 個梯度的平方來用於調整速率，不會使用過去全部的資料
* [2012] RMSprop
    - RMSprop 和 Adadelta 是同時期各自開發的演算法，處理的方式很相似
* [2015] Adam (Adaptive Moment Estimation)
    - 在 Adadelta/RMSprop 加入 bias-correction 和 Momentum
    - 除了像 Adadelta 和 RMSprop 一樣儲存過去 N 個梯度的平方外，還儲存過去 N 個梯度
* [2015] AdaMax
* [2016] Nadam (Nesterov-accelerated Adaptive Moment Estimation)
    - 在 Adam 加入 NAG
* [2018] AMSGrad
    - 適應性的學習速率在被廣泛地使用後，發現在特定領域（例如物件辨識和機器翻譯）會碰到收斂問題，而且 SGD 搭配 Momentum 可以在這情況下表現的更好
    - AMSGrad 為學習速率加入新的改善，讓它不會一昧地上升
    - 然而一些實驗中發現 AMSGrad 不一定會比 Adam 好



其他非 Gradient Decent 的演算法：

* 牛頓法 (Newton's method)
* L-BFGS (Limited-memory BFGS)
* Coordinate Descent
* GNA (Gauss–Newton Algorithm)
* LMA (Levenberg–Marquardt Algorithm)
* Newton–Fourier method



該如何選擇優化器？：

* 如果資料是鬆散的或是想要快速收斂，那選擇具有適應性學習速率的演算法通常會比較好
* 對於任意的狀況，目前常見的選擇是使用 Adam
* 一些近期的研究可能會只採用 SGD，儘管它訓練時間較長



平行和分散 SGD：

* [2011] Hogwild!
* [2012] Downpour SGD
* [2014] Delay-tolerant Algorithms for SGD
* [2015] TensorFlow (先前為 DistBelief)
* [2015] Elastic Averaging SGD



其他優化 SGD 的策略：

* Shuffling and Curriculum Learning
    - 通常我們會想要避免訓練資料的順序具有特定意義，因為這可能會讓優化演算法有偏差，因此可能會對訓練資料先進行洗牌 (Shuffling)
    - 但是在一些問題特別困難的狀況下，我們可能會想要提供特定順序的訓練資料來提升效能和收斂速度，這種建立有意義的順序資料的作法稱為 Curriculum Learning
* Batch Normalization
    - 為每一份小資料做正規化
* Early Stopping
* Gradient Noise
    - 根據 Gaussian distribution 加入雜訊
    - 在一些實驗中，加入雜訊可以讓模型更加強健



參考
========================================

* `An overview of gradient descent optimization algorithms <http://ruder.io/optimizing-gradient-descent/>`_
* `Optimization for Deep Learning Highlights in 2017 <http://ruder.io/deep-learning-optimization-2017/>`_
* `Visualizing and Animating Optimization Algorithms with Matplotlib <http://louistiao.me/notes/visualizing-and-animating-optimization-algorithms-with-matplotlib/>`_


* `Keras - optimizers.py <https://github.com/keras-team/keras/blob/master/keras/optimizers.py>`_
* `scikit-learn - SGD <https://scikit-learn.org/0.20/modules/sgd.html>`_
* `scikit-learn - SGD Penalities <https://scikit-learn.org/0.20/auto_examples/linear_model/plot_sgd_penalties.html>`_
* `Wikipedia - Stochastic Gradient Decent <https://en.wikipedia.org/wiki/Stochastic_gradient_descent>`_
* `PyTorch - Optimzer <https://pytorch.org/docs/stable/optim.html>`_
* `MXNet - Optimizer <https://mxnet.incubator.apache.org/api/python/optimization/optimization.html>`_
* `DyNet - Optimizer <https://dynet.readthedocs.io/en/latest/optimizers.html>`_
* `Chainer - Optimizer <https://docs.chainer.org/en/stable/reference/optimizers.html>`_
* `CNTK - Optimizer <https://cntk.ai/pythondocs/cntk.learners.html>`_
* `TensorFlow - tf.train <https://www.tensorflow.org/api_docs/python/tf/train/>`_
* `Caffe - Solver <https://caffe.berkeleyvision.org/tutorial/solver.html>`_
* `Lasagne - updates <https://lasagne.readthedocs.io/en/latest/modules/updates.html>`_


* `SciPy - Optimization <https://docs.scipy.org/doc/scipy/reference/tutorial/optimize.html>`_
* `Scipy lecture notes - Mathematical optimization: finding minima of functions <https://scipy-lectures.org/advanced/mathematical_optimization/>`_


* `Wikipedia - Mathematical optimization <https://en.wikipedia.org/wiki/Mathematical_optimization>`_
* `Wikipedia - Gradient method <https://en.wikipedia.org/wiki/Gradient_method>`_
* `Wikipedia - Category: Gradient methods <https://en.wikipedia.org/wiki/Category:Gradient_methods>`_
