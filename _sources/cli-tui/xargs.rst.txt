========================================
xargs
========================================


.. contents:: 目錄


範例
========================================

.. code-block:: sh

    find . -name '*.backup' | xargs rm -v
    find . -name "ffi.h" | xargs -I{} cp {} /opt/include/
