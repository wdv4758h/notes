========================================
筆記區
========================================

一些筆記，
有的目前是只有連結蒐集，
有的只有小紀錄，
有的有比較大的篇福在說明 :P

內容部份保留原本的英文，其餘都儘量使用繁體中文做紀錄，希望能增加繁體中文的資料量：）

有任何問題可以開 issues (或 `寄信 <mailto:wdv4758h@gmail.com>`_) 詢問 (或告知)


推薦
========================================

Regular Expression Engine
------------------------------

regex engine 的實作建議可以看 Russ Cox 寫的 `系列文 <https://swtch.com/~rsc/regexp/>`_ ，
裡面說明了當初 Ken Thompson 根據 Finite Automata 理論實作的方式，
到後來 regex 被廣泛使用。
到了 PCRE 後，
regex 的功能甚至超出了在正規語言理論中討論的「Regular Expression」該有的能力範圍，
而此時 PCRE 的實作已經不是當初根據 Finite Automata 的實作方式，
而是使用 Backtracking 的方式來實作。
接著發現當初根據 Finite Automata 實作的 regex engine 可以保證搜尋時間為線性時間，
然而 Backtracking 的實作卻會讓搜尋時間為指數時間。
後來 Russ Cox 在捨棄一些現代 regex 的功能後（例如 Backreference），
根據 Finite Automata 實作新的 regex engine 叫 RE2，
以確保線性的搜尋時間，
避免使用 regex 的服務會因為使用者輸入特定的 regex 讓程式進入長久的搜尋。


PyPy
------------------------------

PyPy 重要的技術在於其背後的 RPython Toolchain，
該 Toolchain 可以幫助開發者處理很多程式語言 Virtual Machine 要面對的問題。

架構方面可以先看 2006 發的論文
「 `PyPy's approach to virtual machine construction <https://bitbucket.org/pypy/extradoc/raw/tip/talk/dls2006/pypy-vm-construction.pdf>`_ 」，
裡面說明了 PyPy 如何分析、做 Type Inference、利用 JIT 來加速。

以前 PyPy 和 RPython Toolchain 的文件是放在一起的，
現在兩邊的文件已經儘量分開了。
新架構狀況可以看
`RPython Architecture <https://rpython.readthedocs.io/en/latest/architecture.html>`_ ，
JIT 相關的文件則在 `RPython JIT <https://rpython.readthedocs.io/en/latest/jit/index.html>`_ 。

官方 Blog 以前有寫過利用 RPython Toolchain 實作 Brainfuck Interpreter 的
`Tutorial <https://morepypy.blogspot.tw/2011/04/tutorial-writing-interpreter-with-pypy.html>`_ ，
不過最新的 code 在 `pypy-tutorial <https://bitbucket.org/brownan/pypy-tutorial/>`_ ，
建議看 pypy-tutorial 上面的 code。
另外我在很久以前有照 Tutorial 試了一遍，
有寫一篇
`文章 <https://wdv4758h.github.io/posts/2015/01/pypy-tutorial-for-brainfuck-interpreter/>`_
做紀錄，需要的話歡迎自行取用。


大致結構
========================================

::

    category/
        examples/
            xxx.rst
        ooo.rst


目前的範例：

* C++
    - ctor/dtor
    - RVO
    - thread
    - virtual and cast
    - parallel for

* Python
    - Celery and Django
    - some CheckiO
    - py.test
    - CPython hello module
    - misc


License
========================================

`Public Domain <http://unlicense.org/>`_



.. toctree::
    :maxdepth: 3
    :glob:

    */*
    *
