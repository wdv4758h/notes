========================================
Rust to WebAssembly
========================================


.. contents:: 目錄


WebAssembly 介紹
========================================

特色：

* 安全
* 快速
* 可攜性高


WebAssembly Runtime/Compiler：

* `Wasmer <https://github.com/wasmerio/wasmer>`_
    - based on Cranelift/DynASM/LLVM
    - written in Rust
    - JIT
* `wasmtime <https://github.com/CraneStation/wasmtime>`_ (by Mozilla)
    - based on Cranelift
    - written in Rust
    - JIT
* `Lucet <https://github.com/fastly/lucet/>`_ (by Fastly)
    - based on Cranelift
    - written in Rust
    - AOT
* `wasmi <https://github.com/paritytech/wasmi>`_ (by Parity)
    - written in Rust
* `WAMR (WebAssembly Micro Runtime) <https://github.com/intel/wasm-micro-runtime>`_ (by Intel)
    - written in C
* `wasmjit <https://github.com/rianhunter/wasmjit>`_
    - written in C
    - JIT


界面：

* `WASI: system interface for the WebAssembly <https://wasi.dev/>`_


相關工具：

* `wrangler <https://github.com/cloudflare/wrangler>`_
    - CLI 工具
    - 把 Rust 生出的 WebAssembly 布署到 Cloudflare Workers
* WebAssembly -> Rust
    - https://github.com/CryZe/wasm-to-rust
* WebAssembly -> WebAssembly
    - https://github.com/rustwasm/walrus
* Dynamic Analysis framework for WebAssembly
    - http://wasabi.software-lab.org/
    - https://github.com/danleh/wasabi


文件：

* https://rustwasm.github.io/docs.html
* https://rustwasm.github.io/book/
* https://rustwasm.github.io/docs/wasm-bindgen/
* https://github.com/rustwasm/awesome-rust-and-webassembly



Rust 對 WebAssembly 的生態圈
========================================

* `wasm-bindgen <https://github.com/rustwasm/wasm-bindgen>`_
    - Rust <-> JavaScript 雙向溝通橋樑
* `js-sys <https://github.com/rustwasm/wasm-bindgen/tree/master/crates/js-sys>`_
    - 基於 ``wasm-bindgen`` 實做所有全域 JavaScript API 的 binding，包含所有 ECMAScript 標準內的 API
    - 不包含 Web 或 Node 的 API
* `web-sys <https://github.com/rustwasm/wasm-bindgen/tree/master/crates/web-sys>`_
    - 基於 ``wasm-bindgen`` 實做所有 Web 相關的 API，例如 WebGL、WebRTC、...
    - 基於 WebIDL 定義來產生實做
    - 可以操作 DOM
* `wasm-pack <https://github.com/rustwasm/wasm-pack>`_
    - Rust 的 WebAssembly 編譯、打包工具
* `Twiggy <https://github.com/rustwasm/twiggy>`_
    - 分析 WebAssembly 內是誰在佔用大量空間
* `wasm-snip <https://github.com/rustwasm/wasm-snip>`_
    - WebAssembly 手動瘦身工具
    - 有時候編譯器還不夠聰明到可以在編譯時期證明函式用不到，因此不能自動清除乾淨，這工具可以手工清理
    - 針對已經產生的 WebAssembly 除去用不到的函式實做，把實做換成 ``unreachable`` ，藉此降低檔案大小
* `wee_alloc <https://github.com/rustwasm/wee_alloc>`_
    - 針對 WebAssembly 使用情境優化的 Memory Allocator
* `walrus <https://github.com/rustwasm/walrus>`_
    - WebAssembly 轉 WebAssembly 的處理套件
    - 可以用於其他工具內
* `gloo <https://github.com/rustwasm/gloo>`_
    - Web 相關應用工具



基本開發流程
========================================

