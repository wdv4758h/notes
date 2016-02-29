#![feature(augmented_assignments)]
#![feature(op_assign_traits)]
#![feature(zero_one)]

/// Given an array of integers, every element appears twice except for one. Find that single one.
/// https://leetcode.com/problems/single-number/
///
/// properties :
///
/// * integer
/// * one unique integer
/// * others integers appears twice (or even times)
///
/// * two same integers do XOR equals to zero

use std::ops::BitXorAssign; // v1
use std::ops::BitXor;       // v2
use std::num::Zero;

pub fn get_odd_one_v1<T>(data: &Vec<T>) -> T
    where T: BitXorAssign<T> + Zero + Clone
{
    let mut number: T = T::zero();  // or use data[0]

    for i in data {
        number ^= i.clone();    // key point : XOR !!!
    }

    number
}

pub fn get_odd_one_v2<T>(data: &Vec<T>) -> T
    where T: BitXor<T, Output=T> + Zero + Clone
{
    data.iter()
        .fold(T::zero(), |acc, x| acc ^ x.clone())  // key point : XOR !!!
}
