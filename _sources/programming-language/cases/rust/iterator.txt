========================================
Iterator
========================================

Normal Use
========================================

Python :

.. code-block:: python

    >>> a = list(range(10))
    >>> a
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    >>> for i in a:
    ...     print(i)
    ...
    0
    1
    2
    3
    4
    5
    6
    7
    8
    9


Rust :

.. code-block:: rust

    fn main() {
        let a = 0..10;
        for i in a {
            println!("{}", i);
        }
    }

    // $ ./tmp
    // 0
    // 1
    // 2
    // 3
    // 4
    // 5
    // 6
    // 7
    // 8
    // 9



zip
========================================

Example 1
------------------------------

Python :

.. code-block:: python

    >>> a = list(range(10))
    >>> a
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    >>> list(zip(a, a))
    [(0, 0), (1, 1), (2, 2), (3, 3), (4, 4), (5, 5), (6, 6), (7, 7), (8, 8), (9, 9)]


Rust :

.. code-block:: rust

    fn main() {
        let a: Vec<_> = (0..10).collect();
        let result: Vec<_> = a.iter()
                              .zip(a.iter())
                              .collect();
        println!("{:?}", result);
    }

    fn main() {
        let result: Vec<_> = (0..10).zip(0..10).collect();
        println!("{:?}", result);
    }

    // $ ./tmp
    // [(0, 0), (1, 1), (2, 2), (3, 3), (4, 4), (5, 5), (6, 6), (7, 7), (8, 8), (9, 9)]


Example 2
------------------------------

Python :

.. code-block:: python

    >>> a = list(range(10))
    >>> a
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    >>> it1 = iter(a)
    >>> it2 = iter(a)
    >>> next(it2)
    0
    >>> list(zip(it1, it2))
    [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9)]


Rust :

.. code-block:: rust

    fn main() {
        let a: Vec<_> = (0..10).collect();
        let result: Vec<_> = a.iter()
                              .zip(a.iter().skip(1))
                              .collect();
        println!("{:?}", result);
    }

    // $ ./tmp
    // [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9)]



Reverse
------------------------------

Python :

.. code-block:: python

    >>> a = list(range(10))
    >>> a
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    >>> list(zip(a, a[::-1]))
    [(0, 9), (1, 8), (2, 7), (3, 6), (4, 5), (5, 4), (6, 3), (7, 2), (8, 1), (9, 0)]


Rust :

.. code-block:: rust

    fn main() {
        let a: Vec<_> = (0..10).collect();
        let result: Vec<_> = a.iter()
                              .zip(a.iter().rev())
                              .collect();
        println!("{:?}", result);
    }

    // $ ./tmp
    // [(0, 9), (1, 8), (2, 7), (3, 6), (4, 5), (5, 4), (6, 3), (7, 2), (8, 1), (9, 0)]



Example
------------------------------

.. code-block:: python

    >>> a = list(range(10))
    >>> a
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    >>> list(zip(*[iter(a)]*2))
    [(0, 1), (2, 3), (4, 5), (6, 7), (8, 9)]






Peakable
========================================

Rust :

.. code-block:: rust

    fn main() {
        let s = "這是測試";
        let mut it = s.chars().peekable();

        while !it.is_empty() {
            let (i, j) = (it.next(), it.peek());
            println!("{} {}", i.unwrap(), j.unwrap_or(&' '));
        }
    }


Output : ::

    這 是
    是 測
    測 試
    試


Reference
========================================

* `Rust - Module std::iter <https://doc.rust-lang.org/std/iter/index.html>`_
