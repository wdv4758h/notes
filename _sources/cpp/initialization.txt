========================================
Initialization
========================================

C++ 的初始化方式可以分成很多種，
七種 Initializer ：

* Default initialization
* Value initialization, e.g. std::string s{};
* Direct initialization, e.g. std::string s("hello");
* Copy initialization, e.g. std::string s = "hello";
* List initialization, e.g. std::string s{'a', 'b', 'c'};
* Aggregate initialization, e.g. char a[3] = {'a', 'b'};
* Reference initialization, e.g. char& c = a[0];


兩種 Static initialization：

1. Static initialization
2. Dynamic initialization


兩種 Dynamic non-local initialization：

1. Ordered dynamic initialization
2. Unordered dynamic initialization


兩種 Class member initialization：

1. Member initializer list
2. in-class brace-or-equal initializer


Reference
========================================

* `cppreference - Initialization <http://en.cppreference.com/w/cpp/language/initialization>`_
* `cppreference - direct initialization <http://en.cppreference.com/w/cpp/language/direct_initialization>`_
* `cppreference - reference initialization <http://en.cppreference.com/w/cpp/language/reference_initialization>`_
* `Wikipedia - Initialization (programming) <https://en.wikipedia.org/wiki/Initialization_%28programming%29>`_
