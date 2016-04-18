========================================================================================
RE2 - fast, safe, thread-friendly alternative to backtracking regular expression engines
========================================================================================

.. contents:: 目錄


Todo
========================================

* RE2 流程圖 (何時使用 NFA、DFA？中間的轉換機制？)
* 為 RE2 實作 backreference fallback (給需要 backreference 的地方有機會使用，雖然效能不佳)
* 基於 RE2 實作 grep (然後跟 GNU grep 做效能比較)
* Regular Expression Engine 功能比較表 (PCRE, PCRE-DFA, Oniguruma, TRE, RE2, PCRE-sljit, sregex)
* Regular Expression Engine 效能比較表 (速度和記憶體使用量)
* 嘗試把 RE2 接上 Neovim 作為 Regular Expression 後端
* 完善 Python 的 RE2 wrapper (https://github.com/axiak/pyre2/)
* 研究 C++ STL 內的 <regex> (libstdc++, libc++) 以及 Boost.Regex
* 研究 CPython 內的 "Secret Labs' Regular Expression Engine"
* 嘗試使用 RPython 實作有 JIT 的 Regular Expressiohn Engine (http://morepypy.blogspot.tw/2010/05/efficient-and-elegant-regular.html, http://morepypy.blogspot.tw/2010/06/jit-for-regular-expression-matching.html, http://sebfisch.github.io/haskell-regexp/regexp-play.pdf, http://sebfisch.github.io/haskell-regexp/, https://mail.python.org/pipermail/python-dev/2012-June/119820.html)
* 研究且改進 Rust 的 regex library (https://github.com/rust-lang-nursery/regex)



使用
========================================

簡單 Script：

.. code-block:: sh

    git clone https://github.com/google/re2 re2

    mkdir src
    # edit src/myprogram.cpp

    mkdir build
    cd build

    make -j8 -C ../re2
    cp ../re2/obj/so/libre2.so .

    clang++ -std=c++14 -Wall -Wextra ../src/myprogram.cpp -I ../re2/ -L . -l re2 -o myprogram
    LD_PRELOAD=./libre2.so ./myprogram


.. code-block:: cpp

    // src/myprogram.cpp

    #include <iostream>

    #include <re2/re2.h>

    int main() {
        std::cout << RE2::FullMatch("Hello World", "H.*W.*") << std::endl;
        std::cout << RE2::FullMatch("Hello |orld", "H.*W.*") << std::endl;
        return 0;
    }



基本功能
========================================

可以從 ``re2/re2.h`` 中找到 RE2 提供的 C++ 介面，
大致翻過裡面的程式碼後可以發現有數個功能可以使用（都在 RE2 namespace 底下），
其中主要的是 ``FullMatch`` 、``PartialMatch`` 、``Consume`` 、``FindAndConsume`` 這幾項。

關係 ::

    +-----------+   +--------------+    +---------+    +----------------+
    | FullMatch |   | PartialMatch |    | Consume |    | FindAndConsume |
    +-----------+   +--------------+    +---------+    +----------------+
          ^                 ^                ^                 ^
          |                 |                |                 |            VariadicFunction2<...>
          |                 |                |                 |
    +------------+  +---------------+   +----------+   +-----------------+
    | FullMatchN |  | PartialMatchN |   | ConsumeN |   | FindAndConsumeN |
    +------------+  +---------------+   +----------+   +-----------------+
          ^                 ^                ^                 ^
          |                 |                |                 |            Simple Wrapper
          |                 |                |                 |
    +--------------------------------------------------------------------+
    |                              DoMatch                               |
    +--------------------------------------------------------------------+
                                     ^
                                     |                                      Wrapper
                                     |
    +--------------------------------------------------------------------+
    |                              Match                                 |
    +--------------------------------------------------------------------+


``FullMatch`` 是 ``FullMatchN`` 的 Special Case，
用 ``VariadicFunction2`` Template 包裝而成 (在 ``re2/variadic_function.h`` )，
而 ``FullMatchN`` 則是 ``RE2::RE2::DoMatch`` 的包裝。
同樣的 ``PartialMatchN`` 、``ConsumeN`` 、``FindAndConsumeN`` 也都是 ``RE2::RE2::DoMatch`` 的包裝。


+----------------+----------------------------------------+--------------+
| Function 名稱  | 功能                                   | Anchor       |
+================+========================================+==============+
| FullMatch      | 完整符合                               | ANCHOR_BOTH  |
+----------------+----------------------------------------+--------------+
| PartialMatch   | 其中符合                               | UNANCHORED   |
+----------------+----------------------------------------+--------------+
| Consume        | 開頭起算完整符合，符合後截去該部份     | ANCHOR_START |
+----------------+----------------------------------------+--------------+
| FindAndConsume | 開頭起尋找符合的部份，符合後截至該部份 | UNANCHORED   |
+----------------+----------------------------------------+--------------+

範例：

.. code-block:: cpp

    #include <iostream>
    #include <string>

    #include <re2/re2.h>

    int main() {
        // FullMatch
        std::cout << RE2::FullMatch("Hello World", "H.*W.*") << std::endl;  // true
        std::cout << RE2::FullMatch("Hello World", "W.*") << std::endl;     // false

        // PartialMatch
        std::cout << RE2::PartialMatch("Hello World", "H.*W.*") << std::endl;  // true
        std::cout << RE2::PartialMatch("Hello World", "W.*") << std::endl;     // true

        // Consume
        {
            std::string contents = "this is my input";
            re2::StringPiece input(contents);   // Wrap a StringPiece around it
            int counter = 0;
            while (RE2::Consume(&input, "(\\S+)")) {
                std::cout << ++counter << "|\"" << input << "\"" << std::endl;
            }
            // 1|" is my input"
        }
        {
            std::string contents = " this is my input";     // add space at the begin
            re2::StringPiece input(contents);   // Wrap a StringPiece around it
            int counter = 0;
            while (RE2::Consume(&input, "(\\S+)")) {    // match nothing
                std::cout << ++counter << "|\"" << input << "\"" << std::endl;
            }
        }

        // FindAndConsume
        {
            std::string contents = "this is my input";
            re2::StringPiece input(contents);   // Wrap a StringPiece around it
            int counter = 0;
            while (RE2::FindAndConsume(&input, "(\\S+)")) {
                std::cout << ++counter << "|\"" << input << "\"" << std::endl;
            }
            // 1|" is my input"
            // 2|" my input"
            // 3|" input"
            // 4|""
        }
        {
            std::string contents = " this is my input";     // add space at the begin
            re2::StringPiece input(contents);   // Wrap a StringPiece around it
            int counter = 0;
            while (RE2::FindAndConsume(&input, "(\\S+)")) {
                std::cout << ++counter << "|\"" << input << "\"" << std::endl;
            }
            // 1|" is my input"
            // 2|" my input"
            // 3|" input"
            // 4|""
        }

        return 0;
    }



FullMatch、PartialMatch、Consume、FindAndConsume 感覺就像是 sscanf 那樣，
第一個吃的是輸入資料，
第二個是要爬的 pattern，
剩下的是要存入的變數位置 (如果有用 groups 的話)，
範例：

.. code-block:: cpp

    #include <iostream>
    #include <string>

    #include <re2/re2.h>

    int main() {
        int i;
        std::string s;
        RE2::FullMatch("iamstring:1234", "(\\w+):(\\d+)", &s, &i);
        return 0;
    }


不定 group 個數：

.. code-block:: cpp

    #include <iostream>
    #include <string>

    #include <re2/re2.h>

    int main() {
        const RE2::Arg* args[10];
        int n;
        // ... populate args with pointers to RE2::Arg values ...
        // ... set n to the number of RE2::Arg objects ...
        bool match = RE2::FullMatchN(input, pattern, args, n);
        // equals:
        // bool match = RE2::FullMatch(input, pattern, args[0], args[1], ..., args[9]);

        return 0;
    }


其他還有一些可以使用的輔助 Functions，
例如：

* Replace
* GlobalReplace
* Extract
* QuoteMeta
* PossibleMatchRange
* Hex
* Octal
* CRadix
* ...
