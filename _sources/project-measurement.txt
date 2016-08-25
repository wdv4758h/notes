========================================
Project Measurement
========================================

(紀錄一些衡量專案的資訊)


General
========================================

* Testing 夠不夠多
* 是否有 Continuous Integration
* 註解夠不夠多
* 文件夠不夠多
* Community 是否活躍
* 支援的平台多不多 (x86_64/ARM/...)
* Coding Style 是否一致
* 版本控制的 Commit Message 是否清楚
* 編譯、執行、安裝方式有沒有寫清楚


C & C++
========================================

* 編譯參數是否嚴格
    - ``-Wall`` 是基本
    - ``-Wextra`` 開啟不包含在 ``-Wall`` 之內的參數
    - ``-pedantic`` 關閉 extension
    - ``-std=XXX`` 指定規範
    - ``-Werror`` 嚴格地把 Warning 當成 Error 處理
    - ``-D_FORTIFY_SOURCE=2``
* 使否使用 Sanitizer 或 Valgrind 做檢查
* Build System (CMake/Automake/...)



Reference
========================================

* `Neovim - Gradually introduce more compiler flags <https://github.com/neovim/neovim/issues/343>`_
