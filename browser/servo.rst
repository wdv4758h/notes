========================================
Servo
========================================


.. contents:: 目錄


編譯
========================================

.. code-block:: sh

    # 依需求選擇編 release 或 debug
    ./mach build -r     # release
    ./mach build -d     # debug



打包編譯結果
========================================

要跑起 Servo 需要的是：

* 編譯完的 `servo` 執行檔（會在 `target/release/servo` ）
* resources 資料夾（在 `https://github.com/servo/servo/tree/master/resources/` ）

有這兩項資料就可以跑起 Servo，
但是如果要跑 `Browser.html` 的話還需要額外的資料：

* 一些 `HTML/CSS/JavaScript/PNG/...` （在 `target/release/build/browserhtml-*/out/` ）


.. code-block:: sh

    mkdir servo-prebuilt
    cd servo-prebuilt
    cp ../target/release/servo ./
    cp -r ../resources/ ./
    cp -r ../target/release/build/browserhtml-*/out/ ./browserhtml



執行
========================================

一般（非 `Browser.html` ）：

.. code-block:: sh

    ./servo URL_or_HTML


`Browser.html` ：

    ./servo ./browserhtml/index.html


Servo 還有許多參數可以選擇，
自行去 `./servo --help` 中尋找、選用。



參考
========================================

* `Experience Report: Developing the Servo Web Browser Engine using Rust <https://kmcallister.github.io/papers/2015-servo-experience-report-draft1.pdf>`_
* `Servo 中文開發者社群 <https://www.facebook.com/groups/608787195932135/>`_
* `Hacking Servo for noobs. <https://gist.github.com/paulrouget/2f00941e6e82aeecad23>`_
