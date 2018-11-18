========================================
利用 GStreamer 模擬常見指令
========================================


.. contents:: 目錄


cp
========================================

.. code-block:: sh

    gst-launch-1.0 -q filesrc location=$SOURCE ! filesink location=$TARGET

    gst_cp() {
      gst-launch-1.0 -q filesrc location=$1 ! filesink location=$2
    }


.. code-block:: sh

    gst_hexdump() {
      gst-launch-1.0 -q filesrc location=$1 ! fakesink dump=1
    }
