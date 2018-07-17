========================================
科學計算相關 (Scientific)
========================================


.. contents:: 目錄


套件
========================================

* `libm - pure Rust "musl libm" port <https://github.com/japaric/libm>`_
    - 支援 no_std
* `num - collection of numeric types and traits <https://github.com/rust-num/num>`_
    - 支援 no_std
* `ndarray - N-dimensional array <https://github.com/bluss/rust-ndarray>`_
* `nalgebra - Linear Algebra <https://github.com/sebcrozet/nalgebra>`_
    - 支援 no_std


介紹
========================================

在科學計算相關的使用上，
比較常聽到的就是 Python 的 NumPy、SciPy 等等，
而 Rust 這邊相關的套件則還在建置中。


在 Standard Library 內，
Rust 有一些像是 Add、Sub、Mul、PartialEq、PartialOrd 等等的 trait 來抽象化各種型別。
在第三方套件中，
有 ``num`` 負責建立各種數值的界面，
例如 Zero、Integer、Float 等等。
另外還有 ``ndarray`` 實做 N 維陣列，
``nalgebra`` 實做線性代數相關運算。



Add, Sub, Mul, Div, Rem
========================================

AddAssign, SubAssign, MulAssign, DivAssign, RemAssign
=====================================================



Eq, PartialEq
========================================

Ord, PartialOrd
========================================


num
========================================

num 所包含的 trait
------------------------------

``num`` 提供了一些數值相關的型別和 Trait，
可以藉此來撰寫數學相關函式。

Crates：

* num-traits:   基本數值界面，例如有號無號、加減乘除、餘數等等
* num-integer:  「整數」型別
* num-rational: 「有理數」型別，主要是可以用分數
* num-complex:  「複數」型別
* num-bigint:   實做「大數」
* num-iter:     支援 iterator，可以用 range
* num-derive:   提供 macro 來實做客製化型別和 primitive 數值的轉換
* num:          把以上 crates 統合打包

----

``Zero`` 定義型別的加法單位元素 (additive identity)，
隱含 ``Sized`` 、 ``Add`` 。

::

    a + 0 = a       ∀ a ∈ Self
    0 + a = a       ∀ a ∈ Self

提供：

* zero
* is_zero

----

``One`` 定義型別的乘法單位元素 (multiplicative identity)，
隱含 ``Sized`` 、 ``Mul`` 。

::

    a * 1 = a       ∀ a ∈ Self
    1 * a = a       ∀ a ∈ Self

提供：

* one

----

``NumOps`` 表示型別支援基本運算操作，
包含 ``Add`` 、 ``Sub`` 、 ``Mul`` 、 ``Div`` 、 ``Rem`` ，
有實做以上五種 trait 的型別會自動實做了 ``NumOps`` ，
算是把這幾個 trait 包起來。

``NumAssignOps`` 表示型別支援 assign 版本的基本運算操作，
包含 ``AddAssign`` 、 ``SubAssign`` 、 ``MulAssign`` 、
``DivAssign`` 、 ``RemAssign`` ，
有實做以上五種 trait 的型別會自動實做了 ``NumAssignOps`` ，
算是把這幾個 trait 包起來。

----

``Num`` 表示型別為數值，
代表定義數值的零、一、加減乘除、餘數、Partial Equal，
隱含 ``Zero`` 、 ``One`` 、 ``NumOps`` 、 ``PartialEq`` 。

提供：

* from_str_radix


``NumAssign`` 表示這個型別的 ``Num`` 也支援 assign 相關操作，
有實做 ``Num`` 和 ``NumAssignOps`` 的型別會自動實做 ``NumAssign`` ，
算是簡易包裝。

----

``Signed`` 表示這個型別的數值是有號的，
數值可以是負，
隱含 ``Sized`` 、 ``Num`` 、 ``Neg`` 。

提供：

* abs
* abs_sub
* signum
* is_positive
* is_negative

----

``Unsigned`` 表示這個型別的數值是無號的，
隱含 ``Num`` ，目前沒有提供額外的 method。

----

