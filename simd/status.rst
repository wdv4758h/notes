========================================
SIMD
========================================

* 目前各平台 SIMD 狀況
    - Intel x86_64 : AVX (以前是 SSE)
    - ARM : NEON


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
