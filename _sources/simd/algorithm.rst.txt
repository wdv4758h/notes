========================================
運用 SIMD 來加速的演算法
========================================


.. contents:: 目錄


介紹
========================================

各家技術
------------------------------

1994 - RISC/SPARC - Sun Microsystems - VIS (Visual Instruction Set)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

1994 - RISC/PA-RISC - Hewlett-Packard - MAX (Multimedia Acceleration eXtensions)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

1995 - RISC/Alpha - DEC - MVI (Motion Video Instructions)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

1996 - RISC/MIPS - MIPS - MDMX (MIPS Digital Media eXtension)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

1996 - RISC/Power - AltiVec - Apple & IBM & Freescale
+++++++++++++++++++++++++++++++++++++++++++++++++++++

1996 - CISC/x86 - Intel - MMX
+++++++++++++++++++++++++++++

1997 - CISC/x86 - Intel - MMX2
++++++++++++++++++++++++++++++

1998 - CISC/x86 - AMD - 3DNow!
++++++++++++++++++++++++++++++

1999 - RISC/MIPS - MIPS - MIPS-3D
+++++++++++++++++++++++++++++++++

1999 - CISC/x86 - Intel - SSE (Streaming SIMD Extensions)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

2001 - CISC/x86 - Intel - SSE2
++++++++++++++++++++++++++++++

2003 - CISC/x86 - AMD - Advanced 3DNow!
+++++++++++++++++++++++++++++++++++++++

2004 - CISC/x86 - Intel - SSE3
++++++++++++++++++++++++++++++

2005 - RISC/ARM - ARM - NEON
++++++++++++++++++++++++++++

2006 - CISC/x86 - Intel - SSSE3 (Supplemental SSE3)
+++++++++++++++++++++++++++++++++++++++++++++++++++

2006 - CISC/x86 - Intel - SSE4
++++++++++++++++++++++++++++++

2007 - RISC/MIPS - Ingenic - MXU (Media Extension Unit)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++

2008 - CISC/x86 - Intel - AVX (Advanced Vector Extensions)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

2009 - CISC/x86 - AMD - F16C (Half-precision Float Conversion)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

2009 - CISC/x86 - AMD - XOP (eXtended Operations)
+++++++++++++++++++++++++++++++++++++++++++++++++

2010 - CISC/x86 - Intel - CLMUL (Carry-less Multiplication)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

2011 - CISC/x86 - AMD - FMA4
++++++++++++++++++++++++++++

2012 - CISC/x86 - AMD - FMA3
++++++++++++++++++++++++++++

2015 - CISC/x86 - Intel - AVX-512
+++++++++++++++++++++++++++++++++

2016 - RISC/ARM - ARM - SVE (Scalable Vector Extensions)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++



SIMD 與 Rust
========================================

針對型別的支援 — feature(repr_simd)
-----------------------------------

加上 ``#[repr(simd)]`` 屬性的型別會被編譯成 SIMD vector，
此型別可以為泛型但必須是同種 primitive type 重複數次。
加上此屬性後該型別可能會根據不同平台而有不同的 alignment。


SIMD 操作 — feature(platform_intrinsics)
----------------------------------------

CPU 廠商通常會提供一個 C header 讓開發者使用 CPU 的 SIMD 功能，
例如 ARM 的 `arm_neon.h <http://infocenter.arm.com/help/topic/com.arm.doc.ihi0073a/IHI0073A_arm_neon_intrinsics_ref.pdf>`_  或是 x86 的 `...mmintrin.h <https://software.intel.com/sites/landingpage/IntrinsicsGuide>`_ 。

這些功能都會以 compiler intrinsics 的形式來支援，
名稱也都會相似於 CPU 廠商所提供的 C header，
可以經由 ``extern`` block 選定適當的 ABI 來使用，
而不會放在 ``std`` 當中。

範例：

.. code-block:: rust

    extern "platform-intrinsic" {
        fn x86_mm_abs_epi16(a: Simd8<i16>) -> Simd8<i16>;
        fn simd_add<T>(a: T, b: T) -> T;
        // ...
    }


在 ``platform-intrinsic`` 中的函式會由 ``librustc_platform_intrinsics`` 來支援，
其中會用前綴來選擇對應平台的 SIMD 函式，
例如 ``x86_`` 、 ``arm_`` 、 ``aarch64`` （可以由 `rust/src/librustc_platform_intrinsics/lib.rs <https://github.com/rust-lang/rust/blob/master/src/librustc_platform_intrinsics/lib.rs>`_ 而知)，
在找到對應的平台後，
會再找到對應的 LLVM 定義（可以由 `rust/src/librustc_platform_intrinsics/x86.rs <https://github.com/rust-lang/rust/blob/master/src/librustc_platform_intrinsics/x86.rs>`_ 而知）。
這些 intrinsics 只在特定的 CPU 上可以使用，
如果 target CPU 不支援的話會產生編譯時期的錯誤。
（ ``librustc_platform_intrinsics`` 內針對各平台的程式是經由餵入不同的 JSON 設定檔給 `rust/src/etc/platform-intrinsics/generator.py <https://github.com/rust-lang/rust/blob/master/src/etc/platform-intrinsics/generator.py>`_ 所產生的）


