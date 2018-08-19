========================================
NNVM - Open Compiler for AI Frameworks
========================================


.. contents:: 目錄


介紹
========================================

`NNVM <https://github.com/dmlc/tvm/tree/master/nnvm>`_ 是一個針對 Deep Learning 的編譯器，
可以把餵入的 Graph IR 做優化，
優化完後變成 Tensor IR 交給 `TVM <https://github.com/dmlc/tvm>`_ 處理，
TVM 再優化後轉成各式不同的後端，
例如 LLVM IR、OpenCL、CUDA、特殊硬體後端等等。


.. image:: /images/compiler/nnvm.png



參考
========================================

* `NNVM Compiler: Open Compiler for AI Frameworks <http://tvmlang.org/2017/10/06/nnvm-compiler-announcement.html>`_