``Real`` 提供實數定義，
但不一定需要實做浮點數相關的 NaN 和 Inf (但是 Float 有實做 Real)，
隱含 ``Num`` 、 ``Copy`` 、 ``NumCast`` 、 ``PartialEq`` 、 ``Neg`` 。

提供：

* min_value
* min_positive_value
* epsilon
* max_value
* floor
* ceil
* round
* trunc
* fract
* abs
* signum
* is_sign_positive
* is_sign_negative
* mul_add
* recip
* powi
* powf
* sqrt
* exp
* exp2
* ln
* log
* log2
* log10
* to_degrees
* to_radians
* max
* min
* abs_sub
* cbrt
* hypot
* sin
* cos
* tan
* asin
* acos
* atan
* atan2
* sin_cos
* exp_m1
* ln_1p
* sinh
* cosh
* tanh
* asinh
* acosh
* atanh

----

``Float`` 提供浮點數定義，
隱含 ``NumCast`` 、 ``Num`` 、 ``Copy`` 、 ``Neg`` 、 ``PartialOrd`` 。

提供：

* nan
* infinity
* neg_infinity
* neg_zero
* min_value
* min_positive_value
* max_value
* is_nan
* is_infinite
* is_finite
* is_normal
* classify
* floor
* ceil
* round
* trunc
* fract
* abs
* signum
* is_sign_positive
* is_sign_negative
* mul_add
* recip
* powi
* powf
* sqrt
* exp
* exp2
* ln
* log
* log2
* log10
* max
* min
* abs_sub
* cbrt
* hypot
* sin
* cos
* tan
* asin
* acos
* atan
* atan2
* sin_cos
* exp_m1
* ln_1p
* sinh
* cosh
* tanh
* asinh
* acosh
* atanh
* integer_decode
* epsilon
* to_degrees
* to_radians

----

``Integer`` 表示型別為整數，
隱含 ``Sized`` 、 ``Eq`` 、 ``Ord`` 、 ``PartialOrd`` 、 ``Num`` 。

提供：

* div_floor
* mod_floor
* gcd
* lcm
* divides
* is_multiple_of
* is_even
* is_odd
* div_rem
* div_mod_floor

----

``Bounded`` 表示數值有上下界。

提供：

* min_value
* max_value

----

``PrimInt`` 提供一些 Primitive 的整數操作，
例如計算 leading zeros、trailing zeros、big/little endian 轉換等等，
隱含 ``Saturating`` 、 ``CheckedAdd`` 、 ``CheckedSub`` 、 ``CheckedMul`` 、 ``CheckedDiv`` 、 ``Bounded`` 、 ``NumCast`` 、 ``Num`` 、 ``Copy`` 、 ``Not`` 、 ``BitAnd`` 、 ``BitOr`` 、 ``BitXor`` 、 ``Shl`` 、 ``Shr`` 、 ``Eq`` 、 ``Ord`` 、 ``PartialOrd`` 。

提供：

* count_ones
* count_zeros
* leading_zeros
* trailing_zeros
* rotate_left
* rotate_right
* signed_shl
* signed_shr
* unsigned_shl
* unsigned_shr
* swap_bytes
* from_be
* from_le
* to_be
* to_le
* pow



範例：階乘 (Factorial)
------------------------------

.. code-block:: rust

    extern crate num;

    use std::iter::Product;
    use num::{PrimInt, one};

    /// Find the factorial of n
    fn factorial<T>(n: T) -> T
        where T: PrimInt + Product {
        num::range(one(), n + one()).product()
    }

    fn main() {
        println!("u8:  3! = {}", factorial(3_u8));
        println!("u16: 3! = {}", factorial(3_u16));
        println!("u32: 3! = {}", factorial(3_u32));
        println!("u64: 3! = {}", factorial(3_u64));
        // println!("u8:  9! = {}", factorial(9_u8));   // overflow
        // println!("u16: 9! = {}", factorial(9_u16));  // overflow
        println!("u32: 9! = {}", factorial(9_u32));
        println!("u64: 9! = {}", factorial(9_u64));
    }



參考
========================================

* `Generic numeric functions in safe, stable Rust with the num crate <https://travisf.net/rust-generic-numbers>`_
