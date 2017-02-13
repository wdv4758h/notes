* Undefined behavior: 不會產生 compiler warning / error

  - 觸發時，任何結果都可能發生
  - 就是爆炸活該，保險不給付的意思

* Implementation-defined behavior

  - 例如 sizeof(int)
  - 要寫在 Compiler 實作的文件裡
  - Programmer 可以用，但一定要把文件看完，否則爆炸活該

* Unspecified behavior

  - 例如 function argument 被 evaluate 的順序，且每次的結果都可能不一樣
  - Compiler 的實作在這裡應該要選擇合理的優化策略，但沒有必要寫在文件中
