========================================
RVO (Return Value Optimization)
========================================

RVO 和 NRVO（Named Return Value Optimization）是 C++ 中的一項編譯器優化技術，
可以減少 Temporary Object 的產生和 Copy 的呼叫，
使用這像優化技術後物件的記憶體位置可能會直接建立在原本要回傳的記憶體位置，
因此物件記憶體位置可能不在現有的 Stack Frame 範圍內，
而在別人的 Stack 上。

以效能來來說，
套用 RVO/NRVO 技術的狀況會比採用 Move Constructor 來的快，
Move Constructor 又比 Copy Constructor 來的快。

::

    RVO/NRVO > Move > Copy


參考
========================================

* `Lesson #5: Move Semantics <https://mbevin.wordpress.com/2012/11/20/move-semantics/>`_
* `RVO V.S. std::move <https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/RVO_V_S_std_move>`_
* `cppreference - copy elision <http://en.cppreference.com/w/cpp/language/copy_elision>`_
    - Optimizes out copy- and move-constructors, resulting in zero-copy pass-by-value semantics
    - 當 local variable 建立時，其實是直接建立在原先 return value 會被 copy 或 move 到的地方，如此一來就不會有額外的 copy 或 move 操作
* `More C++ Idioms - Computational Constructor <https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Computational_Constructor>`_
* `Wikipedia - Return value optimization <https://en.wikipedia.org/wiki/Return_value_optimization>`_
* `GotW #4 Solution: Class Mechanics <http://herbsutter.com/2013/05/20/gotw-4-class-mechanics/>`_
* `Better Optimization for Structure Copies <http://nondot.org/sabre/LLVMNotes/BetterStructureCopyOptimization.txt>`_
