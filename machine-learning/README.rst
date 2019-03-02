========================================
機器學習 (Machine Learning)
========================================


.. contents:: 目錄


機器學習演算法種類
========================================

* Supervised Learning
* Unsupervised Learning
* Semi-Supervised Learning
* Online Learning / Active Learning



機器學習模型
========================================

* `深度學習 (Deep Learning) <deep-learning>`_
* `決策樹 (Decision Tree) <decision-tree>`_
* `線性模型 (Linear Model) <linear-model>`_



主題
========================================

* `機器學習相關套件 <library/>`_

* Technique
    - `回歸 (Regression) <technique/regression.rst>`_
    - `Clustering <clustering.rst>`_
    - `Dimensionality Reduction <dimensionality-reduction.rst>`_
    - `Naive Bayes Classifier <naive-bayes-classifier.rst>`_
    - `t-SNE <t-SNE.rst>`_
    - `Transfer Learning <technique/transfer-learning.rst>`_
    - `Ensemble Learning <technique/ensemble.rst>`_
    - `量化 (Quantization) <technique/quantization.rst>`_
    - `降低 Overfitting <technique/reduce-overfitting.rst>`_


* `ONNX <onnx.rst>`_



模型優化 - 在盡量維持模型準確度的狀況下降低運算需求
===================================================

:目標: 降低運算量，維持同等級的準確度


* `量化 (Quantization) <technique/quantization.rst>`_
    - 例如把浮點數運算換成整數運算
* 刪減 (Pruning)
    - 把不重要的處理刪掉
* 知識淬鍊 (Knowledge Distillation)
    - 藉由現有的模型訓練出另一個小模型，但是達到同等成效
    - 原先的模型可能很大或者使用了 Ensemble 才達到效果，新模型從中學習真正的重點，除去不必要的計算
    - 原模型當老師，新模型當學生
    - Transfer Learning
* 正規化 (Regularization)
    - 懲罰複雜度
    - 選擇成效同等級但是複雜度較低的模型，除非複雜模型有顯著優勢
    - 例如 Lasso、Ridge、ElasticNet 等演算法就是這個概念
    - L1 Regularization： Lasso 的作法，把所有權重的絕對值加起來當 cost
    - L2 Regularization： Ridge 的作法，把所有權重的平方加起來當 cost
* 選擇性計算 (Conditional Computation)
    - 根據特定條件選擇要用到的子模型，在某些狀況下省略步驟來節省運算
    - 例如 Early Exit
* 反覆優化 (Iterative Pruning)
    - 把數個模型優化技巧組合起來重複套用
    - 就像是編譯器在編譯時會有數個優化操作來回套用


參考：

* [2015] `Distilling the Knowledge in a Neural Network <https://arxiv.org/abs/1503.02531>`_
* [2015] `Learning both Weights and Connections for Efficient Neural Networks <https://arxiv.org/abs/1506.02626>`_
* [2017] `A Survey of Model Compression and Acceleration for Deep Neural Networks <https://arxiv.org/abs/1710.09282>`_
* `Neural Network Distiller <https://nervanasystems.github.io/distiller/index.html>`_



類神經網路節點 (Cell)
========================================

Recurrent Neural Network
------------------------------

人類的思考不會每次都從頭開始，
一定是基於過去的經驗來加速判斷，
可能從過去的錯誤經驗反省，
也可能從過去的成功經驗再次改善，
思考會搭配記憶持續地變化。

Recurrent Neural Network (RNN) 基於這一點在節點中加入了迴圈，
如果把這個迴圈展開其實就是一般的神經網路不斷地重複下去，
回饋可以回到自己身上或是上游，
也可以設定在幾個回合後才回饋，
但是根據這概念設計的都叫 RNN。


RNN 應用：

* 語音辨識 (Speech Recognition)
* 翻譯 (Translation)
* Language Modeling
* Image Captioning


上下文 (context) 遠近差異：

* short-term dependencies： 關聯處很近，例如預測「雲朵在 **天上** 」
* long-term dependencies： 關聯處很遠，例如預測「今天比較晚下班，路上又遇到塞車，所以我比較 **晚回家** 」


原始的 RNN 在處理短期的資訊很有用，
但是在長期的資訊卻無法良好地處理，
為了處理長期資訊的問題演變出了 LSTM。
LSTM (Long Short Term Memory) 是一種特化的 RNN，
由 Hochreiter & Schmidhuber 在 1997 年提出，
處理了長期資訊的問題，
在眾多應用中展現出優良的成效，
被廣泛使用中。

LSTM 內部的設計並不唯一，
雖然主要概念相同，
但不同研究可能會對內部設計做些調整，
其中熱門的變體像是 2014 年被提出的 `GRU (Gated Recurrent Unit) <https://arxiv.org/abs/1406.1078>`_ 。

在處理長期資訊問題上並不是只有 LSTM 這一個解法，
其他還有不同的設計，
例如 Clockwork RNN。


