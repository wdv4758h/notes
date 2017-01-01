========================================
proxychains
========================================

:Repo: https://github.com/rofl0r/proxychains-ng


.. contents:: 目錄


基本使用
========================================

.. code-block:: sh

    # Origin
    wget -qO- https://wtfismyip.com/text

    # After
    # need edit /etc/proxychains.conf for setting
    proxychains wget -qO- https://wtfismyip.com/text