除了上面提到的平台特定 SIMD 功能外，
有些功能是各個有支援 SIMD 的平台都能使用的，
這些功能會被包裝成更方便使用的形式，
例如 ``simd_add`` 、 ``simd_sub``
（可以在 `rust/src/librustc_trans/intrinsic.rs <https://github.com/rust-lang/rust/blob/master/src/librustc_trans/intrinsic.rs>`_ 當中的 ``generic_simd_intrinsic`` 找到）。


更完整的通用列表：

.. code-block:: rust

    extern "platform-intrinsic" {
        // Arithmetic
        fn simd_add<T>(x: T, y: T) -> T;
        fn simd_sub<T>(x: T, y: T) -> T;
        fn simd_mul<T>(x: T, y: T) -> T;
        fn simd_div<T>(x: T, y: T) -> T;
        fn simd_shl<T>(x: T, y: T) -> T;
        fn simd_shr<T>(x: T, y: T) -> T;
        fn simd_and<T>(x: T, y: T) -> T;
        fn simd_or<T>(x: T, y: T) -> T;
        fn simd_xor<T>(x: T, y: T) -> T;

        // Comparisons
        fn simd_eq<T, U>(v: T, w: T) -> U;
        fn simd_ne<T, U>(v: T, w: T) -> U;
        fn simd_lt<T, U>(v: T, w: T) -> U;
        fn simd_le<T, U>(v: T, w: T) -> U;
        fn simd_gt<T, U>(v: T, w: T) -> U;
        fn simd_ge<T, U>(v: T, w: T) -> U;

        // Shuffles (simd_shuffleN, N is usize)
        fn simd_shuffle2<T, U>(x: T, y: T, idx: [u32; 2]) -> U;
        fn simd_shuffle3<T, U>(x: T, y: T, idx: [u32; 3]) -> U;
        fn simd_shuffle4<T, U>(x: T, y: T, idx: [u32; 4]) -> U;
        fn simd_shuffle8<T, U>(x: T, y: T, idx: [u32; 8]) -> U;
        fn simd_shuffle16<T, U>(v: T, w: T, idx: [u32; 16]) -> U;

        // inserting/extracting elements
        fn simd_insert<T, E>(x: T, idx: u32, y: E) -> T;
        fn simd_extract<T, E>(x: T, idx: u32) -> E;

        // cast
        fn simd_cast<T, U>(x: T) -> U;
    }


相關檔案：

* https://github.com/rust-lang/rust/blob/master/src/test/run-pass/simd-generics.rs
* https://github.com/rust-lang/rust/blob/master/src/test/run-pass/simd-upgraded.rs
* https://github.com/rust-lang/rust/blob/master/src/test/run-pass/simd-intrinsic-generic-comparison.rs
* https://github.com/rust-lang/rust/blob/master/src/test/run-pass/simd-intrinsic-generic-arithmetic.rs
* https://github.com/rust-lang/rust/blob/master/src/test/run-pass/simd-intrinsic-generic-cast.rs
* https://github.com/rust-lang/rust/blob/master/src/test/run-pass/simd-intrinsic-generic-elements.rs
* https://github.com/rust-lang/rust/blob/master/src/librustc_typeck/check/intrinsic.rs
* https://github.com/rust-lang/rust/blob/master/src/libsyntax/abi.rs
* https://github.com/rust-lang/rust/blob/master/src/etc/platform-intrinsics/generator.py


平台偵測 — feature(cfg_target_feature)
--------------------------------------

要針對特定平台打開 SIMD 支援光是使用 ``cfg(target_arch = "...")`` 是不夠的，
因此需要 ``cfg(target_feature = "...")`` 的支援，
在 CPU 支援特定指令集時才開啟。
要特別指定開啟某個功能可以在編譯時加上參數，
例如 ``-C target-feature="+sse4.2"`` ，
另外也可以藉由 ``-C target-cpu=native`` 來讓編譯器自動偵測現在的 CPU 來選擇要開啟的功能。

如果搭配第三方的 `cfg-if <https://crates.io/crates/cfg-if>`_ 可能會讓程式長成這樣：

.. code-block:: rust

    cfg_if_else! {
    if #[cfg(target_feature = "avx")] {
        fn foo() { /* use AVX things */ }
    } else if #[cfg(target_feature = "sse4.1")] {
        fn foo() { /* use SSE4.1 things */ }
    } else if #[cfg(target_feature = "sse2")] {
        fn foo() { /* use SSE2 things */ }
    } else if #[cfg(target_feature = "neon")] {
        fn foo() { /* use NEON things */ }
    } else {
        fn foo() { /* universal fallback */ }
    }
}


