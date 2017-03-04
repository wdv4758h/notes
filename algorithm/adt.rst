========================================
ADT (Abstract Data Type)
========================================


.. contents:: 目錄


介紹
========================================

ADT 是抽象化過的資料型別，
定義的是型別的操作方式，
不限定實做方法，
藉此使用者只要知道操作界面即可，
不需要了解到實做細節，
當實做改變時也不會受影響而需要重新撰寫程式。



Stack (LIFO)
========================================

Stack 保證的是 LIFO （Last In, First Out），
也就是後進先出，
需要有以下操作：

* push：放入新資料
* pop：移除最新的資料並回傳

其他可能的擴充：

* top：查看最新的資料
* empty：回傳是否為空的


可能的實做方式：

* Array
* Singly Linked List



Queue (FIFO)
========================================

Queue 保證的是 FIFO （First In, First Out），
也就是先進先出，
需要有以下操作：

* enqueue：放入新資料
* dequeue：移除最舊的資料並回傳

其他可能的擴充：

* front：查看最舊的資料
* empty：回傳是否為空的


可能的實做方式：

* Linked List
    - Doublely Linked List
    - Singly Linked List （額外紀錄頭尾的指標來增加效率）
* Circular Buffer
* Deque （把 Queue 當成 Deque 的特例）



Deque (Double-ended Queue)
========================================

Deque 是比 Queue 更有彈性的結構，
可以從頭或尾加入或刪除，
需要有以下操作：

* insert_front：從開頭插入新資料
* insert_back：從結尾插入新資料
* remove_front：從開頭刪除資料
* remove_back：從結尾刪除資料

其他可能的擴充：

* front：查看結尾的資料
* back：查看開頭的資料
* empty：回傳是否為空的


可能的實做方式：

* Doubly Linked List
* Dynamic Array （Array Deque）



List
========================================

List 是用來表示有限的資料（無限的資料會用 Steam 表示），
而且資料的插入順序會被保存並且可以重複，
需要有以下操作：

* append：在尾端插入新資料
* prepend：在開頭插入新資料
* head：回傳第一筆資料
* tail：回傳除了第一筆資料外的剩餘資料

其他可能的擴充：

* empty：回傳是否為空的


可能的實做方式：

* Linked List
* Array
* Self-balancing Binary Search Tree



Set
========================================

Set 是用來表示有限的資料，
而且資料的插入順序 **不會** 被保存並且 **不會** 重複，
需要有以下操作：

* add
* remove
* is_element_of


其他可能的擴充：

* union
* intersection
* difference
* subset

* is_empty
* size/cardinality
* iterate
* enumerate
* pop
* pick
* map
* filter
* fold
* clear
* equal
* hash
* sum
* collapse
* flatten
* nearest
* min
* max


可能的實做方式：

* List （比較沒效率）
* Hash Table
* Self-balancing Binary Search Tree
    - Red-Black Tree
* Trie



Multiset
========================================

MultiSet 類似 Set，
但是允許重複的資料，
依照需求可能會把相同的值視為同一個資料，
並另外用計數器做紀錄，
或是視為相同值但不同的資料，
一樣把資料存進去，
而 MultiSet 儲存資料的順序可以是有序也可以是無序的。



Map (Dictionary) (Associative Array)
========================================

Map 是用來表示一連串 (key, value) pairs，
需要有以下操作：

* add：
* remove
* modify
* lookup

其他可能的擴充：

* iterate
* iterate_values
* iterate_keys


可能的實做方式：

* Hash Table
* Search Tree
    - Self-balancing Binary Search Tree
    - Unbalanced Binary Search Tree
* Sequential Container


Multimap
========================================

Multimap 是用來表示一連串 (key, value) pairs，
跟 Map 的差別在於一個 key 可以對應到多個 value，
需要有以下操作：

* add：
* remove
* modify
* lookup

其他可能的擴充：

* iterate
* iterate_values
* iterate_keys


可能的實做方式：

