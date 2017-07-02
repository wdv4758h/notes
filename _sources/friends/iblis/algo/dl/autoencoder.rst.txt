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