第三方套件 — simd
------------------------------

目前在 Rust 針對 SIMD 最常使用的套件是 `simd <https://github.com/huonw/simd>`_ 。



基本 SIMD 範例
========================================

加法 — simd_add
------------------------------

.. code-block:: rust

    // Rust

    #![feature(repr_simd)]
    #![feature(platform_intrinsics)]

    #[repr(simd)]
    #[derive(Debug, Copy, Clone)]
    pub struct f32x8(f32, f32, f32, f32,
                     f32, f32, f32, f32);

    extern "platform-intrinsic" {
        fn simd_add<T>(a: T, b: T) -> T;
    }

    // 一般版本
    fn inplace_add_array(lhs: &mut [f32; 8], rhs: &[f32; 8]) {
        for (i, j) in lhs.iter_mut().zip(rhs.iter()) {
            *i += *j;
        }
    }

    // SIMD 版本
    fn inplace_add_array_simd(lhs: &mut f32x8, rhs: &f32x8) {
        unsafe {
            *lhs = simd_add(*lhs, *rhs);
        }
    }

    // 試用上面的函式
    fn main() {
        use std::f32;

        // 沒有 overflow
        {
            let mut a = [0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5];
            let b = [70.5, 71.5, 72.5, 73.5, 74.5, 75.5, 76.5, 77.5];
            println!("{:?} +\n{:?} =", a, b);
            inplace_add_array(&mut a, &b);
            println!("{:?}", a);
        }
        {
            let mut a = f32x8(0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5);
            let b = f32x8(70.5, 71.5, 72.5, 73.5, 74.5, 75.5, 76.5, 77.5);
            println!("{:?} +\n{:?} =", a, b);
            inplace_add_array_simd(&mut a, &b);
            println!("{:?}", a);
        }

        // 有 overflow
        {
            let mut a = [0.5, f32::MAX, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5];
            let b = [70.5, f32::MAX/2.0, 72.5, 73.5, 74.5, 75.5, 76.5, 77.5];
            println!("{:?} +\n{:?} =", a, b);
            inplace_add_array(&mut a, &b);
            println!("{:?}", a);
        }
        {
            let mut a = f32x8(0.5, f32::MAX, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5);
            let b = f32x8(70.5, f32::MAX/2.0, 72.5, 73.5, 74.5, 75.5, 76.5, 77.5);
            println!("{:?} +\n{:?} =", a, b);
            inplace_add_array_simd(&mut a, &b);
            println!("{:?}", a);
        }
    }


指令集說明
========================================

Byte Shuffle - pshufb (_mm_shuffle_epi8)
----------------------------------------

範例：

.. code-block:: c

    // C

    #include <stdio.h>
    #include <stdint.h>     // uint16_t
    #include <tmmintrin.h>  // SSSE3

    void print128_num(__m128i var) {
        uint16_t *val = (uint16_t*) &var;
        printf("Numerical: %i %i %i %i %i %i %i %i \n",
                val[0], val[1], val[2], val[3], val[4], val[5],
                val[6], val[7]);
    }

    int main() {
        // Set packed 16-bit integers
        // 128 bits, 8 short, per 16 bits
        __m128i v_in = _mm_setr_epi16(1, 2, 3, 4, 5, 6, 7, 8);
        // Set packed 8-bit integers
        // 128 bits, 16 chars, per 8 bits
        __m128i v_perm = _mm_setr_epi8(1, 0, 2, 3, 8, 9, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15);
        // Shuffle packed 8-bit integers
        __m128i v_out = _mm_shuffle_epi8(v_in, v_perm); // pshufb
        print128_num(v_in);
        print128_num(v_out);
        return 0;
    }


編譯並執行：

.. code-block:: sh

    $ clang -mssse3 test.c
    $ ./a.out
    Numerical: 1 2 3 4 5 6 7 8
    Numerical: 256 2 5 6 3 7 4 8

Byte Shuffle 操作：

