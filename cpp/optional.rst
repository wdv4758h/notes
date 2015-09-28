========================================
Optional
========================================

(Maybe Monad in C++ ~)


Example :

.. code-block:: cpp

    #include <iostream>
    #include <experimental/optional>

    int main() {
        std::experimental::optional<int> x;     // x has no value

        try {
            x.value();
        } catch(const std::logic_error& e) {
            std::cout << e.what() << '\n';      // "Attempt to access value of a disengaged optional object"
        }

        std::cout << x.value_or(0) << std::endl;    // 0

        return 0;
    }


Build & Run :

.. code-block:: sh

    $ [gcc|clang] -std=c++14 example.cpp
    $ ./a.out


Reference
========================================

* `C++ - std::experimental::optional <http://en.cppreference.com/w/cpp/experimental/optional>`_
* `Wikipedia - Option type <https://en.wikipedia.org/wiki/Option_type>`_
