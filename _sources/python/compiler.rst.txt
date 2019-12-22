========================================
Python Compiler
========================================


.. contents:: 目錄


介紹
========================================

Python 官方並沒有完整的編譯工具（只有轉成 CPython bytecode），
如果想把 Python 程式轉成真的 shared library 或是執行檔就要靠第三方套件。

* `Cython <https://github.com/cython/cython/>`_
    - 支援整個 Python 語言
    - 利用 Type Annotation 或是額外的擴充語言來達到更好的效能
    - 如果什麼輔助都沒做的話會呼叫 ``libpython`` 來執行各種操作，效能提升不多
    - 不太能直接優化 NumPy 的運算，除非更改程式碼或是使用 Pythran 做後端
* `Nuitka <https://github.com/Nuitka/Nuitka>`_
    - 支援整個 Python 語言
    - 不需要 Type Annotation 就可以達到一定的效能提升
    - 如果編譯器無法找到更有效率的作法會呼叫 ``libpython``
    - 有一定程度的 Type Inference 支援，會用於優化並避免一些 ``libpython`` 的呼叫
    - https://speedcenter.nuitka.net/
* `Pythran <https://github.com/serge-sans-paille/pythran>`_
    - 專注於 Python 在科學運算的部份（比較類似 Numba 的目標）
    - 可以優化 NumPy 的操作，把多個操作合而為一
    - 可以產生使用 OpenMP 或 SIMD 的程式碼
    - 只在 exported function 需要 Type Annotation
    - 支援產生利用 Boost.SIMD 或 xsimd 的程式碼
* `Numba <https://github.com/numba/numba>`_
    - 專注於 Python 在科學運算的部份
    - 只針對有加特定 decorator 的函式處理
    - 透過 Type Inference 推出型別後交給 LLVM JIT 優化
    - 支援 GPU