::

    Data (Number, Binary, Byte Index) :

        +---------------------+----------+----------+----------+----------+----------+----------+
        |          1          |          2          |          3          |          4          | Number
        +----------+----------+----------+----------+----------+----------+----------+----------+
        | 00000000 | 00000001 | 00000000 | 00000010 | 00000000 | 00000011 | 00000000 | 00000100 | Binary
        +----------+----------+----------+----------+----------+----------+----------+----------+
        |        0 |        1 |        2 |        3 |        4 |        5 |        6 |        7 | Index
        +----------+----------+----------+----------+----------+----------+----------+----------+

        +----------+----------+----------+----------+----------+----------+----------+----------+
        |          5          |          6          |          7          |          8          | Number
        +----------+----------+----------+----------+----------+----------+----------+----------+
        | 00000000 | 00000101 | 00000000 | 00000110 | 00000000 | 00000111 | 00000000 | 00001000 | Binary
        +----------+----------+----------+----------+----------+----------+----------+----------+
        |        8 |        9 |       10 |       11 |       12 |       13 |       14 |       15 | Index
        +----------+----------+----------+----------+----------+----------+----------+----------+

    Index (Byte Index) :

        +------+------+------+------+------+------+------+------+
        |    1 |    0 |    2 |    3 |    8 |    9 |   10 |   11 |
        +------+------+------+------+------+------+------+------+

        +------+------+------+------+------+------+------+------+
        |    4 |    5 |   12 |   13 |    6 |    7 |   14 |   15 |
        +------+------+------+------+------+------+------+------+

    Result :

        +----------+----------+----------+----------+----------+----------+----------+----------+
        |        1 |        0 |        2 |        3 |        8 |        9 |       10 |       11 | Index
        +----------+----------+----------+----------+----------+----------+----------+----------+
        | 00000001 | 00000000 | 00000000 | 00000010 | 00000000 | 00000101 | 00000000 | 00000110 | Binary
        +----------+----------+----------+----------+----------+----------+----------+----------+
        |         256         |          2          |          5          |          6          | Number
        +---------------------+----------+----------+----------+----------+----------+----------+

        +----------+----------+----------+----------+----------+----------+----------+----------+
        |        4 |        5 |       12 |       13 |        6 |        7 |       14 |       15 | Index
        +----------+----------+----------+----------+----------+----------+----------+----------+
        | 00000000 | 00000011 | 00000000 | 00000111 | 00000000 | 00000100 | 00000000 | 00001000 | Binary
        +----------+----------+----------+----------+----------+----------+----------+----------+
        |          3          |          7          |          4          |          8          | Number
        +---------------------+----------+----------+----------+----------+----------+----------+






編譯器 — Vectorization
========================================

介紹
------------------------------

這是讓編譯器自動將原本的程式轉換成使用 SIMD Instruction 的 Binary 的技術，
雖然目前已經有可以使用的技術，
但是還是有改進的空間，
程式設計師仍然能容易地利用 SIMD 自己寫出更好的程式。


Implicit:

* `Auto-Vectorization in LLVM <http://llvm.org/docs/Vectorizers.html>`_
* `Polly - Polyhedral optimizations for LLVM <http://polly.llvm.org/>`_

Explicit:

* `Intel® SPMD Program Compiler - A compiler for high-performance SIMD programming on the CPU <https://ispc.github.io/>`_
* OpenMP SIMD



相關參考：

* [2015] `Throttling Automatic Vectorization: When Less is More <http://llvm.org/devmtg/2015-10/slides/Porpodas-ThrottlingAutomaticVectorization.pdf>`_
    - `Video <https://www.youtube.com/watch?v=xxtA2XPmIug>`_
* [2016] `RV: A Unified Region Vectorizer for LLVM <http://www.llvm.org/devmtg/2016-11/Slides/Moll-RV.pdf>`_
    - `Video <https://www.youtube.com/watch?v=cyldhrzqxPA>`_
    - [GitHub] `A Unified Region Vectorizer for LLVM <https://github.com/simoll/rv>`_


LLVM Auto-Vectorization
------------------------------

Polly
------------------------------

Intel SPMD Program Compiler
------------------------------

ispc 是 Intel 開發的開放原始碼編譯器，
為的是有效地利用 CPU 上 SIMD 的支援來加速程式。
作法和 CUDA 還有 OpenCL 類似，
使用特別制定的 C-Like 語言來實做 ISPC Program （需要用 SIMD 來加速的 Function），
接著使用 ispc 來編譯，
剩餘程式則使用一般的 C 或 C++ 來撰寫即可，
最後搭配在一起達成加速的效果，
如此一來就不用自己去手寫利用 SSE 等指令的程式碼。

相關論文：

* [2012] `ispc: A SPMD Compiler for High-Performance CPU Programming <http://llvm.org/pubs/2012-05-13-InPar-ispc.html>`_


Mandelbrot 範例
++++++++++++++++++++

取自 `ispc/examples/mandelbrot/ <https://github.com/ispc/ispc/blob/master/examples/mandelbrot/>`_ ，
SIMD 版本：

``mandelbrot_serial.cpp`` （一般版本）:

.. code-block:: cpp

    static int mandel(float c_re, float c_im, int count) {
        float z_re = c_re, z_im = c_im;
        int i;
        for (i = 0; i < count; ++i) {
            if (z_re * z_re + z_im * z_im > 4.f)
                break;

            float new_re = z_re*z_re - z_im*z_im;
            float new_im = 2.f * z_re * z_im;
            z_re = c_re + new_re;
            z_im = c_im + new_im;
        }

        return i;
    }

    void mandelbrot_serial(float x0, float y0, float x1, float y1,
                           int width, int height, int maxIterations,
                           int output[])
    {
        float dx = (x1 - x0) / width;
        float dy = (y1 - y0) / height;

        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; ++i) {
                float x = x0 + i * dx;
                float y = y0 + j * dy;

                int index = (j * width + i);
                output[index] = mandel(x, y, maxIterations);
            }
        }
    }


