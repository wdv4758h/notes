========================================
Constraint Satisfaction Problem
========================================

FAQ
========================================

「什麼是 CSP ？」

「為什麼 CSP 重要？CSP 可以拿來解決什麼樣的問題？ 」

「實務上有哪些地方真的在使用 CSP ？」

「什麼是 SAT ？」

「CSP 和 SAT 的關聯性？」

「CSP 的歷史？」

「與 CSP 有密切關連性的領域？」

    * Linear Programming (線性規劃)
    * Integer Linear Programming (整數規劃)
    * Non-Linear Programming (非線性規劃)
    * 數值分析理論
    * ...

「CSP 模型可用於哪裡？」

    * 作業研究 (Operations Research)
    * 網路流量(Network Flows)
    * 最佳化問題(Optimization Problems)
    * ...



CSP Introduction
========================================

CSP 會使用 tuple 表示： ``(V, D, C)`` ，
其中 V (Variable) 代表有限地變數 (X1, X2, ... Xn)，
D (Domain) 代表每個變數可以填入的值，
C (Constraint) 代表所有的限制。

例如一個著色問題 (在各區塊塗上顏色，但相鄰的區塊不能有相同顏色)：

::

    colors : white, black, red

    +--------+--------+
    |        |   B    |
    |   A    +--------+
    |        |   C    |
    +--------+--------+

此時： ::

    V = {A, B, C}

    D = { dom(A) = { white, black, red },
          dom(B) = { white, black, red },
          dom(C) = { white, black, red } }

    C = { ((A, B), A ≠ B),
          ((A, C), A ≠ C),
          ((B, C), B ≠ C) }

最後結果： ::

    (A, B, C) = { (white, black, red), (white, red, black),
                  (black, white, red), (black, red, white),
                  (red, white, black), (red, black, white) }


Constraints 有一個重要的性質是「arity」，
arity 指的是使用到的變數數量，
如果 arity 為 2 則稱為 Binary Constraints，
如果 arity 大於 2 則稱為 Non-Binary Constraints，
而「所有 Non-Binary Constraints 都可以轉換成 Binary Constraints」。

如前面所提到，
Binary Constraint 指的是這個 constraint 「只有」兩個變數參與。
這邊再舉個稍微實際一點點的例子，
在 N 皇后問題中，目標是要在 N x N 的棋盤上放入 N 個皇后，
而這 N 個皇后之間都必須彼此不互相攻擊，
因此我們會有一個 constraint 集合，
該集合裡面包含「皇后 1 不可攻擊皇后 2」、「皇后 1 不可攻擊皇后 3」、「皇后 1 不可攻擊皇后 4」、……，
此集合包含所有 N 個皇后間的配對，
而每個 constraint 都只有兩個不同的皇后參與，
因此每個 constraint 都是 binary constraint。

先前有提到「所有 Non-Binary Constraints 都可以轉換成 Binary Constraints」這個性質，
而目前有兩種把 Non-Binary Constraints 轉換成 Binary Constraints 的方式，
分別為：

1. dual transformation
2. hidden (variable) transformation

----

Consistency Method 是用來把原本的 Network 轉換成較小的 Network，
最後期望變成 Minimal Network (M)

Local Consistency 是 CSP 裡重要的概念，
Local Consistency 是 CSP 在 Local 部份的屬性。

* Node Consistency
* Arc Consistency
* Path-Consistency
* 3-Consistency
* K-Consistency

::

    R  ⊇  R₁  ⊇   R₂ ⊇ ... ⊇ Ri ⊇ ... ⊇ M
      Arc    Path

----

Approximation algorithm (preprocessing, local consistency)

* Arc‐Consistency (Waltz 1972)
* Path‐Consistency (Montanari 1974, Mackworth 1977)
* i‐Consistency (Freuder 1982)


