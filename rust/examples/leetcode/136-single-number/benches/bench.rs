#![feature(test)]

extern crate test;
extern crate leetcode;

use test::Bencher;
use leetcode::*;


#[bench]
fn bench_i8_v1(b: &mut Bencher) {
    b.iter(|| get_odd_one_v1(&vec![1_i8, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_i16_v1(b: &mut Bencher) {
    b.iter(|| get_odd_one_v1(&vec![1_i16, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_i32_v1(b: &mut Bencher) {
    b.iter(|| get_odd_one_v1(&vec![1_i32, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_i64_v1(b: &mut Bencher) {
    b.iter(|| get_odd_one_v1(&vec![1_i64, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_isize_v1(b: &mut Bencher) {
    b.iter(|| get_odd_one_v1(&vec![1_isize, 2, 3, 1, 2, 4, 7, 7, 3]));
}



#[bench]
fn bench_i8_v2(b: &mut Bencher) {
    b.iter(|| get_odd_one_v2(&vec![1_i8, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_i16_v2(b: &mut Bencher) {
    b.iter(|| get_odd_one_v2(&vec![1_i16, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_i32_v2(b: &mut Bencher) {
    b.iter(|| get_odd_one_v2(&vec![1_i32, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_i64_v2(b: &mut Bencher) {
    b.iter(|| get_odd_one_v2(&vec![1_i64, 2, 3, 1, 2, 4, 7, 7, 3]));
}

#[bench]
fn bench_isize_v2(b: &mut Bencher) {
    b.iter(|| get_odd_one_v2(&vec![1_isize, 2, 3, 1, 2, 4, 7, 7, 3]));
}
