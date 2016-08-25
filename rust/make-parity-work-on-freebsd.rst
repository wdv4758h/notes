========================================
Make Parity work on FreeBSD
========================================


.. contents:: Table of Contents / 目錄


問題一 — nanomsg 無法編譯
========================================

TL;DR: 暫時不會解決，要先用自己的 fork

nanomsg 其實有支援 FreeBSD，
但是 ``ethcore/nanomsg.rs`` 的問題造成它無法在 FreeBSD 上編譯。
看了一下 GitHub 上的比對，
``ethcore/nanomsg.rs`` 跟原本的上游 ``thehydroimpulse/nanomsg.rs`` 比起來，
只多了 10 個 commits，上游卻多了 60 個 commits。
深入進去翻兩邊的 ``nanomsg_sys/build.rs`` 會發現，
上游的 ``nanomsg.rs`` 用 feature **bundled** 決定要動態連結還是靜態連結，
選擇靜態連結的話會叫起 ``CMake`` 去處理後續 ``nanomsg`` 的編譯，
選擇動態連結的話則會在系統的 Library 路徑尋找對應的 Shared Library，
找到後傳給 rustc 連結相關的參數。
然而 ``ethcore/nanomsg`` 這邊卻是自己在維護 ``nanomsg`` 的編譯，
把需要的 C 檔一個一個加入、編譯。
兩邊互相比較後，覺得直接跳回上游的 ``nanomsg.rs`` 會比較好，
可以不用額外維護各平台的編譯、可以選擇動態或靜態連結，
既達到 ``ethcore/nanomsg`` fork 出去所加的靜態連結，
又可以不用另外維護相同的專案！

可惜的是，在嘗試上游的 **bundled** feature 後，
發現它還是會動態連結到 ``libnanomsg.so`` ，
但是理論上應該已經不需要這麼做了，
所以就做了點修改，
讓使用 **bundled** 時不需要動態連結到 ``libnanomsg.so`` ，
此 `修改 <https://github.com/thehydroimpulse/nanomsg.rs/commit/c1e15a774c6a5750215f503c8e59077db11642b3>`_
已經送回上游。

* `thehydroimpulse/nanomsg.rs <https://github.com/thehydroimpulse/nanomsg.rs>`_
* `ethcore/nanomsg.rs <https://github.com/ethcore/nanomsg.rs>`_

（目前跟 ethcore 的開發者們討論後，
他們不想要上游 nanomsg 編譯時額外需要的 cmake，
所以目前他們想自己維護一套 nanomsg 的編譯 ...）



問題二 — mio 無法編譯
========================================

TL;DR: 等待新 release，要先用自己的 fork

第二個碰到的問題是 mio 無法在 FreeBSD 上編譯，
其中一個問題是編譯器對於 ``src/sys/unix/kqueue.c`` 內的 ``libc::timespec`` 處理有問題，
會出現 **mismatched types** 的錯誤，
但是這已經有 `PR <https://github.com/carllerche/mio/pull/448>`_ 處理，
而且在我試完的隔天就 merge 了 XD

還有一個是 mio 的相依套件 ``nix`` 在 FreeBSD 上也有問題，
但是已經在 `這個 commit <https://github.com/nix-rust/nix/commit/077d979acb57ecbd1dbe4c1a4b7b1449aa5a14d2>`_
修好了，
目前就等新 release 就可以了，
在那之前我先自己 fork ``mio`` 把 nix 改成使用 GitHub 上的版本，
接著再把 Parity 用的 mio 版本暫時更改成自己 fork 出去的。

其中更改到的部份有：

* 上游的 mio 本身（branch "v0.5.x"）
* ethcore/ws-rs （有用到 mio）（branch "mio-upstream-stable"）
* Parity 內指定的 mio 和 ws-rs



問題三 — rust-rocksdb 無法編譯
========================================

TL;DR: 已修好

RocksDB 其實有支援 FreeBSD，
但是 ``ethcore/rust-rocksdb`` 這 binding 卻沒有做好支援，
造成 FreeBSD 上編譯會失敗。
但是這修起來很簡單，
只要在 ``rocksdb-sys/build.rs`` 加上短短幾行就可以了（感謝 RocksDB 的支援）：

.. code-block:: rust

    if cfg!(target_os = "freebsd") {
        config.define("OS_FREEBSD", Some("1"));
    }

（此修改已經送回 ``ethcore/rust-rocksdb`` ）

* `ethcore/rust-rocksdb <https://github.com/ethcore/rust-rocksdb>`_



問題四 — Parity - url.rs - open 無法編譯
========================================

TL;DR: 已修好

Parity 中有個部份會使用到系統的 ``open`` 或 ``xdg-open`` 指令，
但是這邊沒寫好 FreeBSD 要用哪個，
所以編譯不會過，
簡單加上 ``target_os`` 的判斷即可解決。



跑測試確認功能
========================================

.. code-block:: sh

    cargo test



成果
========================================

終於， ``Parity`` 可以在 FreeBSD 上正常編譯執行了！
這一連串的狀況其實都是小問題，
其實底下的工具都有支援 FreeBSD，
只是在包的時候沒處理好，
造成編譯問題，
簡單修改後就可以把問題解決！