``mandelbrot.ispc`` （ispc 版本）:

.. code-block:: ispc

    static inline int mandel(float c_re, float c_im, int count) {
        float z_re = c_re, z_im = c_im;
        int i;
        for (i = 0; i < count; ++i) {
            if (z_re * z_re + z_im * z_im > 4.)
                break;

            float new_re = z_re*z_re - z_im*z_im;
            float new_im = 2.f * z_re * z_im;
            unmasked {
                z_re = c_re + new_re;
                z_im = c_im + new_im;
            }
        }

        return i;
    }

    export void mandelbrot_ispc(uniform float x0, uniform float y0,
                                uniform float x1, uniform float y1,
                                uniform int width, uniform int height,
                                uniform int maxIterations,
                                uniform int output[])
    {
        float dx = (x1 - x0) / width;
        float dy = (y1 - y0) / height;

        for (uniform int j = 0; j < height; j++) {
            // Note that we'll be doing programCount computations in parallel,
            // so increment i by that much.  This assumes that width evenly
            // divides programCount.
            foreach (i = 0 ... width) {
                // Figure out the position on the complex plane to compute the
                // number of iterations at.  Note that the x values are
                // different across different program instances, since its
                // initializer incorporates the value of the programIndex
                // variable.
                float x = x0 + i * dx;
                float y = y0 + j * dy;

                int index = j * width + i;
                output[index] = mandel(x, y, maxIterations);
            }
        }
    }


``mandelbrot.cpp`` :

.. code-block:: cpp

    #ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
    #define NOMINMAX
    #pragma warning (disable: 4244)
    #pragma warning (disable: 4305)
    #endif

    #include <stdio.h>
    #include <algorithm>
    #include "../timing.h"
    #include "mandelbrot_ispc.h"
    #include <string.h>
    #include <cstdlib>
    using namespace ispc;

    extern void mandelbrot_serial(float x0, float y0, float x1, float y1,
                                  int width, int height, int maxIterations,
                                  int output[]);

    /* Write a PPM image file with the image of the Mandelbrot set */
    static void
    writePPM(int *buf, int width, int height, const char *fn) {
        FILE *fp = fopen(fn, "wb");
        fprintf(fp, "P6\n");
        fprintf(fp, "%d %d\n", width, height);
        fprintf(fp, "255\n");
        for (int i = 0; i < width*height; ++i) {
            // Map the iteration count to colors by just alternating between
            // two greys.
            char c = (buf[i] & 0x1) ? 240 : 20;
            for (int j = 0; j < 3; ++j)
                fputc(c, fp);
        }
        fclose(fp);
        printf("Wrote image file %s\n", fn);
    }


    int main(int argc, char *argv[]) {
        static unsigned int test_iterations[] = {3, 3};
        unsigned int width = 768;
        unsigned int height = 512;
        float x0 = -2;
        float x1 = 1;
        float y0 = -1;
        float y1 = 1;

        if (argc > 1) {
            if (strncmp(argv[1], "--scale=", 8) == 0) {
                float scale = atof(argv[1] + 8);
                width *= scale;
                height *= scale;
            }
        }
        if ((argc == 3) || (argc == 4)) {
            for (int i = 0; i < 2; i++) {
                test_iterations[i] = atoi(argv[argc - 2 + i]);
            }
        }

        int maxIterations = 256;
        int *buf = new int[width*height];

        //
        // Compute the image using the ispc implementation; report the minimum
        // time of three runs.
        //
        double minISPC = 1e30;
        for (unsigned int i = 0; i < test_iterations[0]; ++i) {
            reset_and_start_timer();
            mandelbrot_ispc(x0, y0, x1, y1, width, height, maxIterations, buf);
            double dt = get_elapsed_mcycles();
            printf("@time of ISPC run:\t\t\t[%.3f] million cycles\n", dt);
            minISPC = std::min(minISPC, dt);
        }

        printf("[mandelbrot ispc]:\t\t[%.3f] million cycles\n", minISPC);
        writePPM(buf, width, height, "mandelbrot-ispc.ppm");

        // Clear out the buffer
        for (unsigned int i = 0; i < width * height; ++i)
            buf[i] = 0;

        //
        // And run the serial implementation 3 times, again reporting the
        // minimum time.
        //
        double minSerial = 1e30;
        for (unsigned int i = 0; i < test_iterations[1]; ++i) {
            reset_and_start_timer();
            mandelbrot_serial(x0, y0, x1, y1, width, height, maxIterations, buf);
            double dt = get_elapsed_mcycles();
            printf("@time of serial run:\t\t\t[%.3f] million cycles\n", dt);
            minSerial = std::min(minSerial, dt);
        }

        printf("[mandelbrot serial]:\t\t[%.3f] million cycles\n", minSerial);
        writePPM(buf, width, height, "mandelbrot-serial.ppm");

        printf("\t\t\t\t(%.2fx speedup from ISPC)\n", minSerial/minISPC);

        return 0;
    }