* Map with List
* Set as Map value



Priority Queue
========================================

Priority Queue 類似一般的 Stack 或 Queue，
但是額外加了 Priority 的性質，
Priority 比較高的資料會排比較前面，
以 Stack 來說就是越晚加入的資料 Priority 越高，
以 Queue 來說就是越早加入的資料 Priority 越高，
但是 Priority Queue 則是可以客製化 Priority 的決定方式，
需要有以下操作：

* insert_with_priority
* pull_highest_priority_element

其他可能的擴充：

* peek
* pull_lowest_priority_element


可能的實做方式：

* Unordered Array （沒效率）
* Heap
* Self-balancing Binary Search Tree


另外 Priority Queue 也可以用於排序上面，
把資料放入 Priority Queue 後再取出來，
就會依照順序排好，
對照：

+----------------+-----------------------------------+----------+----------+----------+
| Sorting        | Priority Queue                    | Best     | Average  | Worst    |
+================+===================================+==========+==========+==========+
| Heapsort       | Heap                              | n log(n) | n log(n) | n log(n) |
+----------------+-----------------------------------+----------+----------+----------+
| Smoothsort     | Leonardo Heap                     | n        | n log(n) | n log(n) |
+----------------+-----------------------------------+----------+----------+----------+
| Selection Sort | Unordered Array                   | n^2      | n^2      | n^2      |
+----------------+-----------------------------------+----------+----------+----------+
| Insertion Sort | Ordered Array                     | n        | n^2      | n^2      |
+----------------+-----------------------------------+----------+----------+----------+
| Tree Sort      | Self-balancing Binary Search Tree | n log(n) | n log(n) | n log(n) |
+----------------+-----------------------------------+----------+----------+----------+



DEPQ (Double-ended Priority Queue) (Double-ended Heap)
======================================================

DEPQ 類似 Priority Queue，
但是額外提供有效率的方式可以移除最大或最小的值，
不像 Priority Queue 只有一邊是有效率的，

需要有以下操作：

* insert
* get_min
* get_max
* remove_min
* remove_max


其他可能的擴充：

* size
* is_empty


可能的實做方式：

* Heap
    - Min-Max Heap
    - Pairing Heap
* Self-balancing Binary Search Tree


應用：

* External Sorting



Graph
========================================

Graph 是一種實做了數學中的有向圖或無向圖的 ADT，
儲存了許多節點和路徑，
需要有以下操作：

* adjacent
* neighbors
* add_vertex
* remove_vertex
* add_edge
* remove_edge
* get_vertex_value
* set_vertex_value


其他可能的擴充：

* get_edge_value
* set_edge_value


可能的實做方式：

* Adjacency List
* Adjacency Matrix
* Incidence Matrix



參考
========================================

* `Wikipedia - Abstract data type <https://en.wikipedia.org/wiki/Abstract_data_type>`_
* `Wikipedia - Stack <https://en.wikipedia.org/wiki/Stack_(abstract_data_type)>`_
* `Wikipedia - Queue <https://en.wikipedia.org/wiki/Queue_(abstract_data_type)>`_
* `Wikipedia - Double-ended Queue <https://en.wikipedia.org/wiki/Double-ended_queue>`_
* `Wikipedia - List <https://en.wikipedia.org/wiki/List_(abstract_data_type)>`_
* `Wikipedia - Associative Array <https://en.wikipedia.org/wiki/Associative_array>`_
* `Wikipedia - Multimap <https://en.wikipedia.org/wiki/Multimap>`_
* `Wikipedia - Priority Queue <https://en.wikipedia.org/wiki/Priority_queue>`_
* `Wikipedia - Array <https://en.wikipedia.org/wiki/Array_data_type>`_
* `Wikipedia - Double-ended Priority Queue <https://en.wikipedia.org/wiki/Double-ended_priority_queue>`_
* `Wikipedia - Graph <https://en.wikipedia.org/wiki/Graph_(abstract_data_type)>`_
