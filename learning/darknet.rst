========================================
Darknet
========================================


.. contents:: 目錄


介紹
========================================

`Darknet <https://pjreddie.com/darknet/>`_ 是一套 Neural Network 的 Framework，
用 C 和 CUDA 撰寫，
作者在其中提供了常見 model 的設定，
也提供內建的 Darknet reference model 可以做分類，
作者也基於這個 Framework 開發 Real-Time Object Detection 的 YOLO model。



編譯
========================================

.. code-block:: sh

    $ git clone https://github.com/pjreddie/darknet.git
    $ cd darknet
    # 可以透過 Makefile 設定一些參數，例如 GPU=1、OPENMP=1
    $ make -j
    $ ./darknet



YOLO
========================================

`YOLO: Real-Time Object Detection <https://pjreddie.com/darknet/yolo/>`_ ，
為目前即時物件偵測的 state-of-the-art。


.. code-block:: sh

    $ wget https://pjreddie.com/media/files/yolo.weights
    $ ./darknet detect cfg/yolo.cfg yolo.weights data/dog.jpg


若想要更快速的版本，
可以使用 Tiny YOLO，
不過準確度會比 YOLO 低一點。

.. code-block:: sh

    $ wget https://pjreddie.com/media/files/tiny-yolo.weights
    $ ./darknet detect cfg/tiny-yolo.cfg tiny-yolo.weights data/dog.jpg



參考
========================================

* `Tiny Darknet <https://pjreddie.com/darknet/tiny-darknet/>`_
    - 類似 SqueezeNet 那樣特別降低 model 大小的 Darkenet reference model
    - wget https://pjreddie.com/media/files/tiny.weights
    - ./darknet classify cfg/tiny.cfg tiny.weights data/dog.jpg

* `ImageNet Classification <https://pjreddie.com/darknet/imagenet/>`_
    - AlexNet
    - VGG-16
    - Resnet
    - Densenet

* `Darknet OpenCL fork <https://github.com/myestro/darknet>`_
* [2014] `One weird trick for parallelizing convolutional neural networks <https://arxiv.org/abs/1404.5997>`_
* `ImageNet Classification with Deep Convolutional Neural Networks <https://www.cs.toronto.edu/~fritz/absps/imagenet.pdf>`_
