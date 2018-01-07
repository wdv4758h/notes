========================================
TensorFlow
========================================


.. contents:: 目錄


介紹
========================================

`TensorFlow <https://github.com/tensorflow/tensorflow>`_ 是由 Google 開發的機器學習 Library，
專注在 Deep Learning 上，
可以透過 CPU 或 CUDA 執行，
目前提供 Python、C++、Java 等語言的 API，
Python 的界面是用 SWIG 做的，
而底下的一些 Linear Algebra 運算則是透過 `Eigen <https://bitbucket.org/eigen/eigen/>`_ 。

TensorFlow Lite 則是針對 Android 特製化的版本，
將接上 Android NN API。



編譯
========================================

Python Wheel
------------------------------



Pure Shared Library
------------------------------



ARM 支援
========================================

目前官方 pre-built 都只有各 x86_64 平台和 Google 自己的 Android，
如果要在其他 ARM 平台上面跑就要自己編譯，
TensorFlow 的官方 Build System 是用 Google 自己的 Bazel，
如果平台上沒有 pre-built 的 Bazel 的話就要先編出 Bazel。


TensorFlow 在 0.12 升到 1.0 時大改了很多，
以前的 Release 也不一定能順利編起來（可能需要一些修改），
尤其是要編到官方本來沒有 pre-built 的平台可能會有更多問題，
希望未來會改善。



參考
========================================

* `TensorFlow <http://www.tensorflow.org/>`_
* `Wikipedia - TensorFlow <https://en.wikipedia.org/wiki/TensorFlow>`_
* [2015] `TensorFlow: Large-Scale Machine Learning on Heterogeneous Distributed Systems <http://download.tensorflow.org/paper/whitepaper2015.pdf>`_


Podcast：

* `The Changelog #219 - TensorFlow and Deep Learning with Eli Bixby <https://changelog.com/podcast/219>`_
