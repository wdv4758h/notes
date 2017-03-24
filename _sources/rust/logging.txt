========================================
Logging
========================================


.. contents:: 目錄


介紹
========================================

Logging 是撰寫程式不可或缺的一塊，
藉由劃分不同層級的 log 可以在適當的時候提供訊息，
在除錯方面也可以切換 log 顯示層級後馬上看相關資訊，
而不用自己額外新增和刪除 stdout 輸出。

而在 Logging 這塊 Rust 官方已經有良好的抽象化，
官方有個 crate 就叫 `log <https://github.com/rust-lang-nursery/log>`_ ，
專案目的為提供統一的 logging API，
抽象化各 logging 的實作，
libraries 可以用這個 API 來撰寫，
而在使用 libraries 做出執行檔時，
可以選擇適合自己的 logging 實作，
藉此達到統一的 logging 機制，
如此一來不管是 logging 程式碼的統一性還是 logger 抽換的方便度都很高。


所以狀況會分為：

* libraries：只使用 ``log`` 這個套件
* 執行檔：需選擇要使用的 logging 實作


如果沒提供 logging 實作的話，
會 fallback 回 noop 實作，
此時會忽略所有 log 資訊，
除去 overhead。

層級（使用時當作 ``println!`` 在使用）：

* error!
* warn!
* info!
* debug!
* trace!

如果想要在 release build 可以完全沒有 overhead 的話可以用 ``release_max_level_off`` feature，
如此一來 ``log`` 相關的功能都會被編譯器優化掉，
產生的執行檔會跟沒有使用 ``log`` 相同。

除此之外還有其他層級可選擇，
在設定的層級之外的 logging 程式碼都會在編譯時期被優化掉：

* release_max_level_off
* release_max_level_error
* release_max_level_warn
* release_max_level_info
* release_max_level_debug
* release_max_level_trace

另外也有適用於所有 build 的選項
（release build 以 ``release_max_level_*`` 為優先）：

* max_level_off
* max_level_error
* max_level_warn
* max_level_info
* max_level_debug
* max_level_trace


而對於不使用 ``std`` 的專案，
``log`` 也提供了解決方案，
預設是會開啟 ``use_std`` 這 feature，
但是可以在 ``Cargo.toml`` 使用 ``default-features = false`` 來關閉，
如此一來就不需依賴於 ``std`` 。


開啟特定層級的 log：

.. code-block:: sh

    $ RUST_LOG=mylib=info ./myapplication



env_logger
========================================
