========================================
Numeric
========================================


.. contents:: 目錄


num
========================================

``num`` 提供了一些數值相關的型別和 Trait，
可以藉此來撰寫數學相關函式。


Num Trait
------------------------------

``Num`` 表示型別為數值，
隱含了定義數值的零、一、加減乘除、餘數、Partial Equal。


Integer Trait
------------------------------

``Integer`` 表示型別為整數，
隱含 ``Eq`` 、 ``Ord`` 、 ``PartialOrd`` 、 ``Num`` 。


PrimInt Trait
------------------------------

``PrimInt`` 針對一些 Primitive 的整數提供一些操作，
例如計算 leading zeros、trailing zeros、big/little endian 轉換等等。


Bounded Trait
------------------------------

``Bounded`` 表示數值有上下界。


範例：階乘 (Factorial)
------------------------------

.. code-block:: rust

    extern crate num;

    use std::iter::Product;
    use num::{PrimInt, Unsigned};

    /// Find the factorial of n
    fn factorial<T>(n: T) -> T
        where T: PrimInt + Unsigned + Product
    {
        num::range(T::one(), n + T::one()).product()
    }


.. code-block:: rust

    fn main() {
        println!("u8: 3! = {}", factorial(3_u8));
        println!("u16: 3! = {}", factorial(3_u16));
        println!("u32: 3! = {}", factorial(3_u32));
        println!("u64: 3! = {}", factorial(3_u64));

        // println!("u8: 9! = {}", factorial(9_u8));    // overflow
        // println!("u16: 9! = {}", factorial(9_u16));  // overflow
        println!("u32: 9! = {}", factorial(9_u32));
        println!("u64: 9! = {}", factorial(9_u64));
    }



參考
========================================

* `Generic numeric functions in safe, stable Rust with the num crate <https://travisf.net/rust-generic-numbers>`_
