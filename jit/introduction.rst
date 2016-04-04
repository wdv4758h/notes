========================================
JIT
========================================

Case Study
========================================

McCarthy's LISP
------------------------------

Thompson's regex
------------------------------

LuaJIT
------------------------------

Smalltalk
------------------------------


Regular Expression History
========================================

以下的內容翻譯、修改自
`Regular Expressions – a brief history <http://blog.staffannoteberg.com/2013/01/30/regular-expressions-a-brief-history/>`_


Regular Expression 的概念最早發展自神經科學家和邏輯學家合作，
嘗試了解人類大腦如何用簡單的細胞來產生出複雜的模式。

在 1943 年時，Warren McCulloch (神經科學家) 和 Walter Pitts (邏輯學家)
在 Bulletin of Mathematical Biophysics  5:115-133 發布了
「A logical calculus of the ideas immanent in nervous activity」，
這篇論文對於後來的資訊領域有很大的影響 (雖然這不是這論文本來的目標)。

在 1956 年時，Stephen Kleene (數學家) 改進這個模型，
在「Representation of events in nerve nets and finite automata」中
他用簡單的代數學作為表示 (只有兩個 operations 和一個 function)，
此時「Regular Sets」和「Regular Expressions」這兩個詞就誕生了。

在 1968 年時，
Ken Thompson 在 Communications of the ACM (CACM) Volume 11
發表了「Regular Expression Search Algorithm」，
其中描述了一個可以把 Regular Expression 轉成 IBM 7094 object code 的編譯器。
而在那之後 Ken Thompson 還把 Kleene 的標記法實作在 ``QED`` 這個編輯器中，
如此一來使用者可以對文件做複雜的 pattern matching，
這個功能後來也被實作在 ``ed`` 編輯器中。

在 ``ed`` 中，
如果想要搜尋 Regular Expression 要寫成 ``g/<regular expression>/p`` ，
其中 ``g`` 代表全域搜尋、 ``p`` 代表輸出結果。
這指令 ``g/re/p`` 也就成為後來 ``grep`` 指令的來源，
``grep`` 最早釋出於 1973 年的 Unix v4 (但已經使用許久)，
但是當時並沒有實作完整的 Regular Expression。
直到 1979 年釋出的 Unix v6 中
Alfred Aho 的 ``egrep`` (extended grep) 才有更完整的支援，
``egrep`` 會把所有收到的 Regular Expression 轉成對應的 DFA 來執行。

1987 年，Larry Wall 發明 Perl 程式語言，
其中 Regular Expression 的整合讓 Regular Expressions 更加廣為使用。
後來更多的功能加進了 Regular Expressions，
Perl 也增加了抽象化跟語法糖，
其中有些功能甚至不能用 Finite Automata 完成，
這樣的發展產生了一個問題，
「現代的 Regular Expressions」還能叫作「Regular Expressions」嗎？
「現代的 Regular Expressions」 不只包含 Kleene 的代數表示，
還包含後續各程式語言實作上加入的功能 (例如 Perl)。

現今 Linux 系統上常見的 grep 指令通常為 GNU grep，
是由 Mike Haerkal 撰寫，於 1988 年釋出第一版
(在 1987 年的「GNU's Bulletin」第二版就有提及)。


人物：

* `Warren McCulloch (神經科學家) <https://en.wikipedia.org/wiki/Warren_Sturgis_McCulloch>`_
* `Walter Pitts (邏輯學家) <https://en.wikipedia.org/wiki/Walter_Pitts>`_
* `Stephen Kleene (數學家) <https://en.wikipedia.org/wiki/Stephen_Cole_Kleene>`_
* `Ken Thompson <https://en.wikipedia.org/wiki/Ken_Thompson>`_
* `Alfred Aho <https://en.wikipedia.org/wiki/Alfred_Aho>`_
    - `Columbia - Alfred V. Aho <http://www.cs.columbia.edu/~aho/>`_
* `Larry Wall <https://en.wikipedia.org/wiki/Larry_Wall>`_
* Mike Haerkal

相關文章：

* `Regular Expressions – a brief history <http://blog.staffannoteberg.com/2013/01/30/regular-expressions-a-brief-history/>`_
* `“grep was a private command of mine for quite a while before i made it public.” -Ken Thompson <https://medium.com/@rualthanzauva/grep-was-a-private-command-of-mine-for-quite-a-while-before-i-made-it-public-ken-thompson-a40e24a5ef48#.4gu6lehr7>`_
* `Mike Haertel - why GNU grep is fast <http://lists.freebsd.org/pipermail/freebsd-current/2010-August/019310.html>`_


FAQ
========================================

Why mmap instead of malloc ?
------------------------------


Implementation
========================================

* DynASM
    - http://luajit.org/dynasm.html
    - The Unofficial DynASM Documentation : https://corsix.github.io/dynasm-doc/
* `GCC - libgccjit <https://gcc.gnu.org/onlinedocs/jit/>`_
* `LLVM - MCJIT <http://llvm.org/docs/MCJITDesignAndImplementation.html>`_
* PyPy
* `AsmJit <https://github.com/kobalicek/asmjit>`_
* `LibJIT <https://www.gnu.org/software/libjit/>`_

Bindings
========================================

* `Python bindings for libgccjit <https://github.com/davidmalcolm/pygccjit>`_


Reference
========================================

* `How to JIT - an introduction <http://eli.thegreenplace.net/2013/11/05/how-to-jit-an-introduction>`_
* `A Just-in-time Compiler In Rust <http://www.hydrocodedesign.com/2014/01/17/jit-just-in-time-compiler-rust/>`_
* [2003] A Brief History of Just-In-Time
* [1968] Ken Thompson - Programming Techniques: Regular expression search algorithm
* [1987] Rob Pike - Structural Regular Expressions
