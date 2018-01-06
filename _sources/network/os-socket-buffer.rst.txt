========================================
OS socket buffer
========================================


.. contents:: 目錄


Linux
========================================

看現在的設定：

.. code-block:: sh

    # 資料都在 /proc/sys/net/
    $ sysctl net.ipv4.udp_mem
    $ sysctl net.ipv4.udp_rmem_min
    $ sysctl net.ipv4.udp_wmem_min
    $ sysctl net.core.rmem_max


調整設定（重新啟動後會回復本來的設定）：

.. code-block:: sh

    sysctl -w net.ipv4.udp_mem='65536 131072 262144'
    sysctl -w net.ipv4.udp_rmem_min='16384'
    sysctl -w net.ipv4.udp_wmem_min='16384'
