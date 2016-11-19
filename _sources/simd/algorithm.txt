========================================
運用 SIMD 來加速的演算法
========================================


.. contents:: 目錄


基本 SIMD 範例
========================================

加法
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
