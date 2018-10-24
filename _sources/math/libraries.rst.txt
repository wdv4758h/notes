========================================
數學相關套件 (Math Libraries)
========================================


.. contents:: 目錄


BLAS (Basic Linear Algebra Subprograms)
========================================

低階矩陣和向量操作的套件規範（矩陣相乘、矩陣相加等等）


常見實做：

* OpenBLAS
* ATLAS
* cuBLAS
* clBLAS
* clBLAST
* Eigen BLAS
* GotoBLAS
    - 開發者為 後藤和茂（Kazushige Gotō）
* Intel MKL
* Netlib BLAS


參考：

* `Wikipedia - BLAS <https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms>`_



LAPACK
========================================

高階的線性代數運算，
例如矩陣分解（LU、LLt、QR、SVD、Schur 等），
可用於尋找 eigenvalues 或 singular value 或解線性系統。

LAPACK 是基於 BLAS 上去建立的，
但是通常會跟 BLAS 分開，
可以選擇任意的 BLAS 實做。


參考：

* `Wikipedia - LAPACK <https://en.wikipedia.org/wiki/LAPACK>`_



ATLAS (Automatically Tuned Linear Algebra Software)
===================================================

ATLAS 是跨平台的 BLAS 實做，
但是也實做部份 LAPACK 的功能。


參考：

* `Wikipedia - ATLAS <https://en.wikipedia.org/wiki/Automatically_Tuned_Linear_Algebra_Software>`_



Intel MKL (Math Kernel Library)
========================================



Eigen
========================================