``timing.h`` :

.. code-block:: c

    #include <stdint.h>

    #ifdef __arm__
    #include <sys/time.h>
    // There's no easy way to get a hardware clock counter on ARM, so instead
    // we'll pretend it's a 1GHz processor and then compute pretend cycles
    // based on elapsed time from gettimeofday().
    __inline__ uint64_t rdtsc() {
      static bool first = true;
      static struct timeval tv_start;
      if (first) {
        gettimeofday(&tv_start, NULL);
        first = false;
        return 0;
      }

      struct timeval tv;
      gettimeofday(&tv, NULL);
      tv.tv_sec -= tv_start.tv_sec;
      tv.tv_usec -= tv_start.tv_usec;
      return (1000000ull * tv.tv_sec + tv.tv_usec) * 1000ull;
    }

    #include <sys/time.h>
    static inline double rtc(void)
    {
      struct timeval Tvalue;
      double etime;
      struct timezone dummy;

      gettimeofday(&Tvalue,&dummy);
      etime =  (double) Tvalue.tv_sec +
        1.e-6*((double) Tvalue.tv_usec);
      return etime;
    }

    #else // __arm__

    #ifdef WIN32
    #include <windows.h>
    #define rdtsc __rdtsc
    #else // WIN32
    __inline__ uint64_t rdtsc() {
      uint32_t low, high;
    #ifdef __x86_64
      __asm__ __volatile__ ("xorl %%eax,%%eax \n    cpuid"
                            ::: "%rax", "%rbx", "%rcx", "%rdx" );
    #else
      __asm__ __volatile__ ("xorl %%eax,%%eax \n    cpuid"
                            ::: "%eax", "%ebx", "%ecx", "%edx" );
    #endif
      __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high));
      return (uint64_t)high << 32 | low;
    }

    #include <sys/time.h>
    static inline double rtc(void)
    {
      struct timeval Tvalue;
      double etime;
      struct timezone dummy;

      gettimeofday(&Tvalue,&dummy);
      etime =  (double) Tvalue.tv_sec +
        1.e-6*((double) Tvalue.tv_usec);
      return etime;
    }

    #endif // !WIN32
    #endif // !__arm__

    static uint64_t start,  end;
    static double  tstart, tend;

    static inline void reset_and_start_timer()
    {
        start = rdtsc();
    #ifndef WIN32
        // Unused in Windows build, rtc() causing link errors
        tstart = rtc();
    #endif
    }

    /* Returns the number of millions of elapsed processor cycles since the
       last reset_and_start_timer() call. */
    static inline double get_elapsed_mcycles()
    {
        end = rdtsc();
        return (end-start) / (1024. * 1024.);
    }

    #ifndef WIN32
    // Unused in Windows build, rtc() causing link errors
    static inline double get_elapsed_msec()
    {
        tend = rtc();
        return (tend - tstart)*1e3;
    }
    #endif


編譯並執行：

.. code-block:: sh

    $ mkdir objs
    $ ispc -O3 --target=host mandelbrot.ispc -o objs/mandelbrot_ispc.o -h objs/mandelbrot_ispc.h
    $ clang++ -O3 -I objs/ mandelbrot.cpp -c -o objs/mandelbrot.o
    $ clang++ -O3 -I objs/ mandelbrot_serial.cpp -c -o objs/mandelbrot_serial.o
    $ clang++ -O3 -I objs/ -o mandelbrot objs/mandelbrot.o objs/mandelbrot_ispc.o objs/mandelbrot_serial.o
    $ ls -l mandelbrot
    -rwxr-xr-x 1 user user 13424 Dec  3 13:06 mandelbrot
    $ strip mandelbrot
    $ ls -l mandelbrot
    -rwxr-xr-x 1 user user 10432 Dec  3 13:06 mandelbrot
    $ ldd mandelbrot
            linux-vdso.so.1 (0x00007ffc4b3fe000)
            libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x00007fc2108da000)
            libm.so.6 => /usr/lib/libm.so.6 (0x00007fc2105d6000)
            libgcc_s.so.1 => /usr/lib/libgcc_s.so.1 (0x00007fc2103bf000)
            libc.so.6 => /usr/lib/libc.so.6 (0x00007fc210021000)
            /lib64/ld-linux-x86-64.so.2 (0x00007fc210c62000)
    $ ./mandelbrot  # Intel Xeon(R) CPU E5504 @ 2.00GHz
    @time of ISPC run:                      [156.990] million cycles
    @time of ISPC run:                      [154.923] million cycles
    @time of ISPC run:                      [154.838] million cycles
    [mandelbrot ispc]:              [154.838] million cycles
    Wrote image file mandelbrot-ispc.ppm
    @time of serial run:                    [319.032] million cycles
    @time of serial run:                    [319.239] million cycles
    @time of serial run:                    [318.566] million cycles
    [mandelbrot serial]:            [318.566] million cycles
    Wrote image file mandelbrot-serial.ppm
                                    (2.06x speedup from ISPC)
    $ ./mandelbrot  # Intel Core(TM) i5-6200U CPU @ 2.30GHz
    @time of ISPC run:                      [64.837] million cycles
    @time of ISPC run:                      [59.869] million cycles
    @time of ISPC run:                      [61.037] million cycles
    [mandelbrot ispc]:              [59.869] million cycles
    Wrote image file mandelbrot-ispc.ppm
    @time of serial run:                    [354.393] million cycles
    @time of serial run:                    [353.565] million cycles
    @time of serial run:                    [354.725] million cycles
    [mandelbrot serial]:            [353.565] million cycles
    Wrote image file mandelbrot-serial.ppm
                                    (5.91x speedup from ISPC)


