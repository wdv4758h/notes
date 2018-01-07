========================================
Quantization
========================================


.. contents:: 目錄


介紹
========================================

量化（Quantization）指的就是把數值從一個較大的集合轉換到一個較小的集合的過程，
例如類比訊號轉成數位訊號就是這種處理，
又或者是把 32 位元的浮點數轉換成 8 位元的整數。

量化是一個有損的過程，
所以會影響最後的結果，
影響可大可小，
對於影響的衡量可以藉由計算量化誤差（Quantization Error）來管控。

量化的使用範圍很多，
ADC（類比轉數位）是其中一種，
另外大部分的有損壓縮也是以量化作為核心發展出來的。

在 Deep Learning 的領域裡討論量化時，
通常是為了降低執行時所需要的資源量，
藉由量化來減少記憶體需求並增加執行速度。



參考
========================================

* [2016] `Quantized Convolutional Neural Networks for Mobile Devices <https://arxiv.org/abs/1512.06473>`_
* `Wikipedia - Quantization (signal processing) <https://en.wikipedia.org/wiki/Quantization_(signal_processing)>`_
