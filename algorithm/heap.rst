========================================
Heap （堆）
========================================


Heap 基本介紹
========================================

這裡的 Heap 指的是資料結構上的 Heap，
不是在討論記憶體時所提到的 Heap （動態分配的記憶體）。

Heap 是特殊的樹狀資料結構，
它符合 Heap 的性質，
也就是每對父節點和其子節點都符合同樣的關聯（例如：大於、小於）。
當所有父節點都大於其子節點時，就稱其為「Max Heap」。
當所有父節點都小於其子節點時，就稱其為「Min Heap」。
Heap 不是完全排序過的資料結構，但可以視為部份有序。

Heap 常被作為 Priority Queue （一種 Abstract Data Type）的實作方式。
而一個 Heap 常見的實作為 Binary Heap，它的樹為 Complete Binary Tree。
Heap 在一些圖論的演算法中扮演極其重要的地位，例如 Dijkstra 演算法。
其他還有在排序中的使用，例如 Heapsort。


常見操作
========================================

基本：

* find-min/find-max
* insert
* extract-min/extract-max
* delete-min/delete-max
* replace

建立：

* create-heap
* heapify
* merge (union)
* meld

檢視：

* size
* is-empty

內部：

* decrease-key/increase-key
* delete
* shift-up
* shift-down


實作
========================================

Heap 通常會使用 Array （固定大小或動態決定大小），
如此一來每個資料間就不需要指標來連繫。
當有新的資料插入 Heap 或從 Heap 中移除時，
Heap 的性質可能會被違反，
此時就必須利用內部的操作平衡。

想從已經有資料的 Array 建立 Heap 可利用 Floyd 演算法，
該演算法只需要線性（Linear）時間即可建立（O(n)），
比起從空的 Heap 開始建立所需的對數線性（Log-linear）時間（O(n log(n))）還要快。
