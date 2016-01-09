========================================
Boost.Compute
========================================

Boost.Compute 是一個只有 header 檔的 library，
把 OpenCL 的 API 包裝成類似 STL 的介面，
不需要額外的 linking 參數 (除了 OpenCL 之外)，
例如：

.. code-block:: sh

    g++ -I/path/to/compute/include test.cpp -lOpenCL


Reference
========================================

* [GitHub] `Boost.Compute <https://github.com/boostorg/compute>`_
