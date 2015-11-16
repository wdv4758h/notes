fn main() {
    let fibonacci_i32_iter = (0..).scan((-1i32, 1), |state, _| {
        *state = (state.1, state.0 + state.1);
        Some(state.1)
    });

    let fibonacci_i64_iter = (0..).scan((-1i64, 1), |state, _| {
        *state = (state.1, state.0 + state.1);
        Some(state.1)
    });

    for (i, j) in fibonacci_i32_iter.take(47).enumerate() {
        println!("{:2}: {}", i, j);
    }

    println!("");

    for (i, j) in fibonacci_i64_iter.take(93).enumerate() {
        println!("{:2}: {}", i, j);
    }
}
