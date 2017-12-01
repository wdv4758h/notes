========================================
Firefox
========================================


.. contents:: 目錄


隱私設定
========================================

* about:preferences#privacy
    - Tracking Protection
        + Use Tracking Protection to block trackers
            * Always
            * Change Block Lists
                - strict protection
        + Send "Do Not Track"
            * Always

* `Firefox Multi-Account Containers <https://addons.mozilla.org/zh-TW/firefox/addon/multi-account-containers/>`_
    - 不同網站切開到不同 Container
    - 個人範例：
        + Default （用過就丟，沒什麼登入）
        + Google
        + Twitter
        + GitHub
        + Bank
        + Shopping

* `uBlock Origin <https://addons.mozilla.org/en-US/firefox/addon/ublock-origin/>`_



Gecko
========================================

設定
------------------------------

* about:support
* about:config
* about:networking
* about:memory
* about:performance



SpiderMonkey (JavaScript 引擎)
========================================



Quantum
========================================

`Quantum <https://wiki.mozilla.org/Quantum>`_
是 Mozilla 的一個大計畫，
要基於現有的 Gecko 整合 Servo 的成果進去，
藉此來改善效能、更好地平行化和善用 GPU。


Quantum CSS (Stylo)
------------------------------

`Stylo <https://wiki.mozilla.org/Quantum/Stylo>`_
這專案目標是整合 Servo 的 CSS style system 到 Gecko，
藉此可以平行化地處理 CSS style。
目前仍在 Firefox Nightly 中，
可以開啟 ``about:support`` 確認 Stylo 是開的，
或者進 ``about:config`` 把 ``layout.css.servo.enabled`` 打開。


* `Inside a super fast CSS engine: Quantum CSS (aka Stylo) <https://hacks.mozilla.org/2017/08/inside-a-super-fast-css-engine-quantum-css-aka-stylo/>`_


Quantum DOM
------------------------------

`Quantum DOM <https://wiki.mozilla.org/Quantum/DOM>`_


Quantum Render
------------------------------

`Quantum Render <https://wiki.mozilla.org/Platform/GFX/Quantum_Render>`_
這專案目標是整合 Servo 的 WebRender 到 Gecko，
藉此可以更妥善地運用 GPU 來幫助來渲染網頁。
目前仍在 Firefox Nightly 中，
可以進 ``about:config`` 把 ``gfx.webrender.enabled`` 打開。


* `Mozilla Gfx Team Blog <https://mozillagfx.wordpress.com/>`_


Quantum Compositor
------------------------------

Quantum Compositor
這專案的目標是把 Gecko 的 compositor 移到自己的 process，
藉此來降低瀏覽器掛掉的機率。


Quantum Flow
------------------------------

`Quantum Flow <https://wiki.mozilla.org/Quantum/Flow>`_
這專案目標是改善瀏覽器的使用者體驗，
讓使用者感受更順暢，
內容是跨元件地，
會多方下手。


* `Quantum Flow Engineering Newsletter <https://ehsanakhgari.org/tag/quantumflow>`_


Quantum Network
------------------------------

Quantum Network
目標是要改善瀏覽器的 network stack。

RCWN 是讓 local cache 和網路比看哪個資料拿的比較快，
可以進 ``about:config`` 把 ``network.http.rcwn.enabled`` 打開。



Firefox Focus
========================================



參考
========================================

* `Firefox Browser Architecture <https://mozilla.github.io/firefox-browser-architecture/>`_

----

* `Are We Fast Yet? <https://arewefastyet.com/>`_
* `Are we e10s yet? <https://arewee10syet.com/>`_
* `Are we WebExtensions yet? <http://arewewebextensionsyet.com/>`_
* `Are they slim yet, round 2 <http://www.erahm.org/2017/03/10/are-they-slim-yet-round-2/>`_
* `Tracelogger graph - a tool in the SpiderMonkey JS engine that can make execution traces <https://github.com/h4writer/tracelogger>`_
* `MDN - SpiderMonkey <https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey>`_

----

* `JavaScript runtime: Call Stack and Event Queue - Part 1 <https://curlybrackets.com/posts/43130>`_
* `JavaScript runtime: Call Stack and Event Queue - Part 2 <https://curlybrackets.com/posts/43131>`_
* `JavaScript runtime: Call Stack and Event Queue - Part 3 <https://curlybrackets.com/posts/43132>`_
* `JavaScript runtime: Call Stack and Event Queue - Part 4 <https://curlybrackets.com/posts/43133>`_
* `JavaScript runtime: Call Stack and Event Queue - Part 5 <https://curlybrackets.com/posts/43134>`_

* `Finding memory leaks <http://gent.ilcore.com/2011/08/finding-memory-leaks.html>`_
* `Javascript memory optimization and texture loading <http://blog.tojicode.com/2012/03/javascript-memory-optimization-and.html>`_
* `PageSpeed Insights - Optimizing JavaScript code <https://developers.google.com/speed/articles/optimizing-javascript>`_
* `Understanding V8 - Vyacheslav Egorov <http://mrale.ph/s3/nodecamp.eu/>`_
* `Daniel Clifford - V8 Performance Tuning Tricks <https://mkw.st/p/gdd11-berlin-v8-performance-tuning-tricks/>`_
* `V8 Resources <http://mrale.ph/v8/resources.html>`_
* `I want to optimize my JS application on V8 checklist <http://mrale.ph/blog/2011/12/18/v8-optimization-checklist.html>`_
* `Handcrafting VMs for dynamic languages - reality and dreams <https://docs.google.com/presentation/d/1boYUAQZjrRgk6tazlPmtDXJ9Dg2QDbodqfXaUbqA6do/present>`_
* `Jay Conrod - A tour of V8 <http://jayconrod.com/tags/v8>`_
