extern crate serde_pickle;


use std::collections::HashMap;
use std::fs::File;
use std::io::Write;     // write_all


fn main() {
    let mut map = HashMap::new();
    map.insert("x".to_string(), 1.0);
    map.insert("y".to_string(), 2.0);

    // Serialize the map into a pickle stream.
    // The second argument selects pickle version 3
    let serialized = serde_pickle::to_vec(&map, true).unwrap();
    let mut f = File::create("tmp.pickle").unwrap();
    let _ = f.write_all(&serialized);

    // Deserialize the pickle stream back into a map.
    // Because we compare it to the original `map` below, Rust infers
    // the type of `deserialized` and lets serde work its magic.
    let deserialized = serde_pickle::from_slice(&serialized).unwrap();
    assert_eq!(map, deserialized);
}
