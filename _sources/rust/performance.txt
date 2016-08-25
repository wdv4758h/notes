========================================
Rust's Performance
========================================

+----------+--------------------------------------------+
| 類別     | 狀況                                       |
+==========+============================================+
| Compiler | rustc 1.3.0-nightly (69ca01256 2015-07-23) |
+----------+--------------------------------------------+
| Options  | -C opt-level-3                             |
+----------+--------------------------------------------+

Interesting Topic
========================================

* SIMD
    - `Rust - Module std::simd <https://doc.rust-lang.org/std/simd/>`_



Iterator
========================================

已知數字做 filter
------------------------------

這份 code 可以在優化的時候事先算出 "499999999500000000" 後直接放入：

.. code-block:: rust

    #![feature(iter_arith)]

    fn main() {
        let result: u64 = (1..1000000000).sum();
        println!("{}", result);
    }


但是這個卻不行，優化開下去之後還是需要經過 runtime 的計算：

.. code-block:: rust

    #![feature(iter_arith)]

    fn main() {
        let result: u64 = (1..1000000000).filter(|&x| x > 0).sum();
        println!("{}", result);
    }


感覺應該要可以優化掉？


str::contains & pattern matching
--------------------------------

.. code-block:: rust

    #![feature(convert)]

    use std::io::Read;

    fn tokenize1(text: &str) -> Vec<&str> {
        let delims = [' ', ',', '.', '!', '?', ';', '\'', '"', ':', '\t', '\n', '(', ')', '-'];
        text.split(|c| {
                for &x in delims.iter() {
                    if x == c {
                        return true;
                    }
                }
                return false;
            })
            .filter(|data| !data.is_empty())
            .collect()
    }

    fn tokenize2(text: &str) -> Vec<&str> {
        text.split(|c| {
                match c {
                    ' '  => true,
                    ','  => true,
                    '.'  => true,
                    '!'  => true,
                    '?'  => true,
                    ';'  => true,
                    '\'' => true,
                    '"'  => true,
                    ':'  => true,
                    '\t' => true,
                    '\n' => true,
                    '('  => true,
                    ')'  => true,
                    '-'  => true,
                    _    => false
                }
            })
            .filter(|data| !data.is_empty())
            .collect()
    }

    fn tokenize3(text: &str) -> Vec<&str> {
        let delims = " ,.!?;'\":\t\n()-";
        text.split(|c| str::contains(&delims, c))
            .filter(|data| !data.is_empty())
            .collect()
    }

    fn main() {
        let mut stdin = std::io::stdin();
        let mut tmp = String::new();
        stdin.read_to_string(&mut tmp);
        let result1 = tokenize1(tmp.as_str());
        let result2 = tokenize2(tmp.as_str());
        let result3 = tokenize3(tmp.as_str());
    }

隨便生一個 73 MB 的檔案下去測，
結果發現 pattern matching 的版本最快，
``str::contains`` 的版本最慢，
覺得可以做優化 ...

+-----------+------------------+--------+
| function  | type             | speed  |
+===========+==================+========+
| tokenize1 | for loop         | 1.30 s |
+-----------+------------------+--------+
| tokenize2 | pattern matching | 0.80 s |
+-----------+------------------+--------+
| tokenize3 | str::contains    | 2.45 s |
+-----------+------------------+--------+



Benchmarks Game
========================================

* `[Bitbucket] ewanhiggs/csv-game <https://bitbucket.org/ewanhiggs/csv-game>`_
    - Rust is the fastest now (almost the same as C)
* `[GitHub] kostya/benchmarks <https://github.com/kostya/benchmarks>`_
    - Rust still need some improvement
