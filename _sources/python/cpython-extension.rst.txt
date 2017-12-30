========================================
CPython Extension
========================================


.. contents:: 目錄


pybind11 - C++11 <-> Python
========================================

:URL: https://github.com/pybind/pybind11
:Doc: http://pybind11.readthedocs.org/


pybind11 是一個 header only 的專案，
可以幫助使用 C++ 來撰寫 CPython extension。


範例一 - 簡單函式
------------------------------

.. code-block:: cpp

    #include <pybind11/pybind11.h>

    int add(int i, int j) {
        return i + j;
    }

    PYBIND11_MODULE(mymodule, m) {
        m.doc() = "pybind11 example plugin"; // optional module docstring
        // 函式參數和回傳值的型別會經過轉換
        // pybind11 支援許多內建的型別轉換
        m.def("add", &add, "A function which adds two numbers");
    }


範例二 - keyword arguments
------------------------------

.. code-block:: cpp

    #include <pybind11/pybind11.h>

    namespace py = pybind11;

    int add(int i, int j) {
        return i + j;
    }

    PYBIND11_MODULE(mymodule, m) {
        m.doc() = "pybind11 example plugin"; // optional module docstring
        m.def("add", &add, "A function which adds two numbers",
              py::arg("i"), py::arg("j"));
    }


.. code-block:: cpp

    #include <pybind11/pybind11.h>

    namespace py = pybind11;
    using namespace pybind11::literals;   // 使用 "_a" 後綴來宣告參數

    int add(int i, int j) {
        return i + j;
    }

    PYBIND11_MODULE(mymodule, m) {
        m.doc() = "pybind11 example plugin"; // optional module docstring
        m.def("add", &add, "A function which adds two numbers",
              "i"_a, "j"_a);
    }


範例三 - default arguments
------------------------------

.. code-block:: cpp

    #include <pybind11/pybind11.h>

    namespace py = pybind11;

    int add(int i, int j) {
        return i + j;
    }

    PYBIND11_MODULE(mymodule, m) {
        m.doc() = "pybind11 example plugin"; // optional module docstring
        m.def("add", &add, "A function which adds two numbers",
              py::arg("i") = 1, py::arg("j") = 3);
    }


Exporting Variables
------------------------------

.. code-block:: cpp

    PYBIND11_MODULE(example, m) {
        m.attr("the_answer") = 42;
        py::object world = py::cast("World");
        m.attr("what") = world;
    }


範例X - CMake + setuptools
------------------------------

型別轉換
------------------------------

:Doc: http://pybind11.readthedocs.io/en/stable/advanced/cast/index.html


定義新 class
------------------------------

Smart Pointer
------------------------------

Exception
------------------------------

Custom Type Casting
------------------------------

Communicate with Reference Counting
-----------------------------------
