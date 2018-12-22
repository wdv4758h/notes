=======================================
ONNX (Open Neural Network Exchange)
========================================


.. contents:: 目錄


ONNX 介紹
========================================

Deep Learning 的神經網路會經由 Graph 來表示，
一些 framework（例如 CNTK、Caffe2、Theano、TensorFlow）會用 Static Graph，
一些 framework（例如 PyTorch、Chainer）會用 Dynamic Graph。
這些 Graph 作為模型的 IR (Intermediate Representation) 存在，
會在後續被優化、轉換成裝置可以執行的形式，
裝置例如 CPU、GPU、FPGA。

先前各個 framework 都實做了自己的 API、Graph、Runtime，
不同實做各有優缺點，
有的很適合研究，有的很適合布署，
而實做之間也難以互通，
造成研究到實際產品運用有一段落差。

ONNX 的目標就是定義出通用的 IR 給各個 framework，
開發者根據需求選用適合自己的 framework，
但是可以藉由 ONNX 在不同 framework 間溝通，
甚至可以快速地布署到支援 ONNX 的客製化硬體上，
藉此達到強化生態圈的作用。

ONNX 目前有兩種形式，
基本定義是針對基於神經網路的機器學習演算法，
而 ONNX-ML 則額外再加了一些傳統機器學習會用到的型別和操作，
各個 framework 可以根據需求選擇是否需要神經網路以外的操作。



ONNX 定義
========================================

ONNX 目前有兩個版本：

* ONNX：只有神經網路
* ONNX-ML：基於 ONNX 擴充傳統機器學習的操作


ONNX 目前定義了以下部份：

* extensible computation graph model
* standard data types
* built-in operators


ONNX 並未定義任何 runtime 實做，
runtime 可以對 model 進行以下可能的處理：

* 直譯執行
* codegen 成程式語言實做
* 硬體直接支援
* 其他各種可能


ONNX 只是個儲存和交換的格式，
並未定義 framework 內部該如何處理和表示，
不同實做也可以基於 ONNX 去擴充操作（Model 可以使用 ``opset_import`` 屬性來使用擴充的操作）。


ONNX 目前實做是用 Protobuf 的形式定義，
專案內有一些 ``.proto`` 或 ``.proto3`` 的檔案就是定義實做。



ONNX 優化
========================================

ONNX 作為不知道後端狀況的 IR 有不少優化限制，
但是還是有很多優化是可以在這狀況下進行的，
ONNX 專案也嘗試提供優化工具來簡化模型，
甚至提供給針對裝置優化的編譯器一個可以重複利用的處理。



ONNX 視覺化
========================================

要視覺化模型可以使用以下工具：

* `Netron <https://github.com/lutzroeder/Netron>`_
    - 完整 GUI，有不知道的操作時也可以馬上點出解釋和範例
* `Visual DL <https://github.com/PaddlePaddle/VisualDL>`_
    - 完整 GUI，除了模型視覺化以外還支援其他分析用的視覺化
* `ONNX net drawer <https://github.com/onnx/onnx/blob/master/onnx/tools/net_drawer.py>`_
    - 生出 DOT 定義
