========================================
Streaming Compilation
========================================


.. contents:: 目錄


介紹
========================================

Streaming Compilation 指的是程式碼還沒完全讀完就開始做後續的處理，
這樣的技術在網頁瀏覽器的實做上會用到，
JavaScript 還沒完全傳完就開始 Parsing，
減少需要的 load time。



參考
========================================

* `New JavaScript techniques for rapid page loads <https://blog.chromium.org/2015/03/new-javascript-techniques-for-rapid.html>`_
* `Where is WebAssembly now and what’s next? <https://hacks.mozilla.org/2017/02/where-is-webassembly-now-and-whats-next/>`_
    - recent additions to the JavaScript API will allow streaming compilation of WebAssembly