取自 `ispc/examples/mandelbrot_tasks/ <https://github.com/ispc/ispc/blob/master/examples/mandelbrot_tasks/>`_ ，
SIMD + multithreading 版本：

.. code-block:: sh

    $ ispc -O3 --target=host mandelbrot_tasks.ispc -o objs/mandelbrot_tasks_ispc.o -h objs/mandelbrot_tasks_ispc.h
    $ clang++ -O3 -I objs/ mandelbrot_tasks.cpp -c -o objs/mandelbrot_tasks.o
    $ clang++ -O3 -I objs/ mandelbrot_tasks_serial.cpp -c -o objs/mandelbrot_tasks_serial.o
    $ clang++ -O3 tasksys.cpp -c -o objs/tasksys.o  # for ISPCAlloc, ISPCLaunch, ISPCSync
    $ clang++ -O3 -I objs/ -o mandelbrot objs/mandelbrot_tasks.o objs/mandelbrot_tasks_ispc.o objs/mandelbrot_tasks_serial.o objs/tasksys.o -lpthread         # use pthread for multithreading
    $ ls -l mandelbrot
    -rwxr-xr-x 1 user user 28544 Dec  3 13:06 mandelbrot
    $ strip mandelbrot
    $ ls -l mandelbrot
    -rwxr-xr-x 1 user user 23032 Dec  3 13:06 mandelbrot
    $ ldd mandelbrot
            linux-vdso.so.1 (0x00007fffd6b38000)
            libpthread.so.0 => /usr/lib/libpthread.so.0 (0x00007f8396a40000)
            libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x00007f83966b8000)
            libm.so.6 => /usr/lib/libm.so.6 (0x00007f83963b4000)
            libgcc_s.so.1 => /usr/lib/libgcc_s.so.1 (0x00007f839619d000)
            libc.so.6 => /usr/lib/libc.so.6 (0x00007f8395dff000)
            /lib64/ld-linux-x86-64.so.2 (0x00007f8396c5d000)
    $ ./mandelbrot  # Intel Xeon(R) CPU E5504 @ 2.00GHz
    @time of ISPC + TASKS run:              [143.944] million cycles
    @time of ISPC + TASKS run:              [114.246] million cycles
    @time of ISPC + TASKS run:              [134.146] million cycles
    @time of ISPC + TASKS run:              [131.987] million cycles
    @time of ISPC + TASKS run:              [124.449] million cycles
    @time of ISPC + TASKS run:              [118.815] million cycles
    @time of ISPC + TASKS run:              [119.104] million cycles
    [mandelbrot ispc+tasks]:        [114.246] million cycles
    Wrote image file mandelbrot-ispc.ppm
    @time of serial run:                    [2456.413] million cycles
    [mandelbrot serial]:            [2456.413] million cycles
    Wrote image file mandelbrot-serial.ppm
                                    (21.50x speedup from ISPC + tasks)
    $ ./mandelbrot  # Intel Core(TM) i5-6200U CPU @ 2.30GHz
    @time of ISPC + TASKS run:              [100.304] million cycles
    @time of ISPC + TASKS run:              [118.307] million cycles
    @time of ISPC + TASKS run:              [99.052] million cycles
    @time of ISPC + TASKS run:              [99.102] million cycles
    @time of ISPC + TASKS run:              [98.825] million cycles
    @time of ISPC + TASKS run:              [98.654] million cycles
    @time of ISPC + TASKS run:              [108.323] million cycles
    [mandelbrot ispc+tasks]:        [98.654] million cycles
    Wrote image file mandelbrot-ispc.ppm
    @time of serial run:                    [2760.993] million cycles
    [mandelbrot serial]:            [2760.993] million cycles
    Wrote image file mandelbrot-serial.ppm
                                    (27.99x speedup from ISPC + tasks)



OpenMP SIMD
------------------------------

