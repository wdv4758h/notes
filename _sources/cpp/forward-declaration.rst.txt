========================================
Forward Declaration
========================================


.. contents:: 目錄


介紹
========================================

在了解 Forward Declaration 之前，
先了解 Circular Dependency 的問題，
其狀況為有兩個 class 互相依賴，
但是所以沒辦法把 class A 先定義好再定義 class B，
C++ 編譯器會沒有足夠的資訊來處理，
解決方案是使用 Forward Declaration，
先宣告好 class 但不實做，
後面就可以正常地拿來用。

範例：

.. code-block:: cpp

    class A;    // forward declaration
    class B;    // forward declaration

    class B {
    public:
        A* a;
    };

    class A {
    public:
        B* b;
    };

    int main() {
        return 0;
    }


（Circular Dependency 有時候又被稱為 Circular Reference，
但是這又會跟 Reference Counting 技術中的 Circular Reference 撞名。）



參考
========================================

* `Wikipedia - Circular Dependency <https://en.wikipedia.org/wiki/Circular_dependency>`_
* `Wikipedia - Forward Declaration <https://en.wikipedia.org/wiki/Forward_declaration>`_
* `What's wrong with circular references? <http://softwareengineering.stackexchange.com/a/12030/254958>`_
