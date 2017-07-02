========================================
JIT 相關資源
========================================


.. contents:: 目錄


文章
========================================

Lin Clark
------------------------------

* `A cartoon intro to WebAssembly <https://hacks.mozilla.org/2017/02/a-cartoon-intro-to-webassembly/>`_
    - 稍微帶一下 JavaScript 在加入 JIT 後的效能增進歷史
    - 作為後續主題的進入點
* `A crash course in just-in-time (JIT) compilers <https://hacks.mozilla.org/2017/02/a-crash-course-in-just-in-time-jit-compilers/>`_
    - 簡單的說明加圖示
    - 內容大概解釋 JIT 的運作和 Baseine comipler 與 Optimizing compiler，還有 bailing out 機制
* `A crash course in assembly <https://hacks.mozilla.org/2017/02/a-crash-course-in-assembly/>`_
    - CPU, ALU, registers, RAM, opcode, IR
* `Creating and working with WebAssembly modules <https://hacks.mozilla.org/2017/02/creating-and-working-with-webassembly-modules/>`_
    - IR to WebAssembly
    - ArrayBuffer，模擬系統上的 Heap
    - stack machine
    - http://mbebenita.github.io/WasmExplorer/
    - https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_objects/WebAssembly/Memory
    - https://developer.mozilla.org/en-US/docs/WebAssembly
    - https://rsms.me/wasm-intro
* `What makes WebAssembly fast? <https://hacks.mozilla.org/2017/02/what-makes-webassembly-fast/>`_
    - compact than JavaScript
    - has types (no more reoptimizing and bailing out)
    - more ideal for machines
    - no GC
* `Where is WebAssembly now and what’s next? <https://hacks.mozilla.org/2017/02/where-is-webassembly-now-and-whats-next/>`_
    - trampolining
    - streaming compilation
    - two-compiler system
    - post-MVP (Minimum Viable Product) features
        + Working directly with the DOM
        + Shared memory concurrency
            * SharedArrayBuffer
        + SIMD
        + Exception handling
        + interact with JavaScript's GC
        + ES6 Module integration
