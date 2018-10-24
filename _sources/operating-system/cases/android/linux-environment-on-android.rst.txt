========================================
Linux environment on Android
========================================


.. contents:: 目錄


基本環境
========================================

Android 系統預設的 library 路徑通常會在：

* /system/lib/
* /system/lib64/
* /vendor/lib/
* /vendor/lib64/


可以使用 LD_LIBRARY_PATH 和 LD_PRELOAD 來加入額外的 library。



Termux
========================================

:Repo: https://github.com/termux
:Site: https://termux.com/

Termux 是在 Android 系統上建立 Linux 環境的專案，
`Termux packages <https://github.com/termux/termux-packages>`_
裡面支援多種常見專案的編譯設定。



Android 套件移植常見問題
========================================

* 編譯設定有問題，嘗試連結到 host 上的 library，造成 linker 失敗
* Android 的 bionic libc 沒有 iconv 和 gettext/libintl 支援
* 沒有 SYSV semaphores 支援
* 沒有 SYSV shared memory 支援，但是可以使用 `libandroid-shmem <https://github.com/termux/libandroid-shmem>`_ ，藉由 Android 的 ashmem 模擬
* Android linker 只支援 PIE (Position Independent Executables) 執行檔
    - Jelly Bean 加入 PIE 支援
    - Lollipop 移除 non-PIE 支援
* 某些 DT entry 不支援，會造成 linker 在執行期間噴許多 warning，可以用工具幫忙清理 binary
