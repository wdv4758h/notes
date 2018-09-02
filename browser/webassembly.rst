========================================
WebAssembly
========================================


.. contents:: 目錄


基本介紹
========================================

WebAssembly 的目標是網頁程式可以執行地更有效率，
方向有點像先前的 asm.js，
但 WebAssembly 做的更底層，
規範也由各大瀏覽器開發商（Mozilla、Google、Apple、Microsoft）共同訂定。
WebAssembly 可以當作一個低階的 IR，
這個 IR 會由編譯器產生，
目前已經有數個編譯器在實做相關的支援。

對於 WebAssembly 這樣執行在網頁的程式來說，
沒有「Program」和「Library」之分，
所以會直接稱為「Module」。





WebAssembly 的幾種形式：

* s-expressions
* binary encoding


* `Textual Representation <https://github.com/WebAssembly/design/blob/master/TextFormat.md>`_
* `Binary Encoding <https://github.com/WebAssembly/design/blob/master/BinaryEncoding.md>`_


* [2016/10] `WebAssembly Browser Preview <https://hacks.mozilla.org/2016/10/webassembly-browser-preview/>`_



參考
========================================

Misc
------------------------------

* `WebAssembly <http://webassembly.org/>`_
* `Introduction to WebAssembly <https://rsms.me/wasm-intro>`_
* `What is WebAssembly ? The Dawn of a New Era <https://medium.com/javascript-scene/what-is-webassembly-the-dawn-of-a-new-era-61256ec5a8f6>`_
* `Why we Need WebAssembly ? An Interview with Brendan Eich <https://medium.com/javascript-scene/why-we-need-webassembly-an-interview-with-brendan-eich-7fb2a60b0723>`_
* `A first look at WebAssembly performance <http://www.stefankrause.net/wp/?p=405>`_
* [2015] `Emscripten and WebAssembly <https://kripken.github.io/talks/wasm.html>`_
* [GitHub] `WebAssembly/design <https://github.com/WebAssembly/design>`_
* `Previewing the WebAssembly Explorer <https://hacks.mozilla.org/2017/03/previewing-the-webassembly-explorer/>`_
* `WebAssembly Code Explorer <https://wasdk.github.io/wasmcodeexplorer/>`_
* `JavaScript Start-up Performance <https://medium.com/@addyosmani/javascript-start-up-performance-69200f43b201>`_
* `Optimizing WebAssembly Startup Time | Inside PSPDFKit <https://pspdfkit.com/blog/2018/optimize-webassembly-startup-performance/>`_


Benchmark
------------------------------

* `PSPDFKit - A Real-World WebAssembly Benchmark <https://pspdfkit.com/blog/2018/a-real-world-webassembly-benchmark/>`_


實做
------------------------------

* `Making WebAssembly even faster: Firefox’s new streaming and tiering compiler <https://hacks.mozilla.org/2018/01/making-webassembly-even-faster-firefoxs-new-streaming-and-tiering-compiler/>`_
* `Liftoff: a new baseline compiler for WebAssembly in V8 <https://v8project.blogspot.com/2018/08/liftoff.html>`_
