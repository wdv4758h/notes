===========================================
CRTP (Curiously recurring template pattern)
===========================================

CRTP 是一種 static polymorphism 的方式，
在 Base class 留有 Template 做操作，
後續在繼承時把 Child class 放入 Template 的位置，
如此一來可以在 Compile Time 做好檢查 (Static)，
不需要動態的 Cost (vtable)

.. code-block:: cpp

    // The Curiously Recurring Template Pattern (CRTP)
    template<class T>
    class Base
    {
        // methods within Base can use template to access members of Derived
    };
    class Derived : public Base<Derived>
    {
        // ...
    };


缺點是失去某些動態才會產生需要的 class 的特殊情況？ (我猜應該很少？)
優點是有 compiler 幫你檢查而且 run time 不用 vtable 的 cost


Reference
===========================================

* `Wikipedia - Curiously recurring template pattern <https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern>`_
