:title: [Prolog] Cut
:slug: prolog-cut
:date: 2014-10-29 01:10
:category: Prolog
:tags: prolog
:author: wdv4758h
:summary: proglog's cut

Prolog 裡，"\+" 等同於 not (檢查一個 goal 不能證明為真的 predicate)

"!" 則是切除邏輯判斷的結構

- 在 ! 左邊的 predicates 成立，就把在 ! 之後 head 相同的情況放棄，
- 在 ! 左邊的 predicates 不成立，就把同一行程式 ! 右邊的 predicates 放棄掉

.. code-block:: prolog

    a(X, Y) :- b(X), !, c(Y).
    b(1).
    b(2).
    b(3).

    c(1).
    c(2).
    c(3).

    ?- a(Q, R).
    Q = 1
    R = 1 ;
    Q = 1
    R = 2 ;
    Q = 1
    R = 3 ;
    No
    .

.. code-block:: prolog

    a(X, Y) :- b(X), c(Y), !.
    b(1).
    b(2).
    b(3).

    c(1).
    c(2).
    c(3).

    ?- a(Q, R).
    Q = R, R = 1.

Links
========================================

- `PTT - Prolog的符號: "\+"和"!"是甚麼? <https://www.ptt.cc/bbs/Programming/M.1261677915.A.162.html>`_
- `Prolog/Cuts and Negation <http://en.wikibooks.org/wiki/Prolog/Cuts_and_Negation>`_
