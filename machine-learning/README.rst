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

* Library
    - `MXNet (from Apache) - portable Deep Learning framework <https://github.com/apache/incubator-mxnet>`_
    - `Keras - high level Deep Learning API with multiple backends <library/keras.rst>`_
    - `TensorFlow (from Google) - Machine Learning Framework <library/tensorflow.rst>`_
    - `PyTorch (from Facebook) - Deep Learning with GPU <https://github.com/pytorch/pytorch>`_
    - `Chainer - Deep Learning Framework based on Python <library/chainer.rst>`_
    - `Dlib - C++ toolkit including Machine Learning and other Algorithms <library/dlib.rst>`_
    - `Darknet - Deep Learning Framework based on C/CUDA <library/darknet.rst>`_
    - `Caffe/Caffe2 - Deep Learning Framework from UC Berkeley <https://github.com/BVLC/caffe>`_
    - `CNTK (from Microsoft) - Deep Learning toolkit <https://github.com/Microsoft/CNTK>`_
    - `scikit-learn - Machine Learning based on SciPy <https://github.com/scikit-learn/scikit-learn>`_
    - `Flux.jl - Machine Learning based on Julia <https://github.com/FluxML/Flux.jl>`_
    - `Knet.jl (from Koç University) - Deep Learning framework <https://github.com/denizyuret/Knet.jl>`_
    - `BigDL (from Intel) - distributed Deep Learning library based on Spark <https://github.com/intel-analytics/BigDL>`_
    - `ArrayFire - library for parallel computing <https://github.com/arrayfire/arrayfire>`_
    - `flashlight - C++ library for Machine Learning <https://fl.readthedocs.io/en/latest/index.html>`_

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

* `Machine Learning for Software Engineers <https://github.com/ZuzooVn/machine-learning-for-software-engineers>`_
* `Interpretable Machine Learning A Guide for Making Black Box Models Explainable <https://christophm.github.io/interpretable-ml-book/>`_
* `相關課程 <course.rst>`_
* `Awesome Machine Learning <https://github.com/josephmisiti/awesome-machine-learning>`_
* `Awesome Deep Vision <https://github.com/kjw0612/awesome-deep-vision>`_
* `Awesome Deep Learning papers and other resources <https://github.com/endymecy/awesome-deeplearning-resources>`_
* `Awesome Deep Learning <https://github.com/ChristosChristofidis/awesome-deep-learning>`_
* `Machine Learning From Scratch <https://github.com/eriklindernoren/ML-From-Scratch>`_
