Introduction
===============================================================================

Parts of compiler:

- Front-end
    - generate IR (itermediate representation)
    - 通常複雜度低

- Mid-end

- Back-end
    - 通常複雜度高


Generate Object File
----------------------------------------------------------------------

``prog.c`` -> pre-proccessing -> ``prog.s``


Quote from ``clang(1)``:

    Stage Selection Options

        -E     Run the preprocessor stage.

        -fsyntax-only
            Run the preprocessor, parser and type checking stages.

        -S     Run the previous stages as well as LLVM generation and
            optimization stages and target-specific code generation,
            producing an assembly file.

        -c     Run all of the above, plus the assembler, generating a target
            ".o" object file.


Structure of Compiler
----------------------------------------------------------------------

- token stream

- AST

- IR: 常用 *three address code*. 然後 optimizer 就對 IR 做優化。

- target native code

- symbol table


Phases and Passes
----------------------------------------------------------------------

phase
    是 compiler 在邏輯上操作的切分

pass
    把多個 phase group 起來， compiler 完成一次的 read file -> write file

front-end pass
    - :lexical analysis: output token
    - :syntax analysis: or *parsing*
    - :semantic analysis: 蒐集 type 資訊做檢查， *type checking*;
      語言定義的 type conversion -- *coercions*
    - IR code gen:
        - syntax tree is a form of IR
        - three address code
    - symbol table management

optional pass
    - optimization
        - data-flow optimizations
        - instruction level parallelism, e.g. re-order instruction, SIMD
        - proccessor level parallelism
        - optimization for memory hierarchy

back-end pass
    - code gen


Toolchains
----------------------------------------------------------------------

:parser generator:
    - `PEG.js <https://pegjs.org/>`_
    - `peg <https://github.com/pointlander/peg>`_
    - YACC
    - `Bison <https://www.gnu.org/software/bison/>`_

:scanner generator:
    - lex
    - `flex <https://github.com/westes/flex.git>`_

:syntax-directed translation engine:

:code-generator generator:

:data-flow analysis engine:

:compiler-contruction toolkits:
    - `RPython <https://rpython.readthedocs.io/en/latest/>`_


Misc
----------------------------------------------------------------------

- compiler-rt 可以對相容的 platform (e.g. x86 & amd64) 提高
  object file portability. 或是對 cross-compiling 做處理

- 這個年代的 low-level resource allocation 做的很好了，如， C 有 ``register``
  這個 keyword 讓 programmer 自己控制 register 相關操作；但實際上，使用
  ``register`` 的效果反而容易造成效能損失，因為現代的 compiler 對 register
  management 已經有自己一套很好的 policy 了。
