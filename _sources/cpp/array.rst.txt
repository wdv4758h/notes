========================================
std::array
========================================


.. contents:: 目錄


介紹
========================================

C++ 除了 C-style Array 外，
STL 內還有 ``std::array`` 可以使用，
``std::array`` 是一個 Aggreate Type，
為 C-style Array 的 thin wrapper。

優點：

* 可以提供 iterator 相關支援，以便和 STL 內的其他演算法一起使用，
* 和 C-style Array 相比可以在型別上知道長度，
* 不會被自動轉成 ``T*`` ，可以避免誤傳
* 有 copy constructor 和 assignment constructor，使用上比較方便
* 效能方面理論上等同於 C-stye Array。

缺點：

* 需要 include
* 寫起來較長



.. code-block:: cpp

    #include <array>

    int main() {
        std::array<int, 3> foo = {1, 2, 3};
        foo[0] = 42;            // no bounds checking
        foo.at(1) = 42;         // with bounds checking
        std::get<2>(foo) = 42;  // use std::get template function
                                // compile-time bounds checking
    }



注意事項
========================================

* 使用 ``operator[]`` 一樣沒有 bounds checking，所以存取出超出範圍的值跟 C-style 一樣不會噴 exception
    - 使用 ``at`` 的話就有 bounds checking，不在範圍內會噴 exception



參考
========================================

* `cppreference - std::array <http://en.cppreference.com/w/cpp/container/array>`_
* `Why is there std: :array<> in C++11? What are the benefits of it? <https://www.quora.com/Why-is-there-std-array-in-C++11-What-are-the-benefits-of-it>`_
