========================================
Servo
========================================


.. contents:: 目錄


編譯
========================================

.. code-block:: sh

    # 依需求選擇編 release 或 dev
    # 可以加上 -j <NUM> 參數來使用多核心編譯
    ./mach build -r -j4     # release
    ./mach build -d -j4     # dev


打包編譯結果
========================================

要跑起 Servo 需要的是：

* 編譯完的 ``servo`` 執行檔（會在 ``target/release/servo`` ）
* resources 資料夾（在 ``https://github.com/servo/servo/tree/master/resources/`` ）

有這兩項資料就可以跑起 Servo，
但是如果要跑 ``Browser.html`` 的話還需要額外的資料：

* 一些 ``HTML/CSS/JavaScript/PNG/...`` （在 ``target/release/build/browserhtml-*/out/`` ）


.. code-block:: sh

    rm -rf servo-prebuilt
    mkdir servo-prebuilt
    cd servo-prebuilt
    cp ../target/release/servo ./
    cp -r ../resources/ ./
    cp -r ../target/release/build/browserhtml-*/out/ ./browserhtml
    cd ../
    tar Jcvf servo-prebuilt.tar.xz servo-prebuilt/


直接使用 Servo 專案內建的指令：

.. code-block:: sh

    ./mach package -r   # release
    ./mach package -d   # dev


執行
========================================

一般（非 ``Browser.html`` ）：

.. code-block:: sh

    ./servo URL_or_HTML


``Browser.html`` ：

.. code-block:: sh

    ./servo ./browserhtml/index.html


Servo 還有許多參數可以選擇，
自行去 ``./servo --help`` 中尋找、選用。



測試
========================================

所有更動都需要跑的程式風格檢查：

.. code-block:: sh

    ./mach test-tidy



指定特定的 unit （以 ``components/net/`` 為例）：

.. code-block:: sh

    ./mach test-unit -p net


W3C 的 Web Platform Tests ：

.. code-block:: sh

    # 全部的 WPT
    ./mach test-wpt

    # XMLHttpRequest 內的 WPT
    ./mach test-wpt tests/wpt/web-platform-tests/XMLHttpRequest/

    # 單一一個 WPT
    ./mach test-wpt tests/wpt/web-platform-tests/XMLHttpRequest/formdata-foreach.html


要加入新的 WPT 需要更改 ``tests/wpt/metadata/MANIFEST.json`` ，
如果要標明特定測試為「預期會失敗」的話，
須在底下對應的地方加上設定檔，
例如： ``tests/wpt/metadata/XMLHttpRequest/formdata-foreach.ini`` ，
內容範例：

.. code-block:: ini

    [formdata-foreach.html]
      type: testharness
        [Default iterator should see duplicate keys]
          expected: FAIL

        [Default iterator should see non-deleted values]
          expected: FAIL

        [entries() iterator should see duplicate keys]
          expected: FAIL

        [entries() iterator should see non-deleted values]
          expected: FAIL

        [keys() iterator should see duplicate keys]
          expected: FAIL

        [values() iterator should see non-deleted values]
          expected: FAIL



架構
========================================

瀏覽器提供給 JavaScript 使用的 methods 會用 ``WebIDL`` 定義，
Servo 中視放在 ``components/script/dom/webidls/`` 內，
裡面的 ``WebIDL`` 幾乎都來自 W3C 的規範。


DOM (Document Object Model)
------------------------------

DOM 是由 WebIDL 定義成的界面，
在 Servo 中以 Rust struct 的方式實做。

Servo 的 DOM 會含有兩個不同但相關連的資料：

* DOM object：標有 ``#[dom_struct]`` 的 Rust struct instance，在 Heap 上
* reflector：由 SpiderMonkey 控管的 ``JSObject`` ，其為 DOM object 的擁有者

相關結構：

* ``Root`` smart pointer
* ``JS`` 、 ``MutNullableHeap`` 、 ``MutHeap`` smart pointers
* ``trace`` 實做
* ``Trusted`` smart pointer


WebGL
------------------------------

資料

* `Fully implement WebGL 1.0 <https://github.com/servo/servo/issues/10209>`_
* WebGL 1.0 spec
* GLES 2.0 spec


Bots
========================================

Servo 無論在 GitHub 還是在 IRC 上都有使用機器人，
以下是相關列表：

* `crowbot <https://github.com/servo/crowbot>`_
    - 在 ``#servo`` IRC 上（ ``irc.mozilla.org`` ）
* `highfive <https://github.com/servo/highfive>`_
    - 在 GitHub 上
    - 會指定 reviewer
    - 會更新 PR 的 label
    - 會對新發的 PR 做檢查來標出更動檔案的負責人
* `bors <https://github.com/servo/bors>`_
    - 在 GitHub 上
    - 在 maintainer 同意後會去做 PR 的完整測試
    - 測試通過後會排程自動 merge



參考
========================================

官方資料
------------------------------

* `Hacking Servo - Quickstart <https://github.com/servo/servo/blob/master/docs/HACKING_QUICKSTART.md#hacking-servo---quickstart>`_
* `Servo's directory structure <https://github.com/servo/servo/blob/master/docs/ORGANIZATION.md>`_
* `Servo Starters - a list of easy tasks that are good for beginners to rust or servo <https://starters.servo.org/>`_
* [2015] `Experience Report: Developing the Servo Web Browser Engine using Rust <https://arxiv.org/abs/1505.07383>`_


其他
------------------------------

* `Servo 中文開發者社群 <https://www.facebook.com/groups/608787195932135/>`_
