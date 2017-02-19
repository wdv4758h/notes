========================================
Smart Pointer
========================================


.. contents:: 目錄


介紹
========================================

C++11 開始廣泛採用 Smart Pointer 的概念
（在這之前其實有 ``auto_ptr`` 但是現在建議用 ``unique_ptr`` 取代），
藉由 Ownership 的控管來決定動態分配的記憶體何時要回收。


在 ``<memory>`` 裡有以下幾種 pointer：

* unique_ptr
    - 獨占的 Ownership
    - 不可複製
    - 可以用 **std::move()** 轉移所有權
* shared_ptr
    - 共享的 Ownership
    - 使用 Reference Counting
    - 當 counter 變成 0 時就回收
* weak_ptr
    - 類似 shared_ptr，但是沒有權利回收資源
    - 不會增加 Reference Counting 的計算
    - 不能用來做資料的存取，主要用來監控 shared_ptr 的狀況


有了 Ownership 後只要擁有者都不見了就代表可以清掉，
其中 C++ 有好幾種 pointer 來指定 ownership，
**unique_ptr** 可以指定說只有自己是擁有者，
自己不用時就可以清掉，不用管其他人，
**shared_ptr** 則是指定說會有多個人分享、使用，
當大家都不用時才清掉，
**weak_ptr** 則是和 shared_ptr 類似，
但是沒有清除的權利，也不會被算進資源的使用者裡，當 shared_ptr 要清掉時，不用理 weak_ptr。


相關程式碼可以看 `範例 <./examples/smart-pointer.cpp>`_



相關注意事項
========================================

* unique_ptr 和 shared_ptr 都能和 nullptr 做比較，以確認指標是否有效
* 要強制釋放 Smart Pointer 所擁有的資源可以呼叫 reset 函式
* 用 shared_ptr 來管理 C-style array 時，要自己給額外的 delete 函式
    - shared_ptr 預設會用 delete ptr 來釋放資源
    - 需要自己寫 delete 函式，例如： ``shared_ptr<int> foo(new int[3], [](int* ptr){ delete [] ptr; });``
    - 用 ``std::array`` 就沒這個問題



參考
========================================

* `Wikipedia - Smart pointer <https://en.wikipedia.org/wiki/Smart_pointer>`_
* `cppreference - Dynamic memory management <http://en.cppreference.com/w/cpp/memory>`_
* `避免 memory leak：C++11 Smart Pointer（上） <https://kheresy.wordpress.com/2012/03/03/c11_smartpointer_p1/>`_
* `避免 memory leak：C++11 Smart Pointer（下） <https://kheresy.wordpress.com/2012/03/05/c11_smartpointer_p2/>`_
