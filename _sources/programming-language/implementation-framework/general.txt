========================================
Language Implementation - General
========================================


.. contents:: 目錄


直譯器效能
========================================

影響直譯器效能的因素有很多（這邊不討論 JIT）。



參考
========================================

文章
------------------------------

* Let's Build A Simple Interpreter
    - `Part 1 <http://ruslanspivak.com/lsbasi-part1/>`_
    - `Part 2 <http://ruslanspivak.com/lsbasi-part2/>`_
    - `Part 3 <http://ruslanspivak.com/lsbasi-part3/>`_
    - `Part 4 <http://ruslanspivak.com/lsbasi-part4/>`_
    - `Part 5 <http://ruslanspivak.com/lsbasi-part5/>`_
    - `Part 6 <http://ruslanspivak.com/lsbasi-part6/>`_
    - `Part 7 <http://ruslanspivak.com/lsbasi-part7/>`_
    - `Part 8 <http://ruslanspivak.com/lsbasi-part8/>`_
    - `Part 9 <http://ruslanspivak.com/lsbasi-part9/>`_
    - `Part 10 <http://ruslanspivak.com/lsbasi-part10/>`_
    - `Part 11 <http://ruslanspivak.com/lsbasi-part11/>`_
    - `Part 12 <http://ruslanspivak.com/lsbasi-part12/>`_
* `Making a simple VM interpreter in Python <https://csl.name/post/vm/>`_


Papers
------------------------------

* [2005] `The Structure and Performance of Efficient Interpreters <https://www.jilp.org/vol5/v5paper12.pdf>`_
    - 要改善大量的 indirect branches
    - 「快速的直譯器和緩慢的直譯器間的差距」大於「快速的直譯器和編譯過的執行檔」
    - 「快速的直譯器和編譯過的執行檔的差距」大約 10 倍
    - 「緩慢的直譯器和編譯過的執行檔的差距」大約 1000 倍
    - 研究的實做
        + Ocaml
        + Gforth
        + Scheme48
        + Yap (Prolog)
        + Perl
        + Xlisp
    - Stach Machine & Register Machine
    - 快速的直譯器的特徵
        + 會把程式碼轉成 IR 來避免重複 Parse
        + IR 是扁平的，像是 Machine Code，而不是樹狀結構，藉此降低解讀的難度
        + 可以方便地從原始碼轉成 IR
        + Dispatch 很重要，Direct Threaded Code 是不錯的實做方式
* [2005] `Virtual Machine Showdown: Stack Versus Registers <https://www.usenix.org/legacy/events/vee05/full_papers/p153-yunhe.pdf>`_
