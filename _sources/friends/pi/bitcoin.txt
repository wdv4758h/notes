=======
Bitcoin
=======

觀念
-----
比起貨幣，Bitcoin 更像是貴金屬；Bitcoin 不由中央銀行發行，礦工可以自行開採，而且總數量有上限（略少於 2100 萬個）

Bitcion 系統把所有的交易紀錄存在分散式的 Database 裡面，稱為區塊鏈（Blockchain）

區塊鏈由區塊（Block）組成，每個區塊由一些交易紀錄組成，原則上是線性的

礦工們透過 P2P 的方式互相連接，幫忙驗證所有的交易紀錄，並從中獲得 bitcoin（獎金或手續費）

全球所有的 Bitcoin client 藉由共享這串區塊鏈來決定每個錢包裡面有多少餘額


交易（Transaction）
--------------------
每一筆交易包含：

* 基於哪些交易（它們的 Transaction ID）

  - 第一筆交易被稱為「創世區塊（genesis block）」

* 轉到哪個錢包

  - 由此可知每個錢包裡存放著一堆 Transaction ID，而不是 bitcoin
  - 要是錢包掉了或是 Transaction ID 掉了，就會有一些 bitcoin 消失

* 沒被提到的 bitcoin 將被視為手續費，由礦工吸收

  - 所以每筆交易都要記得把剩下的錢轉給自己

每筆交易都會被廣播到整個 Bitcoin 網路上


區塊（block）
--------------
每個 block 包含：

* 一個可以任意填寫的欄位
* 「上一個 block」的 sha256 hash 值
* 數筆交易紀錄，總大小上限為 4GB

礦工們若要開始挖礦，會先產生一個新的 block，在裡面加上第一條訊息：「把 X 個 bitcoin 做為獎金給自己」

不斷收集網路上的交易訊息，累積在 block 裡面，並不斷計算 block 的 sha256 hash 值

只要 sha256 hash 值小於某個值，該礦工就可以把這個 block 廣播到整個 Bitcoin 網路上（其他礦工會幫忙驗證他所拿到的獎金）

獎金的值和需要滿足的 hash 值都會根據當時挖礦的難度調整，使得總量以及 block 生產的速度固定


假造/更改 blockchain
``````````````````````
由於每個 block 都透過 sha256 hash 值指向上一個 block，這形成了非常難假造的 blockchain

想要假造 block，至少需要掌握整個 Bitcoin 網路一半以上的運算能力，不然 hash 值就會不符合

若有如此強的運算力，就可以用超過其他所有礦工的速度生產出 block，主導 blockchain 的長度


分支
``````
理論上是有可能同時有兩名礦工挖到 bitcoin，並同時把自己的結果廣播出去，此時整個網路會分成兩半，分別接收到不同的結果

哪個結果最後會被承認，取決於哪邊有礦工挖到新的 bitcoin，使該方向的 blockchain 變得比另一邊更長，導致所有礦工都改承認新的結果


其他
-----
* 最小單位為 0.00000001 bitcoin（1 聰）
* 為了避免 blockchain 分支所造成的帳目變動，有些 Bitcoin 平台在計算錢包總額時會暫時不把最後 6 個 block 計入，所以用 Bitcoin 付款會需要大約一個小時後才會被確認
* Bitcoin 系統限制了一個 Block 的大小，漸漸使得交易開始累積在礦工身上，無法被加入 block ，造成交易確認的時間變得更長

  - Bitcoin 的核心開發者之一提出提案，稱為 Bitcoin XT，希望調高這個限制
  - 但過半數核心開發者不同意（3 比 2）
  - 於是 Bitcoin XT 自己發佈了 Client，讓網路世界來決定未來該如何發展
  - 舊的 Client 不接受超過 4GB 的 block，blockchain 產生了「硬分支」，同時開始發展
  - 中國的礦場佔了 50% 以上的運算力，而他們不想更換，於是 Bitcoin XT 處於劣勢

* 每個區塊沒有限制至少要有多少條交易紀錄，確實有出現過只有一條獎金交易的 block，但這樣很不划算


更多
-----
已經有許多以 blockchain 為概念的 coin 出現（例如 Doge coin），其中一個是 Ethereum，它有一些特色

* 既然 blockchain 實際上就是個巨大的分散式 Database，為什麼不把 DNS 存在裡面呢？礦工可以努力「挖到自己的 Domain」
* Ethereum 想讓 blockchain 變得「programmable」

  - 任何人都可以發行自己的 coin，只要提供該 coin 和 Ethereum coin 轉換的方式（用程式碼描述）
  - 任何人都可以在上面搭建分散式的應用服務
