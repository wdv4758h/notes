========================================
Pimpl
========================================

"Pimpl" == "pointer to implementation" == "Compilation Firewalls" == "Cheshire Cat"

Pimpl 是一個隱藏實作的技術，用於 C++ 或其他類似的 statically compiled languages。
做法是把實作的東西包成一個 class，在 header 檔只宣告這個 class，
而 class 內部有什麼則是另外再實作，
所以 header 檔裡面看到的會是對外的一些 interface 以及只有宣告的實作細節。


範例 code :

.. code-block:: cpp

    // widget.hpp

    #include <memory>

    class widget {

    public:

        widget();
        ~widget();

    private:

        class impl;
        std::unique_ptr<impl> pimpl;

    };

    ////////////////////////////////////////

    // widget.cpp

    #include "widget.hpp"

    class widget::impl {
        // implementation
    };

    widget::widget() : pimpl{ std::make_unique<impl>() } { }
    widget::~widget() = default;



優點：

* 更改實作時，用到這實作的 code 不用重新編譯



缺點：

* 實作者需要多做一些事
* 因為是間接的處理，所以執行期間的效能會稍稍的下降，尤其是 function calls 是 virtual 時，branch prediction 對於 indirect branches 通常效能會比較差
* code 可能比較難讀，因為一些資訊不在 header 檔裡面



要點：

* Pimpl object 應該要不能 shared，所以使用 unique_ptr (也比 shared_ptr 有效率)
* 在自己的實作裡面使用 Pimpl object，這樣可以把實作細節藏起來
* 在 out-of-line constructor 建立 Pimpl object
* 在自己實作裡仍需要寫 destructor，如此一來才會讓 compiler 在已經定義完實作 class 的地方建立 destructor，而不是讓 compiler 在原本的 header 檔那裡嘗試用不完整的型別建立 destructor
* 如果需要 copy & move assignment 的話，也需要在實作檔案裡寫上
* Pimpl 這種型別是非常 move-friendly 的，因為只需要 copy 一個 pointer 值
* 根據設計上來說，private 和 nonvirtual members 為 implementation details，只有這塊需要被 Pimpl 藏起來


.. image:: /images/cpp/pimpl.png
    :alt: Pimpl




Reference
========================================

* `GotW #100: Compilation Firewalls (Difficulty: 6/10) <http://herbsutter.com/gotw/_100/>`_
* `Pimpl Idiom <http://c2.com/cgi/wiki?PimplIdiom>`_
* `[2008] Dr.Dobb's - Making Pimpl Easy <http://www.drdobbs.com/cpp/making-pimpl-easy/205918714>`_
* `Wikipedia - Opaque pointer <https://en.wikipedia.org/wiki/Opaque_pointer>`_
* `Wikibooks - C++ Programming/Idioms <https://en.wikibooks.org/wiki/C++_Programming/Idioms#Pointer_To_Implementation_.28pImpl.29>`_
