========================================
Vim/Neovim Tips
========================================


.. contents:: 目錄


直接編輯指令的輸出
========================================

.. code-block:: sh

    SOME_CMD | vim -

.. code-block:: sh

    ls | vim -
    nm -g librure.so | rg -v ' [tbrdw] ' | vim -
    nm -Pg librure.so | vim -
    readelf -Ws librure.so | vim -
