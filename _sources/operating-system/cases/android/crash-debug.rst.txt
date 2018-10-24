========================================
Android Process Crash Debug
========================================


.. contents:: 目錄


Tombstone
========================================

在 Android 系統中，
如果 process 整個 crash 死亡，
系統會幫它建墓碑，
墓碑會放在 ``/data/tombstones/`` 資料夾，
裡面會有 0 ~ 9 共十個墓碑，
當有超過十個 process 都 crash 時，
墓碑裡的資料會被新的覆蓋。
墓碑裡是存文字檔案，
會儲存 process 的整個記憶體狀況，
包含讀進來的 shared library 或是相關執行的 symbol，
後續可以用工具整理分析問題。

要知道自己的 process 被分配到哪個 tombstone 可以用 logcat 尋找，
logcat 中尋找關鍵字 ``Fatal`` 就是有 process crash 發生，
接下來也會輸出正在使用的 tombstone。



ndk-stack
========================================

在 Android NDK 中有個工具叫 ``ndk-stack`` ，
可以用來輔助分析 tombstone，
使用方法如下：

.. code-block:: sh

    ndk-stack -sym <root_folder_for_symbols> -dump <tombstonefile>

指定好要使用的資料夾後，
``ndk-stack`` 會去整理 tombstone 裡的 call stack，
並且根據 address 所在的 library 去指定的資料夾內搜尋，
從中找到 library 並讀取相關 symbol，
最後輸出整理過的結果。



addr2line
========================================

``addr2line`` 可以用來把某個記憶體位置轉成有意義的 symbol，
例如：

.. code-block:: sh

    aarch64-linux-android-addr2line -f -e lib/libglib-2.0.so 00000000000cdab4
