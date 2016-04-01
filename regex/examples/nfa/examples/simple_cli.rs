extern crate nfa;

use nfa::*;

use std::env;

fn main() {
    let mut args = env::args().skip(1);

    let regex = args.next().unwrap();
    println!("[origin] {}", regex);

    let postfix = regex_to_postfix(regex).unwrap();
    println!("[postfix] {}", postfix);
}
