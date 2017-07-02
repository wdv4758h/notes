C++ FAQ

- C++11 Language Extensions — General Features: https://isocpp.org/wiki/faq/cpp11-language
- C++14 Language Extensions: https://isocpp.org/wiki/faq/cpp14-language

Type Deduction/Template
-----------------------

- [C++11] auto type
- [C++11] foreach (range-based for)
- [C++11] initializer

  - map<int, char> m = {{1, 'a'}, {3, 'b'}, {5, 'c'}, {7, 'd'}};

- C++11 嘴砲: auto, decltype, trailing-return type: http://tommyjswu-blog.logdown.com/posts/736924-c-11-mouth-cannon-auto

Alias
-----
- type alias, like typedef: ``using size_t = int``
- alias template, typedef for template type: 

  - define: ``template <class T> vector_2d = std::vector<std::vector<T>>;``
  - use:    ``vector_2d<int> matrix;``

- namespace template: like python ``import as``

Rvalue Reference
----------------

http://stackoverflow.com/a/4986802

- rvalue reference: reference to rvalue and extend lifetime of rvalue (only constant rvalue?)
::
    
    std::vector<int> return_vector(void)
    {
        std::vector<int> tmp {1,2,3,4,5};
        return tmp;
    }

    std::vector<int> &&rval_ref = return_vector();

- move semantic: transfer rvalue to xvalue?

- RVO(return value optimization) & move constructor
::

    std::vector<int> return_vector(void)
    {
        std::vector<int> tmp {1,2,3,4,5};
        return tmp;
    }

    std::vector<int> rval_ref = return_vector();
    // compiler will use RVO if ok
    // OR fall back to vector's move constructor

Constant Expression
-------------------
constant expression in C++14: https://isocpp.org/wiki/faq/cpp14-language#extended-constexpr

example code::

    #include <iostream>

    constexpr auto fib(int n){
        if( n == 0 ){
            return 0;
        }
        if( n == 1 ){
            return 1;
        }

        return fib(n-1) + fib(n-2);
    }

    int main(int argc, char *argv[]){
        std::cout << fib(10) << std::endl;
        std::cout << fib(15) << std::endl;
        return 0;
    }
