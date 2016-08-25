========================================
Return Value Optimization
========================================

Speed :

::

    RVO/NRVO > Move > Copy


* `Lesson #5: Move Semantics <https://mbevin.wordpress.com/2012/11/20/move-semantics/>`_
* `RVO V.S. std::move <https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/RVO_V_S_std_move>`_

* `cppreference - copy elision <http://en.cppreference.com/w/cpp/language/copy_elision>`_
    - Optimizes out copy- and move-constructors, resulting in zero-copy pass-by-value semantics
    - 當 local variable 建立時，其實是直接建立在原先 return value 會被 copy 或 move 到的地方，如此一來就不會有額外的 copy 或 move 操作

* `More C++ Idioms - Computational Constructor <https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Computational_Constructor>`_
* `Wikipedia - Return value optimization <https://en.wikipedia.org/wiki/Return_value_optimization>`_
* `GotW #4 Solution: Class Mechanics <http://herbsutter.com/2013/05/20/gotw-4-class-mechanics/>`_
* `Better Optimization for Structure Copies <http://nondot.org/sabre/LLVMNotes/BetterStructureCopyOptimization.txt>`_
