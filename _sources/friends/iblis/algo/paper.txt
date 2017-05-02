Paper
===============================================================================


.. _deep-nn-mnist:

Deep Big Simple Neural Nets Excel on Hand-written Digit Recognition
----------------------------------------------------------------------

:tag: NN, MLP, GPU, training set deformations, MNIST, BP
:ref: https://arxiv.org/pdf/1003.0358.pdf
:dataset: MNIST


Data Preproc
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Elastic deformation (Elastic distortion) 來達到 regularization。
用了大量的參數，但是 generization 沒有變差。

Feature scaling 到 [-1.0, 1.0]


Learning Algo
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

* On-line BP without momentum (what is momentum on BP?).

* 2 - 9 hidden layers MLP

* Arch descibe in table 1

* learning rate 遞減




Tiled convolutional neural networks
----------------------------------------------------------------------


:ref: https://papers.nips.cc/paper/4136-tiled-convolutional-neural-networks.pdf

* "convolutional (tied) weights significantly reduces
  the number of parameters"


TODO
----------------------------------------------------------------------


* https://arxiv.org/pdf/1103.4487.pdf
