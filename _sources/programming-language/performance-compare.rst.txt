========================================
語言效能比較
========================================


.. contents:: 目錄


介紹
========================================

The Computer Language Benchmarks Game
-------------------------------------

.. image:: https://benchmarksgame-team.pages.debian.net/benchmarksgame/download/which-programs-are-fastest-faster.svg

.. image:: https://benchmarksgame-team.pages.debian.net/benchmarksgame/download/which-programs-are-fastest.svg



FFI
========================================

比較各語言在透過 FFI 呼叫 C 函式時的成本。


* `Comparing the C FFI overhead in various programming languages <https://github.com/dyu/ffi-overhead>`_
    - [HN] `Comparing the C FFI overhead in various programming languages <https://news.ycombinator.com/item?id=17161168>`_

根據上面的測試，
C++/Rust/Zig 基本上跟 C 直接呼叫一樣，
Nim/D 則是再多加一點點成本（10 ~ 20%），
Java 大概多 3 倍成本，
Node.js 大概多 9 倍成本，
Go 大概多 35 倍成本。

特別的是 LuaJIT 在多次呼叫 C 函式的測試中達到比在 C 中多次呼叫還要快的效能，
這是因為 C/C++/Rust 在呼叫時都透過了 PLT (procedure linkage table)，
而 LuaJIT 則是避免掉每次都透過 PLT，
在 C 中先使用 dlsym 取得 function 記憶體位址後再使用就可以達到和 LuaJIT 一樣的結果。


例如：

.. code-block:: c

  #include <dlfcn.h>  // need to linke with "-ldl"

  void run(int count) {
      // introduce already loaded functions to runtime linker's space
      void* handle = dlopen(0, RTLD_NOW|RTLD_GLOBAL);
      // load the function to our pointer
      // which doesn't know how many arguments there sould be
      int (*plusone)() = dlsym(handle, "plusone");
      int x = 0;
      while (x < count)
          x = plusone(x);
  }



參考
========================================

* `The Computer Language Benchmarks Game <https://benchmarksgame-team.pages.debian.net/benchmarksgame/>`_
