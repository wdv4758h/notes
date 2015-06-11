Stack & Heap
=========================================

在講記憶體管理的一開始，我們先來看看資料在記憶體中是如何被放置的。

Linux process :

.. image:: images/memory-management/Linux-Address-Layout.png
    :alt: Linux Address Layout

其中 Stack 是 **local variables** 和 **function parameters** 的地方，
每呼叫一次 function 就會 push 一個 stack frame 進去，
每次 function 回傳時就會被清掉。

[Error] 這邊可以注意到，如果我們不斷地 push 到 stack 裡，
最後超過可容許的大小，就會產生 ``stack overflow``

因為放在 stack 上的資料會在回傳時被清掉，
當遇到回傳後仍需使用的情況，
就要把資料放在 Heap。

在 C 中要使用 Heap 就需要用 **malloc** 並設定需要的大小，
用完後需要使用 **free** 來清除。
這些步驟在一般使用 Stack 的情況中都不需要，
但是 Heap 的特別處就在於不會受限於特定的 scope 裡，
就算 function 回傳還是可以正常使用，也常用動態決定資料大小的情況。

Common Memory Problem
=========================================

管理

* double free (清多次)
* memory leak (沒清到)

使用

* use after free (清了還用)
* dangling pointer (清了還用)
* heap overflow (寫超過)
* stack buffer overflow (寫超過)
* buffer over-read (讀超過)
* stack overflow (用太多)

Debugger
=========================================

* Valgrind

RAII (Resource Acquisition Is Initialization)
=============================================

RAII 為在數個 OO 語言中使用的 programming idiom，
為 C++ 於 1984 到 1989 年間發展出來，主要由 Bjarne Stroustrup 和 Andrew Koenig 來完成，
後來也用於 D、Ada、Vala、Rust 等語言。

主要概念為把資源和物件的 lifetime 綁在一起，
當物件由 constructor 建立時，就做 resource allocation，
當物件由 destructor 拆掉時，就做 resource deallocation，
如此一來只要物件正常的拆掉，就不會有 resource leak 發生。

Ownership
=========================================

Garbage Collection
=========================================

Cases
=========================================

* Python
    - CPython : GC with reference counting
    - PyPy : GC with incremental generational tracing (incminimark)

Reference
=========================================

* `[2009] Anatomy of a Program in Memory <http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/>`_
* `[2013] Using the Pointer Ownership Model to Secure Memory Management in C and C++ <http://blog.sei.cmu.edu/post.cfm/using-the-pointer-ownership-model-to-secure-memory-management-in-c-and-c>`_
