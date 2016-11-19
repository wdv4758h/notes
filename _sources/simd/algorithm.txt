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


SIMD 操作 - feature(platform_intrinsics)
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


平台偵測 - feature(cfg_target_feature)
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
