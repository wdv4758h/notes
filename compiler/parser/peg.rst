========================================
PEG (Parsing Expression Grammar)
========================================

.. contents:: Table of Contents


PEGTL Examples
========================================

Introduction
------------------------------

`PEGTL <https://github.com/colinh/pegtl>`_ 是一個 C++ 實作的 parser generator，
內部使用 PEG 來做 parsing，
用 template 的方式來實作。
使用時把 grammar 用內建的 template 做成對應的 class，
並且實作對應的 action，
如此一來就完成需要的 parser 了。

(如果這專案有 DSL 的話寫起來會更方便 ...)


簡易數字相加
------------------------------

.. code-block:: cpp

    // add.cpp

    #include <pegtl.hh>     // PEGTL

    #include <iostream>

    namespace myparser {

        // parsing rule: \d+
        struct number
            : pegtl::plus< pegtl::digit > {};

        // parsing rule: \+
        struct add
            : pegtl::one< '+' > {};

        // parsing rule: ^\d+\+\d+$
        // exception on failure
        struct grammar
            : pegtl::must< number, add, number, pegtl::eof > {};


        // class template to define actions
        // do nothing by default
        template< typename Rule >
        struct action
            : pegtl::nothing< Rule > {};

        // action for "number"
        template<> struct action< number > {
            static void apply( const pegtl::input & in , int& sum ) {
                sum += std::stoi(in.string());
            }
        };

    }

    int main( int argc, char * argv[] ) {
        if ( argc > 1 ) {
            int sum = 0;
            pegtl::parse< myparser::grammar, myparser::action >( 1, argv, sum );
            std::cout << sum << std::endl;
        }
    }


.. code-block:: sh

    $ clang++ -std=c++14 -Wall -Wextra -O3 -march=native add.cpp -I ./includes/PEGTL/ -o add
    $ ls -l add
    -rwxr-xr-x 1 user users 24064 Mar 13 15:04 add*
    $ ./add "41+1"
    42
    $ ./add "41+1a"
    terminate called after throwing an instance of 'pegtl::parse_error'
      what():  argv[1]:1:4: parse error matching pegtl::eof
    Aborted (core dumped)


對應表
------------------------------

namespace : ``::pegtl::ascii``

下面只有粗略的對應，完整的請看
`Rule Reference <https://github.com/ColinH/PEGTL/wiki/Rule-Reference>`_

+------------------+---------------------------+--------------+
| pegtl            | regex                     |              |
+==================+===========================+==============+
| digit            | ``\d``, ``[0-9]``         |              |
+------------------+---------------------------+--------------+
| eol              | $                         |              |
+------------------+---------------------------+--------------+
| blank            | ``[ \t]``                 |              |
+------------------+---------------------------+--------------+
| space            | ``\s``, ``[ \t\n\r\f\v]`` |              |
+------------------+---------------------------+--------------+
| alnum            | ``[0-9a-zA-Z]``           |              |
+------------------+---------------------------+--------------+
| alpha            | ``[a-zA-Z]``              |              |
+------------------+---------------------------+--------------+
| any              | .                         |              |
+------------------+---------------------------+--------------+
| eolf             |                           |              |
+------------------+---------------------------+--------------+
| identifier_first | ``[a-zA-Z_]``             | C identifier |
+------------------+---------------------------+--------------+
| identifier_other | ``[a-zA-Z0-9_]``          | C identifier |
+------------------+---------------------------+--------------+
| identifier       |                           |              |
+------------------+---------------------------+--------------+
| istring          |                           |              |
+------------------+---------------------------+--------------+
| lower            | ``[a-z]``                 |              |
+------------------+---------------------------+--------------+
| not_one<C, ...>  |                           |              |
+------------------+---------------------------+--------------+
| not_range<C, D>  |                           |              |
+------------------+---------------------------+--------------+
| nul              | 0                         |              |
+------------------+---------------------------+--------------+


Basic Calculator (support ``+-*/``)
-----------------------------------

S-Expression
------------------------------

JSON pretty printer
------------------------------

ABNF
------------------------------

benchmark
------------------------------


Reference
========================================

* `Wikipedia - Parsing expression grammar (PEG) <https://en.wikipedia.org/wiki/Parsing_expression_grammar>`_
* `The Packrat Parsing and Parsing Expression Grammars Page <http://bford.info/packrat/>`_
* `Parsing: The Solved Problem That Isn't <http://tratt.net/laurie/blog/entries/parsing_the_solved_problem_that_isnt>`_
* [GitHub] `PEGTL - Parsing Expression Grammar Template Library <https://github.com/colinh/pegtl>`_
