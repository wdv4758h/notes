========================================
Branch Prediction Hint
========================================

LLVM Branch Weight Metadata
========================================

* `LLVM Branch Weight Metadata <http://llvm.org/docs/BranchWeightMetadata.html>`_
    - ``__builtin_expect``


Linux Kernel Macro
========================================

.. code-block:: c

    #define likely(x)      __builtin_expect(!!(x), 1)
    #define unlikely(x)    __builtin_expect(!!(x), 0)

``#define likely(x) (x)`` on compilers that don't support the ``__builtin_expect``
