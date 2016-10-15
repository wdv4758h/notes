========================================
Rust to asm.js
========================================


.. contents:: 目錄


前置作業
========================================

.. code-block:: sh

    # asm.js
    rustup target add asmjs-unknown-emscripten

    # wasm
    rustup target add wasm32-unknown-emscripten

    # Emscripten
    curl -O https://s3.amazonaws.com/mozilla-games/emscripten/releases/emsdk-portable.tar.gz
    tar -xzf emsdk-portable.tar.gz
    source emsdk_portable/emsdk_env.sh
    emsdk update
    emsdk install sdk-incoming-64bit
    emsdk activate sdk-incoming-64bit



簡單範例
========================================

Hello World
------------------------------

程式碼：

.. code-block:: rust

    // hello.rs

    fn main() {
        println!("Hello World!");
    }


編譯：

.. code-block:: sh

    rustc --target=asmjs-unknown-emscripten hello.rs


執行：

.. code-block:: sh

    $ node hello.js
    Hello World!


Fibonacci
------------------------------

程式碼：

.. code-block:: rust

    #![feature(link_args)]

    #[link_args = "-s EXPORTED_FUNCTIONS=['_fib']"]
    extern {}

    fn main() {}

    #[no_mangle]
    pub extern fn fib(n: u32) -> u32 {
        if n < 2 {
            n
        } else {
            fib(n-1) + fib(n-2)
        }
    }


編譯：

.. code-block:: sh

    rustc --target=asmjs-unknown-emscripten fib.rs


執行：

.. code-block:: sh

    $ node
    > var fib = require('./fib.js');
    undefined
    > fib
    [Emscripten Module object]
    > fib._fib
    [Function]
    > console.log(fib._fib.toString())
    function () {
    assert(runtimeInitialized, 'you need to wait for the runtime to be ready (e.g. wait for main() to be called)');
    assert(!runtimeExited, 'the runtime was exited (use NO_EXIT_RUNTIME to keep it alive after main() exits)');
    return real__fib.apply(null, arguments);
    }
    > fib._fib(5)
    5
    > fib._fib(6)
    8
    > fib._fib(7)
    13



參考
========================================

* `Compiling Rust to your Browser <http://rust.cologne/2016/09/05/compile-to-js.html>`_
* `Rust Meetup Cologne (2016-09-05): Jan-Erik Rediger - Compiling Rust to asm.js <https://www.youtube.com/watch?v=bvJCMhJ3RnQ>`_
* `mir2wasm - An experimental compiler from Rust to WebAssembly <https://github.com/brson/mir2wasm/>`_
* `Compiling to WebAssembly with Binaryen <https://kripken.github.io/talks/binaryen.html>`_
* `Compiling to the web with Rust and emscripten <https://users.rust-lang.org/t/compiling-to-the-web-with-rust-and-emscripten/7627>`_
* `Rust implementation of TodoMVC with Emscripten <https://github.com/tcr/rust-todomvc>`_
* `rust-webplatform - A Rust library for use with emscripten to access the DOM <https://github.com/tcr/rust-webplatform>`_
* `SIMD.js <https://tc39.github.io/ecmascript_simd/>`_
