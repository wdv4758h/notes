use std::cmp::Ordering;
use std::collections::{HashMap, BinaryHeap};


#[derive(Eq, PartialEq, Debug)]
struct Huffman {
    weight: u32,
    data: Vec<HuffmanData>,
}

#[derive(Eq, PartialEq, Debug)]
struct HuffmanData {
    symbol: char,
    code: String,
}

// The priority queue depends on `Ord`.
// Explicitly implement the trait so the queue becomes a min-heap
// instead of a max-heap.
impl Ord for Huffman {
    fn cmp(&self, other: &Self) -> Ordering {
        // Notice that the we flip the ordering here
        other.weight.cmp(&self.weight)
    }
}

// `PartialOrd` needs to be implemented as well.
impl PartialOrd for Huffman {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}


fn count_frequency(data: &String) -> HashMap<char, u32> {
    let mut counter = HashMap::new();
    for key in data.chars() {
        *counter.entry(key).or_insert(0) += 1;
    }
    counter
}

fn get_huffman_code(sym2freq: &HashMap<char, u32>) -> Vec<HuffmanData> {
    let mut heap = BinaryHeap::new();
    for (key, value) in sym2freq.iter() {
        let tmp = Huffman {
            weight: *value,
            data: vec![
                HuffmanData {
                    symbol: *key,
                    code: Default::default(),
                }
            ],
        };
        heap.push(tmp);
    }

    // bottom up
    while heap.len() > 1 {
        let mut item1 = heap.pop().unwrap();
        let mut item2 = heap.pop().unwrap();
        for i in item1.data.iter_mut() {
            i.code.push('0');
        }
        for i in item2.data.iter_mut() {
            i.code.push('1');
        }
        item1.data.append(&mut item2.data);   // cost
        heap.push(
            Huffman {
                weight: item1.weight+item2.weight,
                data: item1.data,
            }
        );
    }

    let mut result = {
        let tmp = heap.pop().unwrap();
        tmp.data
    };

    // reverse, so the result will become top down
    for i in result.iter_mut() { i.code = i.code.chars().rev().collect::<String>(); }
    result.sort_by(|a, b| a.code.len().cmp(&b.code.len()));
    result
}

fn main() {
    let data = "this is an example for huffman encoding".to_string();
    let sym2freq = count_frequency(&data);
    let table = get_huffman_code(&sym2freq);

    println!("Symbol | Weight | Huffman Code");
    println!("====== | ====== | ============");
    for i in table.iter() {
        println!("{:<6} | {:<6} | {}", i.symbol, sym2freq[&i.symbol], i.code);
    }
}

/* result

Symbol | Weight | Huffman Code
====== | ====== | ============
n      | 4      | 011
       | 6      | 111
o      | 2      | 0000
h      | 2      | 0010
m      | 2      | 0011
s      | 2      | 0101
a      | 3      | 1001
f      | 3      | 1010
i      | 3      | 1100
e      | 3      | 1101
x      | 1      | 00010
r      | 1      | 00011
g      | 1      | 01000
l      | 1      | 01001
t      | 1      | 10000
c      | 1      | 10001
d      | 1      | 10110
u      | 1      | 101110
p      | 1      | 101111

*/
