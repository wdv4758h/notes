========================================
Regular Expression
========================================

Russ Cox - Part 1 - Regular Expression Matching Can Be Simple And Fast
======================================================================

文章閱讀散亂紀錄(未整理): ::

    兩種 regular expression 方式

    一種用於許多程式語言
    例如 Perl

    另一種用於其他少數地方
    例如 awk 和 grep

    其中用 (a?){n}a{n} 和 a{n} 來測試的話會發現 Perl 的實作下時間會和 n 呈指數成長

    相比之下 awk 和 grep 使用的 Thompson NFA 就呈現較緩慢的成長速度

    其中 Perl 的使用的是秒，然而 Thompson 使用的數量級是 microseconds (us) (微秒)

    這是因為 “pathological” regular expressions 會讓 Perl 的實作跑得非常慢


    但是對於 Thompson 的實作而言，沒有任何 regex 是  “pathological” regular expressions

    那為何 Perl 不選用 Thompson 的實作呢？

    regex 是好理論導致好程式的經典案例
    thomopson 把理論實作到 QED 在 CTSS 上

    在 Perl 加入的新 regex features 中，只有 backreference (\1 \2) 是有增加新能力的，其他都可以用較長的舊有方式來達成

    The power that backreferences add comes at great cost: in the worst case, the best known implementations require exponential search algorithms, like the one Perl uses. Perl (and the other languages) could not now remove backreference support, of course, but they could employ much faster algorithms when presented with regular expressions that don't have backreferences

    deterministic finite automaton (DFA)
    任何可能的輸入都只會讓 state 轉移到單一一個新的 state，所以是 deterministic

    non-deterministic finite automata (NFAs or NDFAs)

    regular expression 和 NFA 同等能力
    所有 regex 都可以轉成 NFA (NFA 也都可以轉成 regex)
    轉換方式有很多種，Thompson 在 1968 年發佈在 CACM 的論文就是其中一種

    講述實作方式

    講述現今常見的擴充用法如何實作在 Thompson 之上

    As mentioned earlier, no one knows how to implement regular expressions with backreferences efficiently, though no one can prove that it's impossible either. (Specifically, the problem is NP-complete, meaning that if someone did find an efficient implementation, that would be major news to computer scientists and would win a million dollar prize.)


    講述 regex 實作的歷史

    鮮為人知的 Pike 實作


Russ Cox - Part 2 - Regular Expression Matching: the Virtual Machine Approach
=============================================================================

Russ Cox - Part 3 - Regular Expression Matching in the Wild
===========================================================


Reference
========================================

* `Russ Cox - Implementing Regular Expressions <https://swtch.com/~rsc/regexp/>`_
* `Regular Expression to NFA (Non-Deterministic Finite Automata) <http://hackingoff.com/compilers/regular-expression-to-nfa-dfa>`_
