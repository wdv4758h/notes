========================================
壓縮入門
========================================


.. contents:: 目錄


簡單的壓縮法 - Run-length Encoding
========================================

* `Wikipedia - Run-length encoding <https://en.wikipedia.org/wiki/Run-length_encoding>`_
* `Rosetta Code - Run-length encoding <https://rosettacode.org/wiki/Run-length_encoding>`_


直接跑過字串，把重複的資料單元以一個該資料單元以及代表次數的數字做表示。
對於具有許多重複性的資料較有用，例如：簡單的圖像、簡單的影像，
對於分佈較複雜的資料比較沒有效，甚至會讓檔案變大。


範例：

輸入 ::

    WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW

輸出 ::

    12W1B12W3B24W1B14W

或是 ::

    W12B1W12B3W24B1W14


Run-length encoding 還可以用很多不同的方法表示，
例如對於重複資料較少的資料，
可以改採「重複兩個字元加數字時代表該字元的次數，
而只出現一個字元時就直接代表該字元」，
藉此省去只有一個字元時的多餘表示。

範例：

輸入 ::

    WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW

輸出 ::

    WW12BWW12BB3WW24BWW14


如果做完 Run-length encoding 後還要套用其他的壓縮演算法時，
為了要更好壓縮，
可以把出現次數跟原本的資料分離，
藉此可以分開處理。

範例：

輸入 ::

    WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW

輸出 ::

    WWBWWBBWWBWW
    12,12,3,24,14


此作法特別適用於 icons，
也是早期圖像壓縮的常用手法（例如線上服務 CompuServe），
直到後來更複雜的格式出現（例如 GIF）。
雖然 JPEG 有效地把這作法用於前處理過後（轉換、quantizing image blocks）所剩下的係數，
但此作法在照片類的圖片比較不適用。
另外 Run-length encoding 早期也有用於電視訊號（1967 年）。

一些 Run-length encoding 常見的地方：

* Truevision TGA
    - 由 Truevision 於 1984 年釋出的圖片格式
* PackBits
    - Apple 早期所使用的格式
* PCX
    - 由 ZSoft Corporation 於 1985 年釋出的圖片格式
* ILBM
    - 由 Electronic Arts 於 1985 年釋出的圖片格式，用於早期的遊戲
* T.45
    - 國際電信聯盟（ITU，International Telecommunication Union）訂定的傳真標準
    - 結合 Modified Huffman coding 一起使用
    - 因為傳真常常是一堆空白，偶爾有些資料，所以壓縮成果蠻有效的



簡單的壓縮法（改進） - BWT
========================================

* `Wikipedia - Burrows–Wheeler transform <https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform>`_

BWT 是 Burrows–Wheeler transform 的縮寫，
該演算法會將字串重新排列，
產生的結果會有較多的連續重複字元。
這對於壓縮演算法很有利（例如 move-to-front transform 或 run-length encoding）。
重點是這個操作是可逆的，
不需要儲存任何額外的資訊。
因此對於需要儲存的資料量來說，
這是個可以提昇壓縮效果的「免費」操作，
只需要花費一些額外的計算。

使用於 bzip2。


範例：

輸入（ ``|`` 代表 EOF） ::

    ^BANANA|

建立所有順序轉換 ::

    ^BANANA|
    |^BANANA
    A|^BANAN
    NA|^BANA
    ANA|^BAN
    NANA|^BA
    ANANA|^B
    BANANA|^

用字典順序排列 ::

    ANANA|^B
    ANA|^BAN
    A|^BANAN
    BANANA|^
    NANA|^BA
    NA|^BANA
    ^BANANA|
    |^BANANA

取出最後一行作為輸出 ::

    BNN^AA|A


逆操作（不斷地向前一行插入並排序）：

::

    B         A        BA         AN        BAN         ANA        BANA
    N         A        NA         AN        NAN         ANA        NANA
    N  sort   A  add   NA  sort   A|  add   NA|  sort   A|^  add   NA|^
    ^ ------> B -----> ^B ------> BA -----> ^BA ------> BAN -----> ^BAN
    A         N        AN         NA        ANA         NAN        ANAN
    A         N        AN         NA        ANA         NA|        ANA|
    |         ^        |^         ^B        |^B         ^BA        |^BA
    A         |        A|         |^        A|^         |^B        A|^B


            ANAN        BANAN         ANANA        BANANA         ANANA|
            ANA|        NANA|         ANA|^        NANA|^         ANA|^B
     sort   A|^B  add   NA|^B  sort   A|^BA  add   NA|^BA  sort   A|^BAN
    ------> BANA -----> ^BANA ------> BANAN -----> ^BANAN ------> BANANA
            NANA        ANANA         NANA|        ANANA|         NANA|^
            NA|^        ANA|^         NA|^B        ANA|^B         NA|^BA
            ^BAN        |^BAN         ^BANA        |^BANA         ^BANAN
            |^BA        A|^BA         |^BAN        A|^BAN         |^BANA


           BANANA|         ANANA|^        BANANA|^         ANANA|^B
           NANA|^B         ANA|^BA        NANA|^BA         ANA|^BAN
     add   NA|^BAN  sort   A|^BANA  add   NA|^BANA  sort   A|^BANAN
    -----> ^BANANA ------> BANANA| -----> ^BANANA| ------> BANANA|^
           ANANA|^         NANA|^B        ANANA|^B         NANA|^BA
           ANA|^BA         NA|^BAN        ANA|^BAN         NA|^BANA
           |^BANAN         ^BANANA        |^BANANA         ^BANANA|
           A|^BANA         |^BANAN        A|^BANAN         |^BANANA


輸出以「EOF」結尾的那一列：

::

    ^BANANA|


範例 Python 程式：

.. code-block:: python

    def bwt(s):
        n = len(s)
        table = [s[n-i:]+s[:n-i] for i in range(n)]
        table.sort()
        return ''.join(t[-1] for t in table)

    def reverse_bwt(s):
        l = [c for c in s]
        l.sort()

        for _ in range(len(s)):
            l = [i+c for c, i in zip(l, s)]
            l.sort()

        for i in l:
            if i[-1] == "|":
                return i

    if __name__ == '__main__':
        print(bwt("^BANANA|"))
        print(reverse_bwt("BNN^AA|A"))



更有效率的作法：

::

    TODO



