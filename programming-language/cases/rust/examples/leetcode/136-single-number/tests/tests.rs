extern crate leetcode;

use leetcode::*;

#[test]
fn test_get_odd_one() {
    assert_eq!(get_odd_one_v1(&vec![1_i8, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
    assert_eq!(get_odd_one_v1(&vec![1_i16, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
    assert_eq!(get_odd_one_v1(&vec![1_i32, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
    assert_eq!(get_odd_one_v1(&vec![1_i64, 2, 3, 1, 2, 4, 7, 7, 3]), 4);

    assert_eq!(get_odd_one_v2(&vec![1_i8, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
    assert_eq!(get_odd_one_v2(&vec![1_i16, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
    assert_eq!(get_odd_one_v2(&vec![1_i32, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
    assert_eq!(get_odd_one_v2(&vec![1_i64, 2, 3, 1, 2, 4, 7, 7, 3]), 4);
}