.. code-block:: sh

    # 直接下載包好的工具 wasm-pack，它大致上會處理以下事情：
    # 1. "rustup target add wasm32-unknown-unknown"
    # 2. "cargo build --target wasm32-unknown-unknown"
    # 3. wasm-bindgen
    curl https://rustwasm.github.io/wasm-pack/installer/init.sh -sSf | sh

    # 編譯 Rust 專案成 WebAssembly
    cd my-project/
    wasm-pack build

    # 建立 NPM 的 WebAssembly 專案
    # https://github.com/rustwasm/create-wasm-app
    npm init wasm-app www
    # https://github.com/rustwasm/rust-webpack-template
    # npm init rust-webpack my-app
    # https://github.com/rustwasm/rust-parcel-template
    # npm init rust-parcel my-app
    cd www/
    npm install

    # 讓 NPM 認識我們的 Rust 專案
    cd ../pkg
    mkdir ~/.npm-global
    npm config set prefix '~/.npm-global'
    npm link

    # 指定要把我們的 Rust 專案加入相依套件
    cd ../www
    npm link my-project

    # 調整 JavaScript 來呼叫我們在 Rust 實做的函式
    sed -i "s/hello-wasm-pack/my-project/" index.js
    sed -i "s/wasm.greet/wasm.myfunc/" index.js

    # 開 local server 測試
    npm run start
    npm run build

    # 優化檔案大小
    # https://rustwasm.github.io/book/reference/code-size.html
    #
    # (個人測試用專案：uuid)
    # 1. 開 LTO (lto = true)
    #       (個人測試用專案效果：60.8 KB -> 56.8 KB)
    # 2. 讓 LLVM 針對檔案大小去優化 (opt-level = 's')
    #       (個人測試用專案效果：56.8 KB -> 51.4 KB)
    # 3. 使用 wee_alloc 替代原本的 allocator
    #       (個人測試用專案效果：51.4 KB -> 48 KB)
    # 4. 使用 wasm-snip
    #   cargo install wasm-snip
    #   wasm-snip --snip-rust-panicking-code my-project.wasm -o output.wasm
    #       (個人測試用專案效果：48 KB -> 47.1 KB)
    # 5. 使用 wasm-opt 優化
    #   https://github.com/WebAssembly/binaryen
    #   wasm-opt my-project.wasm -o output.wasm
    #       (個人測試用專案效果：47.1 KB -> 41.1 KB)
    #   wasm-opt my-project.wasm --vacumm -o output.wasm
    #       (個人測試用專案效果：47.1 KB -> 40.6 KB)
    #   wasm-opt my-project.wasm --vacumm --strip-producers -o output.wasm
    #       (個人測試用專案效果：47.1 KB -> 40.4 KB)
    #   wasm-opt my-project.wasm -Os -o output.wasm
    #       (個人測試用專案效果：47.1 KB -> 33.8 KB)

    # twiggy
    twiggy top my-project.wasm
    twiggy dominators my-project.wasm



取代既有 JavaScript 工具
========================================

* Babel (JavaScript to JavaScript transpiler)
    - `swc (speedy web compiler) <https://github.com/swc-project/swc>`_
* Webpack
    - `Pax <https://github.com/nathan/pax>`_



相關專案
========================================

* `wasm-flate <https://github.com/drbh/wasm-flate>`_



參考
========================================

* `The Rust and WebAssembly Book <https://rustwasm.github.io/book/>`_
* `This week in Rust and WebAssembly <https://rustwasm.github.io/>`_
* `Awesome WASM <https://github.com/mbasso/awesome-wasm>`_


* From Rust to beyond - Ivan Enderlin
    - `Prelude <https://mnt.io/2018/08/21/from-rust-to-beyond-prelude/>`_
    - `The WebAssembly galaxy <https://mnt.io/2018/08/22/from-rust-to-beyond-the-webassembly-galaxy/>`_
    - `The ASM.js galaxy <https://mnt.io/2018/08/28/from-rust-to-beyond-the-asm-js-galaxy/>`_
    - `The C galaxy <https://mnt.io/2018/09/11/from-rust-to-beyond-the-c-galaxy/>`_
    - `The PHP galaxy <https://mnt.io/2018/10/29/from-rust-to-beyond-the-php-galaxy/>`_



* `Compiling Rust to your Browser <http://rust.cologne/2016/09/05/compile-to-js.html>`_
* `Compiling Rust to your Browser - Examples <http://www.hellorust.com/emscripten/>`_
* `Rust Meetup Cologne (2016-09-05): Jan-Erik Rediger - Compiling Rust to asm.js <https://www.youtube.com/watch?v=bvJCMhJ3RnQ>`_
* `mir2wasm - An experimental compiler from Rust to WebAssembly <https://github.com/brson/mir2wasm/>`_
* `Compiling to WebAssembly with Binaryen <https://kripken.github.io/talks/binaryen.html>`_
* `Compiling to the web with Rust and emscripten <https://users.rust-lang.org/t/compiling-to-the-web-with-rust-and-emscripten/7627>`_
* `Rust implementation of TodoMVC with Emscripten <https://github.com/tcr/rust-todomvc>`_
* `rust-webplatform - A Rust library for use with emscripten to access the DOM <https://github.com/tcr/rust-webplatform>`_
* `SIMD.js <https://tc39.github.io/ecmascript_simd/>`_

* `Haskell Wiki - The JavaScript Problem <https://wiki.haskell.org/The_JavaScript_Problem>`_

* `rust-wasm <https://github.com/rust-lang-nursery/rust-wasm>`_
* `Hello wasm-pack! – Mozilla Hacks – the Web developer blog <https://hacks.mozilla.org/2018/04/hello-wasm-pack/>`_
* `Rust stdweb - A standard library for the client-side Web <https://github.com/koute/stdweb>`_


* `WASM: Universal Application Runtime - Cybernetist <https://cybernetist.com/2019/04/25/wasm-universal-application-runtime/>`_



* `Awesome WASM <https://github.com/mbasso/awesome-wasm>`_