大致上的分類：

* RNN
    - LSTM
        + GRU
        + Depth Gated RNN
    - Clockwork RNN


參考：

* `Understanding LSTM Networks <https://colah.github.io/posts/2015-08-Understanding-LSTMs/>`_
* `The Unreasonable Effectiveness of Recurrent Neural Networks <https://karpathy.github.io/2015/05/21/rnn-effectiveness/>`_
* [2015] `LSTM: A Search Space Odyssey <https://arxiv.org/abs/1503.04069>`_
    - 熱門 LSTM 變種比較
* [2015] `An Empirical Exploration of Recurrent Network Architectures <http://proceedings.mlr.press/v37/jozefowicz15.pdf>`_
    - 大量 RNN 設計比較


Convolutional Neural Networks
------------------------------

CNN 的設計在於把同樣訓練好的節點重複套用到資料的每個部份，
把小節點當做寫好的函式，
拿去資料每個小部份做計算，
一個小部份要包含多少資料可以自由決定（可以是數個一維資料也可以是數個多維資料），
最後蒐集所有計算結果後做後續處理（例如最後交給 Fully Connected Neural Network 處理）。

Convolutional Layer 通常會搭配 Pooling Layer，
例如數個結果取最大值，
藉此可以快速地降低資料量。

一般的 Convolutional Layer 裡面是一層 Perceptron，
但是也有多層 Perceptron 的設計，
例如 2013 年在 `Network In Network <https://arxiv.org/abs/1312.4400>`_ 提出的
mlpconv (Multiple Layer Convolution Layer)。


歷史：

* [2012] `ImageNet Classification with Deep Convolutional Neural Networks <https://www.cs.toronto.edu/~fritz/absps/imagenet.pdf>`_
    - 突破當時圖像分類的能力
    - 採用新的節點 ReLU
    - 使用新技術 DropOut 來避免 Overfitting
    - 使用大量圖像資料 ImageNet
    - 節點深度跟當時其他作法比起來深很多
    - 使用 CNN


CNN 應用：

* 電腦視覺 (Computer Vision)



參考：

* `Conv Nets: A Modular Perspective <https://colah.github.io/posts/2014-07-Conv-Nets-Modular/>`_



其他資源
========================================

* `Interpretable Machine Learning A Guide for Making Black Box Models Explainable <https://christophm.github.io/interpretable-ml-book/>`_
    - 解讀模型的線上書籍
* `Mathematics for Machine Learning <https://mml-book.github.io/>`_
    - CH1 - 數學基礎
        + 線性代數
        + 解析幾何
        + 矩陣分解
        + 向量分析
        + 機率與分布
    - CH2 - 機器學習的應用
        + 線性回歸
        + 降低維度 & PCA
        + SVM
* `Machine Learning From Scratch <https://github.com/eriklindernoren/ML-From-Scratch>`_
    - 眾多常見模型的 Python 實做範例
* `Machine Learning for Software Engineers <https://github.com/ZuzooVn/machine-learning-for-software-engineers>`_
    - 學習規劃
* `Deep Learning Ocean <https://github.com/osforscience/deep-learning-ocean>`_
    - 許多常見的模型發表時的論文連結
    - 根據不同模型分類
    - 優化技巧、特定領域應用
    - 各種原始資料
* `Awesome Deep Vision <https://github.com/kjw0612/awesome-deep-vision>`_
    - 電腦視覺論文、課程、書籍、文章
* `Awesome Deep Learning papers and other resources <https://github.com/endymecy/awesome-deeplearning-resources>`_
    - 論文、模型、課程、書籍、應用範例
* `Awesome Deep Learning <https://github.com/ChristosChristofidis/awesome-deep-learning>`_
    - 書籍、課程、影片、論文、原始資料、研討會、工具
* `Awesome Machine Learning <https://github.com/josephmisiti/awesome-machine-learning>`_
    - 各語言的套件

* `Stanford - Unsupervised Feature Learning and Deep Learning Tutorial <http://deeplearning.stanford.edu/tutorial/>`_
* `Stanford - CS224n: Natural Language Processing with Deep Learning <http://web.stanford.edu/class/cs224n/>`_
* `MIT - Deep Learning <https://deeplearning.mit.edu/>`_
* `MIT - 6.S099: Artificial General Intelligence <https://agi.mit.edu/>`_
* `UC Berkeley - CS 294-112 - Deep Reinforcement Learning <http://rail.eecs.berkeley.edu/deeprlcourse/>`_
* `UC Berkeley - CS 294-129 - Designing, Visualizing and Understanding Deep Neural Networks <https://bcourses.berkeley.edu/courses/1453965/pages/cs294-129-designing-visualizing-and-understanding-deep-neural-networks>`_
* `Berkeley Artificial Intelligence Research Lab <https://bair.berkeley.edu/>`_