Node Consistency

    如果某變數 (Variable) 的值 (Domain) 都符合該變數的 Unary Constraints，
    則稱該變數為 Node Consistency

    ::

        V = { X }

        D = { dom(X) = { 0, 1, 2 } }

        C = { (X, X > 0) }

        => Node Consistency

        V = { X }

        D = { dom(X) = { 1, 2 } }

        C = { (X, X > 0) }


Arc Consistency

    如果某變數 (Variable) 的值 (Domain) 都符合該變數的 Binary Constraints，
    則稱之為 Arc Consistency。

    如果該 Network 內的所有變數 (Variable) 都滿足 Arc Consistency，
    則稱該 Network 為 Arc Consistency。

    ::

        V = { X, Y }

        D = { dom(X) = { 1, 2 },
              dom(Y) = { 1, 2 } }

        C = { ((X, Y), X > Y) }

        => Arc Consistency

        V = { X, Y }

        D = { dom(X) = { 2 },
              dom(Y) = { 1 } }

        C = { ((X, Y), X > Y) }


Arc Consistency Algorithm AC‐3

+------------+--------+
| 時間複雜度 | O(ek³) |
+------------+--------+
| Steps      | O(k²)  |
+------------+--------+
| Loop       | O(ek)  |
+------------+--------+


Path-Consistency (3-Consistency)

    對於滿足 (Xi, Xj) 間所有 Binary Constraints 的值 (a, b)，
    都存在屬於 Xk 的 Domain 的值 c，
    使得 (a, c) 滿足 (Xi, Xk) 間所有的 Binary Constraints，
    且 (b, c) 滿足 (Xj, Xk) 間所有的 Binary Constraints，
    則稱 Xi 和 Xj 為與 Xk 滿足 Path Consistency

* (i, j)-Consistency
* (1, 1)-Consistency => Arc Consistency
* (2, 1)-Consistency => Path Consistency
* (1, 2)-Consistency => Path Inverse Consistency

----

所有的 SAT (Propositional Satisfiability) 都可以表示成 CSP

----

Constraint Graph

* 每個變數都畫一個節點 (Node)
* 每個限制 (Constraint) 都畫一條連結 (Arc)

----

Contraint Diagram

----

Contraint Table

----

Contraint Matrix

----

Contraint Formula

----

著名案例：

* 八皇后問題 (8-Queens problem)
* 數獨 (Sudoku)
* 地圖著色 (map coloring)
* 排班問題
* 資源配置最佳化問題

----

Positive or Negative Representation

Positive：紀錄允許的操作

Negative：紀錄不允許的操作

(我們使用 Positive Representation)

Closed World Assumption：沒有說允許的就是不允許

----

The 4‐Queen Problem

----

Boolean Satisfiability Problem

a.k.a Propositional Satisfiability Problem

a.k.a SATISFIABILITY

a.k.a SAT

----

Naïve Backtracking Algorithm

Backtrack 起先被稱為 Forward

----

Constraint Propagation

利用 Constraint 來減少後續變數值的選擇性

----

如果 rel(proj(ρ)) 和相同的話，代表 ρ 是由 Binary Constraints Network 所表示。

----

尋找 Minimal Network 是 NP-Complete 問題，所以 sub‐minimal 趨近就已經夠了

----

重要性質

* 「所有 Non-Binary Constraints 都可以轉換成 Binary Constraints」


Reference
========================================

* `Wikipedia - Constraint satisfaction problem <https://en.wikipedia.org/wiki/Constraint_satisfaction_problem>`_
* `Wikipedia - Boolean satisfiability problem <https://en.wikipedia.org/wiki/Boolean_satisfiability_problem>`_
* `Wikipedia - Binary constraint <https://en.wikipedia.org/wiki/Binary_constraint>`_
* `Wikipedia - Local consistency <https://en.wikipedia.org/wiki/Local_consistency>`_
* `Binary vs. Non-Binary Constraints <http://www.cs.toronto.edu/~fbacchus/Papers/bcvwaij02.pdf>`_
