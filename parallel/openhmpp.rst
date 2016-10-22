========================================
OpenHMPP
========================================

Introduction
========================================

OpenHMPP 中的 HMPP 指的是 Hybrid Multicore Parallel Programming，
為一個針對 Heterogeneous computing (異質運算) 的標準，
目標是在不涉及複雜的 GPU programming 的情況下利用硬體來加速。

OpenHMPP 提供的是一個 directive-based programming model，
最初由 CAPS (Compiler and Architecture for Embedded and Superscalar Processors) 進行。

OpenHMPP 提供了很多可以設定的 `參數 <https://en.wikipedia.org/wiki/OpenHMPP#OpenHMPP_directives>`_

OpenHMPP 包含了一些 OpenACC 沒包含的 topic：

* data-flow  extension
* tracing interface
* auto-tuning APIs
* GPU-accelerated library integration


Reference
========================================

* `Wikipedia - OpenHMPP <https://en.wikipedia.org/wiki/OpenHMPP>`_
* `CAPS OpenACC Compiler <https://www.olcf.ornl.gov/wp-content/uploads/2012/10/HMPPOpenACC-3.2_ReferenceManual.pdf>`_
