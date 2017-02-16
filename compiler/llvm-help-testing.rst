========================================
LLVM 輔助測試
========================================


.. contents:: 目錄


Mutation Testing
========================================

Mutation Testing 是一種白箱測試，
藉由更動程式碼部份的操作來衡量現有的測試是否有效，
是「測試」的測試。


相關實做：

* `Pitest - State of the art mutation testing system for the JVM <https://github.com/hcoles/pitest>`_
* `Mutant - Mutation testing for Ruby <https://github.com/mbj/mutant>`_
* `LLVM-based Mutation Testing System. Proof of Concept <https://github.com/AlexDenisov/mutation-testing-poc>`_
* `Attempt to build a system for mutation testing on top of LLVM <https://github.com/mull-project/mull>`_
* `Compiler and mutation testing framework for Pascal-86 <https://github.com/john-tornblom/llvm-p86>`_


相關資源：

* `Wikipedia - Mutation testing <https://en.wikipedia.org/wiki/Mutation_testing>`_
* [FOSDEM 2017] `Mutation Testing - Leaving the Stone Age <https://fosdem.org/2017/schedule/event/mutation_testing/>`_
* `LLVM-based Mutation Testing System. Request For Comments <https://lowlevelbits.org/llvm-based-mutation-testing-system.-request-for-comments/>`_
* `How do I find the function pointers for tests from the LLVM IR code of a Rust program? <http://stackoverflow.com/questions/42177712/how-do-i-find-the-function-pointers-for-tests-from-the-llvm-ir-code-of-a-rust-pr>`_



Fuzz Testing
================================================================================

* `libFuzzer – a library for coverage-guided fuzz testing <http://llvm.org/docs/LibFuzzer.html>`_
* `AFL (American Fuzzy Lop) <http://lcamtuf.coredump.cx/afl/>`_
* `Radamsa <https://github.com/aoh/radamsa>`_
* `OSS-Fuzz <https://github.com/google/oss-fuzz>`_
