========================================================================================
RE2 - fast, safe, thread-friendly alternative to backtracking regular expression engines
========================================================================================

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
其中主要的是 FullMatch、PartialMatch、Consume、FindAndConsume 這幾項：

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
