==============
輸入輸出重導向
==============
在 UNIX-like 環境中工作時，很常會遇到輸入輸出重導向的問題

POSIX 定義了（其實可能更早出現，這裡暫時不探究歷史）輸入輸出的模型：

* stdin：做為程式的輸入，編號為 0
* stdout：做為程式的輸出，編號為 1
* stderr：做為程式錯誤訊息的輸出，編號為 2

所以當你寫了一支程式，可以從 stdin 抓資料、在 stdout 上印出訊息、在 stderr 上印出錯誤訊息

可以想像有三個 channel，資料可以丟進不同的 channel，代表不同的意義

這些 channel 被稱為串流（stream），這些編號則被稱為 file descriptor

程式在執行的時候，只負責從 stdin 抓資料、把資料丟到 stdout 和 stderr

其實這些 stream 的實際來源/目的地都是由 shell 查表得知的

這個行為被稱為「輸入輸出重導向（IO redirection）」

用一張圖表示 ::

  A -> [stdin] -> Command --+---> [stdout] -> B
                            |
                            +---> [stderr] -> C

用 file descripter table 表示

+------------+-----------------+
| 編號       | 實際來源/目的地 |
+============+=================+
| 0 (stdin)  | A               |
+------------+-----------------+
| 1 (stdout) | B               |
+------------+-----------------+
| 2 (stderr) | C               |
+------------+-----------------+


語法
-----

* 語法： ``cmd1 | cmd2`` ，會造成以下效果 ::

    cmd1 --> [stdout] -> [stdin] -> cmd2

* 語法： ``src>dst`` ，會把 ``src`` 的內容導向至 ``dst``

  - ``src`` 為空代表 stdout，否則用 file descripter 表示
  - 若 ``dst`` 為 ``&數字`` ，會導向至對應的 file descripter
  - 注意一行指令中可以出現多次的 ``src>?`` ，此時順序很重要，shell 會依指定的順序改寫 file descripter table
  - 若 ``src`` 原本不存在，則在會表格中新增一列
  - 若 ``dst`` 不存在則會錯誤


範例
-----

Pipe line
```````````
::

  ls -1 | nl

以 ``ls -1`` 的 stdout 做為 ``nl`` 的 stdin


``$()``
`````````
編寫 Shell Script 時，可以把指令的結果抓取起來，存到變數裡面 ::

  value=$(date)

``date`` 的 stdout 會被做成字串，存進 ``value`` 變數中


合併 Stdin/Stdout
```````````````````
準備以下範例程式 ::

  # test.py
  import sys
  print('OUT', file=sys.stdout)
  print('ERR', file=sys.stderr)

執行 ::

  $ python3 test.py
  OUT
  ERR

會印出兩串字在螢幕上，但其實 ``OUT`` 是印在 stdout，而 ``ERR`` 是印在 stderr

可以用 ``wc -l`` 指令檢查 ::

  $ python3 test.py | wc -l
  ERR
         1

``ERR`` 沒有被重導向，直接印在螢幕上， ``OUT`` 則被重導向給 ``wc -l`` ，計算出行數為一行

執行 ::

  $ python3 test.py 2>&1

將會把 ``OUT`` 和 ``ERR`` 都導入 stdout


分離 Stdin/Stdout
```````````````````
執行 ::

  $ python3 test.py 1>out.txt 2>err.txt

將會把 ``OUT`` 和 ``ERR`` 分別寫入 ``out.txt`` 以及 ``err.txt``


交換 Stdin/Stdout
------------------
執行 ::

  $ python3 test.py 3>&2 2>&1 1>&3

將會使 stdout 和 stderr 的內容交換（看起來其實滿難懂的）

shell 的解讀順序如下

1.  ``python3 test.py`` ::

      python3 test.py --+-- [stdout] ---> [A]
                        |
                        '-- [stderr] ---> [B]

2.  ``python3 test.py 3>&2`` ::

      python3 test.py --+-- [stdout] ---> [A]
                        |
                        +-- [stderr] ---> [B]
                        |
                        '-- [3] --------> [B]

    + 抓取 stderr 指向的目的地，並指定給 ``3``

3.  ``python3 test.py 3>&2 2>&1`` ::

      python3 test.py --+-- [stdout] ---> [A]
                        |
                        +-- [stderr] ---> [A]
                        |
                        '-- [3] --------> [B]

    + 抓取 stdout 指向的目的地，並指定給 stderr

4.  ``python3 test.py 3>&2 2>&1 1>&3`` ::

      python3 test.py --+-- [stdout] ---> [B]
                        |
                        +-- [stderr] ---> [A]
                        |
                        '-- [3] --------> [B]

    + 抓取 ``3`` 指向的目的地，並指定給 stdout

做了以上操作以後，stdout 和 stderr 就會互換了，可以用 ``wc -l`` 確認

``3`` 留著沒有影響，反正程式不會去用到


其他
-----
zsh 有 multi-IO 的功能， ``cmd >file1 >file2`` 會把 stdout 複製，故不完全適用上述行為

``man dup``
