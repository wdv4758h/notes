Trait and SFINAE
----------------

- c++11 type trait: http://en.cppreference.com/w/cpp/types
- SFINAE: http://xatier.github.io/jobspace-cpp-talk/slides.html

  - example: https://github.com/RadeonOpenCompute/hcc/blob/clang_tot_upgrade/include/experimental/impl/type_utils.inl

- boost type trait: http://blog.csdn.net/pongba/article/details/83828


type traits 簡單說就是在 compile time 測試出某個 type 的性質.

sfinae 的精隨就是在 compiler time 構造出一個 boolean expression, 使之可以依照這個 condition 開啟或關閉某組 template function.
那搭配 C++11 的 type library 就能將 type 是某滿足某些 constrain 當作 condition 用

