========================================
SIMD
========================================

* 目前各平台 SIMD 狀況
    - Intel x86_64 : AVX (以前是 SSE)
    - ARM : NEON、SVE


Intel 的 SSE 浮點運算會使用另外的 register set (``XMM`` registers)，
SSE 原先使用的是 128-bit 的 registers (XMM0 ~ XMM7)

::

    <-----  128 bits  ----->
    +----------------------+
    | xmm0                 |
    +----------------------+
    | xmm1                 |
    +----------------------+
    | xmm2                 |
    +----------------------+
    | xmm3                 |
    +----------------------+
    | xmm4                 |
    +----------------------+
    | xmm5                 |
    +----------------------+
    | xmm6                 |
    +----------------------+
    | xmm7                 |
    +----------------------+


ARMv8-A - SVE
========================================

SVE 是 Scalable Vector Extensions 的縮寫，
支援 128 ~ 2048 bits （之前的 NEON 只有 64 或 128 bits）

* SVE Auto-Vectorization



Reference
========================================

* `Why we Need WebAssembly - An Interview with Brendan Eich <https://medium.com/javascript-scene/why-we-need-webassembly-an-interview-with-brendan-eich-7fb2a60b0723>`_
* `[2015][GDC] Performance Optimization, SIMD and Cache <https://www.youtube.com/watch?v=Nsf2_Au6KxU>`_
    - `Slides <http://media.steampowered.com/apps/valve/2015/Migdalskiy_Sergiy_Physics_Optimization_Strategies.pdf>`_
* `[2010] ARM Advanced SIMD (NEON) Intrinsics and Types in LLVM <http://blog.llvm.org/2010/04/arm-advanced-simd-neon-intrinsics-and.html>`_
* `X86MCCodeEmitter.cpp <http://llvm.org/docs/doxygen/html/X86MCCodeEmitter_8cpp_source.html>`_

* `ARM Advanced SIMD (NEON) Intrinsics and Types in LLVM <http://blog.llvm.org/2010/04/arm-advanced-simd-neon-intrinsics-and.html>`_
* `Using SIMD for Hardware Acceleration <http://krishnakanthmallikc.blogspot.tw/2011/02/using-simd-for-hardware-acceleration.html>`_
* `Beyond intrinsics to code idiom <http://altdevblog.com/2011/12/24/beyond-intrinsics-to-code-idiom/>`_

ARM SVE

* `Champ Yen - ARM 近日公佈了在 ARMv8-A 架構新增了 Scalable Vector Extension (SVE) 新的 SIMD 擴充指令集 <https://www.facebook.com/champ.yen/posts/10208485207620973>`_
* `Champ Yen - 延續昨晚的分享，今日 ARM 揭露了更多SVE的細節 <https://www.facebook.com/champ.yen/posts/10208488947994480>`_
