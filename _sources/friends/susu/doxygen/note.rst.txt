- comment block

  a. brief
  b. detail description
  c. body [only function and method has it]

- usage and problems

    1. function prototype 跟 function definition 都可以放 comment block, 效果會疊加 (兩邊都放 /brief 就會有兩個 /brief)
       只有 function prototype 的 /brief 會顯示在 doxygen 上方的 function list.

    2. doxygen 的內文 style 為何? 目前發現跟 markup language 一樣要換兩行才會換行. 跟我目前 comment 需要條列式步驟的習慣不合.
