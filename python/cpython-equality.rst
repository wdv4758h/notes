========================================
CPython Equality
========================================

CPython 的 dictionary 在比較相等性時會先看兩個 dictionary 的長度是否一樣，
一樣的話再爬進去比裡面各個項目是否都被包含在另外一個 dictionary。

.. code-block:: c

    // Objects/dictobject.c

    ////////////////////////////////////////

    // dictview_richcompare

    case Py_NE:
    case Py_EQ:
        if (len_self == len_other)
            ok = all_contained_in(self, other);
        if (op == Py_NE && ok >= 0)
            ok = !ok;
        break;

    ////////////////////////////////////////

    // all_contained_in

    for (;;) {
        PyObject *next = PyIter_Next(iter);
        ...
        ok = PySequence_Contains(other, next);
    }
