========================================
Gradual Typing
========================================


.. contents:: 目錄


介紹
========================================

Gradual Typing 為混合 Static Typing 和 Dynamic Typing 所形成的型別系統，
部份變數會在編譯時期知道型別並檢查型別的正確性，
部份變數則會保持不知道型別的狀態，
直到執行時期才撿查型別錯誤。
在許多實際案例上，Gradual Typing 為在原本的動態語言上加入靜態型別的選擇而成，
在某些案例上則是語言在一開始的設計就選擇了 Gradual Typing。



範例
========================================

Dynamically Typed -> Gradually Typed

* TypeScript (改自 JavaScript)
* Hack (改自 PHP)
* Typed Racket (改自 Racket)
* Typed Clojure (改自 Clojure)
* Cython (改自 Python)


Statically Typed -> Gradually Typed

* C#


Others

* Dart
* Dylan
* Perl 6



參考
========================================

* `Wikipedia - Gradual typing <https://en.wikipedia.org/wiki/Gradual_typing>`_
* `ECOOP 2016 - Gradual Type Systems <http://2016.ecoop.org/event/summer-school-gradual-type-system>`_
* `ECOOP 2016 - 28 Years of Types for Untyped Languages: A Random Walk Thru TypeLand <http://2016.ecoop.org/event/summer-school-gradual-typing>`_
* `POPL 2016 Papers <https://github.com/gasche/popl2016-papers>`_
* `Lambda the Ultimate - Progress on Gradual Typing <http://lambda-the-ultimate.org/node/5292>`_
* `A bibliography on Gradual Typing <https://github.com/samth/gradual-typing-bib>`_
* [2015] `Towards Practical Gradual Typing <http://www.ccs.neu.edu/racket/pubs/ecoop2015-takikawa-et-al.pdf>`_
* `What is Gradual Typing <http://homes.soic.indiana.edu/jsiek/what-is-gradual-typing/>`_


Python

* `PEP 483 -- The Theory of Type Hints <https://www.python.org/dev/peps/pep-0483/>`_
* `Reticulated Python -  Types for Python <https://github.com/mvitousek/reticulated>`_
