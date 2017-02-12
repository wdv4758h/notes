========================================
筆記區
========================================

一些筆記，
有的目前是只有連結蒐集，
有的只有小紀錄，
有的有比較大的篇福在說明 :P

----

內容部份保留原本的英文，其餘都儘量使用繁體中文做紀錄，希望能增加繁體中文的資料量：）

(As most information of Computer Science is written in English,
I'm trying my best to increase the CS information in Traditional Chinese.)

----

有任何問題可以開 issues (或 `寄信 <mailto:wdv4758h@gmail.com>`_)

(Feel free to open issues or send mails.)


.. contents:: 目錄



行為準則
========================================

（修改自《日內瓦宣言》）


當我進入開放原始碼圈子時：

* 我鄭重地保證自己要奉獻一切為開放原始碼服務
* 我將要給開源貢獻者應有的崇敬及感戴
* 我將要憑我的良心和尊嚴從事程式撰寫
* 開源專案的進步應為我的首要的顧念
* 我將要尊重所寄託給我的秘密
* 我將要盡我的力量維護開放原始碼的榮譽和高尚的傳統
* 我的同業應視為我的手足
* 我將不容許有任何種族、民族、文化、膚色、國籍、移民狀況、社會和經濟階層、受教育程度、性別、性取向、性別認同、年齡、身材、家庭狀況、政治傾向、宗教信仰、精神狀況和身體狀況的考慮介於我的職責和開源專案間
* 我將要盡可能地維護程式碼的開放，自從專案開始時起
* 即使在威脅之下，我將不運用我的資訊知識去違反人道
* 我鄭重地、自主地並且以我的人格宣誓以上的約定



部份項目
========================================

Vim
------------------------------

（老王賣瓜）
我以前曾經講過一場 Vim 的使用教學，
有興趣的可以參考：
`《Vim 手指健康操》 <https://speakerdeck.com/wdv4758h/vim-shou-zhi-jian-kang-cao>`_

Plugin 管理的部份個人喜歡 `vim-plug <https://github.com/junegunn/vim-plug>`_ ，
安裝 Plugins 很快，管理也很有彈性。
(多個 Plugins 的更新和安裝可以同步進行、
可以指定要使用的 branch、
可以設定更新後要進行的額外操作）


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


版本控制
------------------------------

個人在版本控制上習慣使用 Git （純粹個人習慣），
Git 在 `官網 <https://git-scm.com/doc>`_ 就有很好的說明和教學，
另外 GitHub 也有做 `Tutorial <https://try.github.io>`_ ，
除此之外這邊還有一張
`Cheatsheet <http://www.ndpsoftware.com/git-cheatsheet.html>`_
可以看。
如果想要了解更深入的話可以看
`Git Magic <http://www-cs-students.stanford.edu/~blynn/gitmagic/>`_ 。


Python
------------------------------

初學者的話建議直接從 **Python 3** 開始學起。

Python 的 Coding Style 可以參考 PEP8，
這裡有 `好讀版 <http://pep8.org/>`_ 。

檢查方面建議在定義 Functions 時，
就使用 `PEP484 <https://www.python.org/dev/peps/pep-0484/>`_ 所加入的 Type Hints，
並且使用 `mypy <https://github.com/python/mypy>`_ 做靜態檢查，
以盡早避免某些 Bugs 發生。

測試部份建議使用 `pytest <https://pytest.org/>`_ ，
使用 pytest 的話可以直接寫普通的 Function 和使用 ``assert`` 就可以了！

如果覺得內建的 Python Interactive Shell 不夠好用的話，
可以使用 `IPython <https://ipython.org/>`_
或者基於 IPython 之上做的
`ptpython <https://github.com/jonathanslenders/ptpython>`_ 。

要使用 Python 做科學相關研究的話，
可以先參考 `Scipy Lecture Notes <http://www.scipy-lectures.org/>`_
和以下專案：

* NumPy
* SciPy
* Pandas
* Matplotlib
* scikit-learn
* ...


想要更多 Python 的建議可以參考
`The Hitchhiker's Guide to Python <http://docs.python-guide.org/en/latest/>`_



JIT
------------------------------

JIT 的歷史可以看 2003 年發的 Paper 「A Brief History of Just-In-Time」，
裡面涵蓋從 Lisp、Thompson's regex engine 到 Self、JVM 等等的演進過程，
做了分類、比較。



Rust
------------------------------

Rust 的安裝和管理可以使用 `rustup <https://www.rustup.rs/>`_ ，
能夠方便地管理 toolchain 版本跟平台。
第三方套件則使用 `Cargo <http://doc.crates.io/guide.html>`_ ，
由官方提供統一的 Build System 和套件格式，
在第三套件的管理和利用上會比 C 或 C++ 方便許多。

如果是有些經驗的程式設計師，
可以先看 `Rust by Example <http://rustbyexample.com/>`_ 來了解 Rust 寫起來會是什麼樣子。
要進一步了解背後的設計哲學可以先看
`Why Rust <http://www.oreilly.com/programming/free/files/why-rust.pdf>`_ 這本書。
接著可以看官方的 `The Rust Programming Language <https://doc.rust-lang.org/book/>`_ 仔細學習每個部份，
另外搭配 `Frequently Asked Questions <https://www.rust-lang.org/faq.html>`_ 釐清其他觀念。
然後看 `The Rustonomicon <https://doc.rust-lang.org/nomicon/>`_ 補充更多知識。

語言設計可以參考：

* `You Can't Spell Trust Without Rust <https://raw.githubusercontent.com/Gankro/thesis/master/thesis.pdf>`_
* `Rust Bibliography <https://forge.rust-lang.org/bibliography.html>`_

要更多資源可以到 `rust-learning <https://github.com/ctjhoa/rust-learning>`_
和 `awesome-rust <https://github.com/kud1ing/awesome-rust>`_ 尋找。

Rust 作為一個年輕的程式語言，
雖然語言本身已經進入穩定釋出了，
但是生態圈（基礎建設）還不夠完整，
這是個麻煩也是個機會，
麻煩的地方在於有時會找不到合適的第三方套件使用，
機會在於還有很多地方是很容易貢獻的！

Rust 的 Build System - Cargo - 內建就有許多方便的 subcommands 可以使用，
內建的 subcommands 可以在 `這裡 <https://github.com/rust-lang/cargo/tree/master/src/bin>`_ 找到。
除此之外，大家也可以為 Cargo 寫 subcommands
（內建的 `subcommands <https://github.com/rust-lang/cargo/tree/master/src/bin>`_ 可以在這裡找到），
目前也已經有不少不錯的第三方 subcommands。
例如，只想單純作檢查而不生執行檔可以使用
`cargo-check <https://github.com/rsolomo/cargo-check>`_ ，
想檢查相依套件的新版本可以用 `cargo-outdated <https://github.com/kbknapp/cargo-outdated>`_ 。

其他資源：

* `Rust for functional programmers <http://science.raphael.poss.name/rust-for-functional-programmers.html>`_
* `Rust-101 <https://www.ralfj.de/projects/rust-101/main.html>`_
* `Learning Rust With Entirely Too Many Linked Lists <http://cglab.ca/~abeinges/blah/too-many-lists/book/>`_
* `Rust Iterator Cheat Sheet <https://danielkeep.github.io/itercheat_baked.html>`_


Garbage Collection
------------------------------

GC 是現今程式語言常見的記憶體管理方式，
諸如 Lisp、Python、Ruby、Lua、Go 等等都在使用，
個人目前的相關筆記放在 `這裡 </garbage-collection/introduction.rst>`_ 。


Android
------------------------------

個人目前使用的手機是 2012 年出的，
剛開始是 Android 2.3，
後來官方有提供到 Android 4.1，
但是就沒有後續升級了，
所以我就自己刷 AOSP 來用，
目前是 Android 7.1.1。

少量的相關筆記在 `這裡 </android/install.rst>`_ 。


Kindle Paperwhite
------------------------------

由於陸陸續續買了一些電子書，
所以就買了一台 Kindle Paperwhite 來看，
因為想在上面裝些東西所以就刷了，
刷完後就可以發現上面跑的是 Linux、CPU 是 ARM，
而系統上還跑著我天天都在用的 Awesome WM。

少量的相關筆記在 `這裡 </hardware/kindle.rst>`_ 。


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



不自殺聲明
========================================

本人在此特地聲明：

本人樂觀開朗，身體健康，
無任何使我困擾之慢性病或心理疾病，故絕不可能做出任何看似自殺之行為。

本人從無睡眠困擾，故不需服用安眠藥。

本人不酗酒亦不吸毒，也絕不會接近下列地點──

1. 開放性水域
2. 無救生員之游泳池
3. 有高壓、危險氣體，或密閉式未經抽氣處理之地下室、蓄水池、水桶等
4. 無安全護欄之任何高處
5. 任何施工地點（拆政府除外），包括製作消波塊之工地
6. 任何以上未提及但為一般人正常不會前往之地點

本人恪遵下列事項──

1. 車輛上路前會檢查煞車部件、油門線等，並會在加油前關閉車輛電源與行動電話。
2. 絕不擅搶黃燈、闖紅燈。
3. 乘坐任何軌道類交通工具一定退到警戒線後一步以上，直到車輛停妥。
4. 騎乘機車必戴安全帽；乘車必繫安全帶。
5. 絕不接近任何會放射對人體有立即危害的輻射之場所（如核電廠）或設備。
6. 颱風天不登山、不觀浪。

本人將盡可能注意電器、瓦斯、火源之使用。

本人居住之房屋均使用符合法規之電路電線，絕無電線走火之可能；
也絕未在家中放置任何可燃性氣體或液體。
浴室中除該有之燈管燈泡外，不放置任何電器用品，
並在睡覺前關閉除電燈、冰箱、電扇外之所有電器開關。

本人絕不會與隨機的不明人士起衝突，並盡可能保護自我人身安全。

所以若網友在看完此聲明之後，近期或將來發現此帳號不再上線，
請幫我討回公道，謝謝。



提問的智慧
========================================

How To Ask Questions The Smart Way

* `原文 <http://www.catb.org/~esr/faqs/smart-questions.html>`_
* `繁體中文翻譯 <https://github.com/ryanhanwu/How-To-Ask-Questions-The-Smart-Way>`_



.. toctree::
    :maxdepth: 3
    :glob:

    */*
    *
