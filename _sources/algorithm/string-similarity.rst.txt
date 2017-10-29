========================================
String Similiarity
========================================


.. contents:: 目錄


Edit Distance
========================================

Edit Distance = 更動多少次數後，兩字串會一樣

計算方式有很多種：

+------------------------------+-----------+----------+--------------+----------------------+
| Algorithm                    | insertion | deletion | substitution | transposition (換位) |
+==============================+===========+==========+==============+======================+
| Hamming distance             | X         | X        | O            | X                    |
+------------------------------+-----------+----------+--------------+----------------------+
| Longest Common Subsequence   | O         | O        | X            | X                    |
+------------------------------+-----------+----------+--------------+----------------------+
| Levenshtein distance         | O         | O        | O            | X                    |
+------------------------------+-----------+----------+--------------+----------------------+
| Damerau-Levenshtein distance | O         | O        | O            | O                    |
+------------------------------+-----------+----------+--------------+----------------------+


Levenshtein distance
------------------------------

* http://en.wikipedia.org/wiki/Levenshtein_distance
* http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance


Levenshtein distance 是用來評估兩 sequence 差別度的一種 string metric，
兩個字串的 Levenshtein distance 就是一個字串變成另一個字串的最小字元編輯次數 (insert, delete, substitute)，
由俄國科學家 Vladimir Levenshtein 在 1965 年提出

* substitution : s **a** t -> s **i** t
* insertion : st -> s **i** t
* deletion : si **a** t -> sit

看一段簡單的 Python code 來了解運算:

.. code-block:: python

    def lev(a, b):
        if not a: return len(b)
        if not b: return len(a)

        return min(lev(a[1:], b[1:]) + (a[0] != b[0]),
                   lev(a[1:], b)+1,
                   lev(a, b[1:])+1)

傳入 min function 的有 3 個，
第一個是兩邊都減一個字元，如果減去字元不一樣就把次數加 1 (substitute)，
第二個是 a 減去一個字元並且次數加一，這可以看成 a 字串的 delete 或是在 b 前面 insert 了和 a match 的字元，
第三個跟第二個雷同

當然，這個寫法很沒有效率，做了很多次不必要的遞迴，用 CPython (Python 3.4) 下去跑測試，
丟個簡單的字串當測試 ``lev('fasfasf', 'afvq')`` 這個做法大約要 1.9 ms

簡單地用 lru cache 來做 DP:

.. code-block:: python

    from functools import lru_cache

    def lev(a, b):

        @lru_cache(maxsize=None)
        def _lev(a, b):
            if not a: return len(b)
            if not b: return len(a)

            return min(_lev(a[1:], b[1:]) + (a[0] != b[0]),
                       _lev(a[1:], b)+1,
                       _lev(a, b[1:])+1)
        return _lev(a, b)


利用 lru cache 來簡單地做 DP 後，剛剛的測試現在大約變成 370 µs

當然，還有很多改進空間，像是

* 自己實際寫 DP
* 判斷字串相同就直接回傳 0 (對於有很多相同子字串的情況可以用字串比對的 cost 換掉一些遞迴)
* 減去頭尾相同的子字串

如果要速度的話: `python-Levenshtein <https://github.com/ztane/python-Levenshtein>`_
，C 寫的 Python extension，測試下去大概會變成 300 ns 以內。

計算的 cost 大約會是 O(len(a) * len(b))，所以在幫助 fuzzy string searching 的時候，
比較的字串同常會比較小，以便於提升速度


其他性質：

* lower bound : 兩字串的長度差
* upper bound : 較長的字串的長度
* 只有當字串相等時會是 0
* 當字串長度相同時，Hamming distance 會是 Levenshtein distance 的 upper bound
* [三角不等式] 兩個字串的 Levenshtein distance 不會大於分別和第三個字串的 Levenshtein distance 的合


使用情境：

* spell checkers
* OCR
* assist natural language translation based on translation memory
* http://en.wikipedia.org/wiki/Record_linkage



參考
========================================

* `Jellyfish - Python library for doing approximate and phonetic matching of strings <https://github.com/jamesturk/jellyfish>`_
* `Distances.jl - Julia package for evaluating distances(metrics) between vectors <https://github.com/JuliaStats/Distances.jl>`_
