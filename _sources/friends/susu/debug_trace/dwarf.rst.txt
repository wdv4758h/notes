- DWARF 的 Debug Info 格式: http://www.cnblogs.com/catch/p/3884271.html

  - 在 breakpad 中加入印 function parameter 的功能, 增加印出的 callstack 的可讀性.
  - 時間幾乎都花在理解 DWARF 上面

DWARF

- LEB128 encoding
- ELF .debug_info section

  - 多個 DIE(debugging information entry) 組成
  - DIE = tag + 多個 attribute
  - readelf --debug-dump=info <exe>

- serialize tree data structure
- data compression
- DWARF expression

  - stack-based language
  
    a. Literal Encoding: stack 上放常數, memory address. e.g. lit0~31, addr, const1u~const8u
    b. Register Based Addressing: 從 register 拿數字出來運算, 並放入 stack. e.g. breg0~31
    c. Stack operation: dup, pop
    d. Arithmetic And Logical Operation: abs, div, and
    e. Control flow operations: 六種 compare, 看起來有點像 logical operation??
    f. nop
