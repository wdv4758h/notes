Autoencoder
===============================================================================

主要是用於特徵的抽取，或是降低維度。

Feature extraction: 物理意義是尋找 feature representation

Let :math:`\phi` is encoder.

Let :math:`\psi` is decoder.

.. math::

    \phi = X \rightarrow F

    \psi = F \rightarrow X


Objective function:

.. math::

    arg \min_{\phi, \psi} \| X - \psi (\phi (X)) \|^2


:Undercomplete Autoencoder:
    hidden coding 的維度是降低的. 在 non-linear 能力過好的
    undercomplete autoencoder 一樣會很 overfitting，
    如同建立字典，而無 generization

:Overcomplete Autoencoder:
    coding 維度提高
