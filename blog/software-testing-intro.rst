:title: [WIP][Software Testing] Intro.
:slug: software-testing-intro
:date: 2014-11-10 01:17
:modified: 2014-11-10 01:17
:category: Misc
:tags: testing
:author: wdv4758h
:summary: note for Software Testing course

Note: **本篇仍在未完成狀態**

----

- `課程講義 <http://people.cs.nctu.edu.tw/~skhuang/st2014/>`_

期中考: 第 5,6,7,8,9 章 (boundary value, equivalence class, decision table, path testing, data flow testing)

Intro.
========================================

white & black
------------------------------

測試大概可以分成 **白箱測試 (white-box testing)** 與 **黑箱測試 (black-box testing)**

white-box testing 又可以稱為 **透明箱測試 (glass box testing)**，
因為可以看到內部結構，因此又稱為 **結構測試 (structural testing)** 或 **邏輯驅動測試 (logic-driven testing)**

test case adequacy criteria
------------------------------

test case adequacy criteria 討論的是 "需要多少的測試才足夠"，
這可以由涵蓋的 control-flow & data-flow 比例來衡量

- control-flow coverage (測量可以經過多少 execution path)
    * statement coverage
    * branch coverage

- data-flow coverage (definition & use & kill)
    * all-du-paths (definition & use)
    * all-uses
    * all-defs
      + 如果每條 variable 的 dc-paths 都包含的話
    * all-c-uses (computation)
    * all-p-uses (predicate)
    * all-c-uses/some-p-uses
    * all-p-uses/some-c-uses
    * dc-paths (definition & clear)

test case 難寫通常也代表著程式太複雜，因此要降低結構複雜度，再來是避免 non-determinism

----

Rapps-Weyuker hierarchy of data flow coverage metrics :

::

                        +-----------+
                        | All-Paths |
                        +-----------+
                            |
                        +--------------+
                        | All-DU-Paths |
                        +--------------+
                            |
                        +----------+
                        | All-Uses |
                        +----------+
                            |
                            |
             |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
             |                              |
    +------------------------+      +------------------------+
    | All C-Uses some P-Uses |      | All P-Uses some C-Uses |
    +------------------------+      +------------------------+
                                            |
                                            |
                            |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
                            |                        |
                        +----------+            +------------+
                        | All-Defs |            | All P-Uses |
                        +----------+            +------------+
                                                     |
                                                +-----------+
                                                | All Edges |
                                                +-----------+
                                                     |
                                                +-----------+
                                                | All Nodes |
                                                +-----------+

.. table::
    :class: table table-bordered

    +-------+---------------------------------------------+
    | P-use | use in predicate                            |
    +-------+---------------------------------------------+
    | C-use | use in computation                          |
    +-------+---------------------------------------------+
    | O-use | use for output                              |
    +-------+---------------------------------------------+
    | L-use | use for location (pointers, subscripts)     |
    +-------+---------------------------------------------+
    | I-use | iteration (internal counters, loop indices) |
    +-------+---------------------------------------------+
    | I-def | defined by input                            |
    +-------+---------------------------------------------+
    | A-def | defined by assignment                       |
    +-------+---------------------------------------------+

----

- `Wikipedia - Program Slicing <http://en.wikipedia.org/wiki/Program_slicing>`_

- https://github.com/romanofski/programslice
- http://www.researchgate.net/publication/261261093_Static_Slicing_for_Python_First-Class_Objects

.. table::
    :class: table table-bordered

    +--------------+--------+---------+----------------------------------------------------+
    | Spyder       | ANSI C | Dynamic | http://spaf.cerias.purdue.edu/Students/spyder.html |
    +--------------+--------+---------+----------------------------------------------------+
    | Unravel      |        |         |                                                    |
    +--------------+--------+---------+----------------------------------------------------+
    | CodeSonar    |        |         |                                                    |
    +--------------+--------+---------+----------------------------------------------------+
    | Indus/Kaveri |        |         |                                                    |
    +--------------+--------+---------+----------------------------------------------------+
    | JSlice       |        |         |                                                    |
    +--------------+--------+---------+----------------------------------------------------+
    | SeeSlice     |        |         |                                                    |
    +--------------+--------+---------+----------------------------------------------------+
    | Programslice |        |         |                                                    |
    +--------------+--------+---------+----------------------------------------------------+

decision-to-decision path (DD-path)
-----------------------------------

coverage.py
------------------------------

``coverage report -m``

.. code-block:: sh

    $ coverageg report -m

    Name    Stmts   Miss  Cover   Missing
    -------------------------------------
    hw1        58      2    97%   49-50
    test       21      0   100%
    -------------------------------------
    TOTAL      79      2    97%

Ch5 - Boundary Value Testing
========================================

- `Ch5 課程講義 <https://docs.google.com/presentation/d/1m05eRr-mqSQIrOb6V3rDLxb3Rtj8gO5CkxphlGSv06I/edit#slide=id.g3a0892a38_030>`_

Ch6 - Equivalence Class Testing
========================================

- weak normal
- strong normal
- weak robust
- strong robust

Ch7 - Decision Table-based Testing
========================================

- `CH7 課程講義 <https://docs.google.com/presentation/d/1zUOofTArt4Q-APf-Ne3kE_JUt5gXZFzQTIqBL0VOJqA/edit#slide=id.g4821ca451_016>`_

Ch8 - Path Testing
========================================

Program Graphs
------------------------------

用 imperative 寫出來的程式的 program graphs 會是

- directed graph
- nodes are statement fragements
- edges are flow of control

DD-Paths
------------------------------

Test Coverage Metrics
------------------------------

- node coverage
- edge coverage
- chain coverage
- path coverage

- https://bitbucket.org/ned/coveragepy

Miller's Coverage Metrics
------------------------------

Todo

DO-178B
------------------------------

Ch9 - Data Flow Testing
========================================

- Define/Use Testing
- Slice-Based Testing
- Program Slicing Tools

重點: 變數在哪裡拿到 values、在哪裡被使用

- unifying structure of **test coverage** metrics
- program slice (1979 - Mark Weiser)

define/reference anomalies
------------------------------

檢查以下 issue

- 只有定義但沒有被使用的變數
- 變數未定義就使用
- 變數定義了多次
- 變數在使用之前就被 deallocate

defining node
------------------------------

usage node
------------------------------

P-use & C-use
------------------------------

Ref
========================================

- `白箱測試與黑箱測試（上） <http://teddy-chen-tw.blogspot.tw/2014/06/blog-post.html>`_
