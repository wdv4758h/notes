========================================
Anbox - 在 GNU/Linux 上執行 Android 系統
========================================


.. contents:: 目錄


介紹
========================================



編譯與安裝
========================================



使用
========================================

.. code-block:: sh

    sudo modprobe binder_linux
    sudo modprobe ashmem_linux
    sudo systemctl start anbox-container-manager.service

.. code-block:: sh

    anbox launch --package=org.anbox.appmgr --component=android.intent.action.VIEW



安裝 Google Play
========================================

https://github.com/anbox/anbox/issues/118



相關問題
========================================

* 目前需要把 boost 降級到 1.65.1 才能執行 ``anbox``
* 目前需要把 mesa 降級到 17.0.5 才能讓執行更順暢
    - 和後來加入的 ``EGL_ANDROID_native_fence_sync`` 相關
    - https://github.com/anbox/anbox/issues/437#issuecomment-348470547
* Arch Linux 上預設的資料夾會在 ``/var/lib/anbox/rootfs/``



參考
========================================

* `Anbox - container-based approach to boot a full Android system on a regular GNU/Linux system <https://github.com/anbox/anbox>`_