OpenMP 自 4.0 釋出後加入了 SIMD 的支援，
而各編譯器也漸漸有了支援：

* `GCC 4.9.0 for C/C++, GCC 4.9.1 for Fortran <https://www.gnu.org/software/gcc/gcc-4.9/changes.html#languages>`_
* `Intel Fortran and C/C++ compilers 15.0 <https://software.intel.com/en-us/articles/openmp-40-features-in-intel-compiler-150>`_
* `LLVM/Clang 3.7 (partial) <http://llvm.org/releases/3.7.0/tools/clang/docs/ReleaseNotes.html#openmp-support>`_


使用方法如下：

.. code-block:: c

    #pragma omp simd
    for (...) {
        ...
    }

    #pragma omp parallel for simd
    for (...) {
        ...
    }


相關參數可以參考 `OpenMP 4.0 API C/C++ Syntax Quick Reference Card <http://www.openmp.org/wp-content/uploads/OpenMP-4.0-C.pdf>`_



參考
========================================

* `Wikipedia - SIMD <https://en.wikipedia.org/wiki/SIMD>`_
* `Wikipedia - SWAR (SIMD within a register) <https://en.wikipedia.org/wiki/SWAR>`_
* `Wikipedia - Intrinsic function <https://en.wikipedia.org/wiki/Intrinsic_function>`_
* [2005] `An Investigation of SIMD instruction sets <https://web.archive.org/web/20140320040450/http://noisymime.org/blogimages/SIMD.pdf>`_
* [2014] `Automatic SIMD Vectorization of SSA-based Control Flow Graphs <http://d-nb.info/1071087355/34>`_
* `LLVM - Intrinsic Functions <http://llvm.org/docs/LangRef.html#intrinsic-functions>`_
* `Polly Labs - Promoting Polyhedral Compilation <https://pollylabs.org/>`_
* `Basics of SIMD Programming <https://www.kernel.org/pub/linux/kernel/people/geoff/cell/ps3-linux-docs/CellProgrammingTutorial/BasicsOfSIMDProgramming.html>`_
* `Julia - Performance Annotations - @simd <http://docs.julialang.org/en/release-0.5/manual/performance-tips#performance-annotations>`_
    - https://github.com/JuliaLang/julia/blob/26d6c20dc803eedf77f41430806efb20f253da1b/src/llvm-simdloop.cpp


* `Rust RFCs - 1199 - SIMD Infrastructure <https://github.com/rust-lang/rfcs/blob/master/text/1199-simd-infrastructure.md>`_
* `SIMD in Rust <https://huonw.github.io/blog/2015/08/simd-in-rust/>`_
* `Mandelbrot Set with SIMD Intrinsics <http://nullprogram.com/blog/2015/07/10/>`_


* `MDN - JavaScript - SIMD <https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_Objects/SIMD>`_
* `MDN - JavaScript - SIMD types <https://developer.mozilla.org/en/docs/Web/JavaScript/SIMD_types>`_
* `SIMD.js specification <https://tc39.github.io/ecmascript_simd/>`_

* `x86 Intrinsics Cheatsheet <https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf>`_
* `Intel Intrinsics Guide <https://software.intel.com/sites/landingpage/IntrinsicsGuide/>`_
* `Intel® 64 and IA-32 Architectures Software Developer's Manual <http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html>`_
* `Intel® 64 and IA-32 Architectures Optimization Reference Manual <https://software.intel.com/sites/default/files/managed/9e/bc/64-ia-32-architectures-optimization-manual.pdf>`_


Wojciech Muła:

* `SIMD-friendly algorithms for substring searching <http://0x80.pl/articles/simd-strfind.html>`_


專案參看：

* `VecPy <https://github.com/undefx/vecpy>`_
    - builds native libraries from arbitrary kernel functions written in Python
* `Pillow-SIMD <https://github.com/uploadcare/pillow-simd>`_
* `PyPy Vectorization <https://pypyvecopt.blogspot.com/>`_
* `Pythran <https://github.com/serge-sans-paille/pythran>`_
    - Python to C++ compiler for a subset of the Python with SIMD support
* `Numba <https://github.com/numba/numba>`_
    - NumPy aware dynamic Python compiler using LLVM
* `Yeppp! - high-performance SIMD-optimized mathematical library for x86, ARM, and MIPS <https://www.yeppp.info/index.html>`_
* `Project Ne10: An Open Optimized Software Library Project for the ARM Architecture <http://projectne10.github.io/Ne10/>`_
* `Eigen <https://bitbucket.org/eigen/eigen/>`_
    - C++ template library for linear algebra
* `Boost.SIMD <https://github.com/NumScale/boost.simd>`_
    - portable SIMD programming library to be proposed as a Boost library
* `OpenCV <https://github.com/opencv/opencv>`_
* `dlib <https://github.com/davisking/dlib>`_
    - modern C++ toolkit containing machine learning algorithms
