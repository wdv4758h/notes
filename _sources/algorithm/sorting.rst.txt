========================================
Sorting
========================================


.. contents:: 目錄


介紹
========================================


屬性：

* stable
* partition
* adaptive
* parallel


記憶體需求：

* O(1)
* O(n)




參考
========================================

* `Wikipedia - Sorting Algorithm <https://en.wikipedia.org/wiki/Sorting_algorithm>`_
* `Wikipedia - External Sorting <https://en.wikipedia.org/wiki/External_sorting>`_
     - a class of sorting algorithms that can handle massive amounts of data
* `Wikipedia - Partial Sorting <https://en.wikipedia.org/wiki/Partial_sorting>`_
* `Rosetta Code - Sorting Algorithm <https://rosettacode.org/wiki/Category:Sorting_Algorithms>`_
* `Sort Benchmark <http://sortbenchmark.org/>`_
* `Rust - slice::sort <https://doc.rust-lang.org/std/primitive.slice.html#method.sort>`_
    - stable sort
    - need auxiliary memory
    - adaptive, iterative merge sort inspired by timsort
* `Rust - slice::sort_unstable <https://doc.rust-lang.org/std/primitive.slice.html#method.sort_unstable>`_
    - unstable sort
    - don't need auxiliary memory
    - pattern-defeating quicksort
    - combines the fast average case of randomized quicksort with the fast worst case of heapsort, while achieving linear time on slices with certain patterns


* Quicksort
* Merge sort
* Heapsort
* Introsort
* Blocksort
* Cubesort
* Gnome sort
* Smoothsort
* Selection Sort
* Insertion Sort
* Tree Sort
* Tim Sort
* Radix sort
* Bucket sort
* Counting Sort
* Gridsort
    - https://news.ycombinator.com/item?id=26062891
