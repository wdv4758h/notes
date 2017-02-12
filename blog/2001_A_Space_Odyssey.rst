:title: 2001: A Space Odyssey (2001 太空漫遊)
:slug: 2001-a-space-odyssey
:date: 2015-04-03 15:02
:modified: 2015-04-03 15:02
:category: Misc
:tags: AI, movie
:author: wdv4758h
:summary:

《2001: A Space Odyssey》是一部 **1968** 年上映的經典科幻片，
故事改編自 Arthur Clark 寫的一些短篇，
由 Arthur Clark (作家) 和 Stanley Kubrick (導演) 共同創作，
電影拍攝的同時 Arthur Clark 也在創作小說，
最後小說和電影在同一時期面世。

電影於 1964 年開始拍攝，當時國際仍處於冷戰時期 (1947 ~ 1991)，而且正值太空競賽期間 (1957 ~ 1975)。
1961 年 4 月蘇聯才剛送上第一位太空人 (當時蘇聯的太空技術領先美國)，
種種因素迫使美國投入阿波羅計劃，以登上月球為目標，
美國的甘迺迪總統也在 1961 年 5 月宣佈將會在 1970 年之前將太空人送上月球並成功返回。
而後在 1969 年 7 月，Buzz Aldrin 和 Neil Armstrong 成為史上第一個登入月球的人類。

《2001: A Space Odyssey》剛好在太空技術正開始發展的時間點，
人們開始對太空有許多的想像、寄望，
藉由這部電影可以看到當時對未來的各種想像，
也因此成為現今科幻片的經典代表。

但是對於未來的想像難免過於樂觀，
電影想像的未來 "2001 年" 早就已經過了，
現在已經來到了 2015 年，
但是片中還是有很多技術尚未實現。


.. image:: /images/space/space-voice.png
    :alt: Voice

.. image:: /images/space/space-ai.png
    :alt: AI

.. image:: /images/space/space-ai-chess.png
    :alt: AI Chess

**語音辨識** ，這部電影有很多地方是建立在電腦已經能正確辨識人類說的話之上。
早在 1932 年，Bell Labs 就有這方面的研究。
1952 年，Bell Labs 建立了一個辨識系統，不過能力非常非常差。
後來因為經費因素而影響到了後續研究。
1960 年代晚期，開始出現使用 Hidden Markov Model (HMM) 來做語音辨識，
因此開始可以結合不同領域的知識來形成一個統一的機率模型 (像是聲學、語言、語法等等)。

1971 年，DARPA 對語音辨識投資了 5 年的研究，BBN、IBM、CMU、Stanford Research Institute 都參與了這項計劃，
但是後續 DARPA 就不再投資這個部份了 (相比其他能源或醫療或登月相關計劃，認為這領域沒有那麼重要)。
1980 年代開始出現 n-gram 語言模型。
Sphinx (CMU Sphinx speech recognition engines) 由李開復 (台灣) 開發，
利用 HMM 和 n-gram 而形成，特色在於第一個做到 speaker-independent。
Sphinx 2 則是針對 performance 改過的版本，由黄学东 (美國) 開發，
在 1992 年 DARPA 的評估時被認為是當時效能最好的。

2000 年，Lernout & Hauspie 取得了 Dragon Systems 這套系統，
成為當時業界的領導者，後來 Lernout & Hauspie 的 speech technonogy 被 ScanSoft 買下，
在 2005 成為 Nuance，之後與 Apple 合作，將此技術使用於 Siri 上。
2009 年開始有 deep learning 用運在語音辨識上，被稱為「自 1979 年後語音辨識準確度最戲劇性的變化」，
錯誤率下降了 30%。


**人工智慧** ，片中的 AI (**HAL 9000**) 已經能夠和人類下棋，
也能用一般的人類語言來對話，並且可以幫忙操控太空船的諸多部份，
甚至有自己的思考，會提出問題。

AI 這領域從 1956 年位在 Dartmouth College 的一場 conference 後開始被廣泛討論，
而當初參與這研討會的成員也變成了 AI 研究的領導者。
之後發展冷冷熱熱，投資來來去去。
1997 年 5 月，IBM 的 Deep Blue 成為世界上首個在西洋棋上擊敗人類世界冠軍的 AI。
2011 年 2 月，IBM 的 Watson 則在 Jeopardy! 這個智力競賽中擊敗兩位紀錄保持人。
但到現在依舊還是無法完整模擬人類的大腦，AI 領域上還是有很多地方需要被克服。


.. image:: /images/space/space-video-call.png
    :alt: Video Call

**視訊電話** ，其實早期就有在發展 (甚至在 1876 年就有出現概念了)，曾經有做在電信網路上過，
到了後來網際網路發展成熟後就轉往用 TCP/IP 當底層來實作，
所以現今已經藉由網路讓 PC、手機等各個地方都可以使用視訊電話的服務。
(而網際網路的話在 1960 年代開始發展 ARPANET，到 1982 年 TCP/IP 成為 ARPANET 上的標準 protocol)

Reference
========================================

* `【科學史上的今天】4/2——《2001太空漫遊》首映 <http://history.pansci.tw/post/115218661780/4-2-2001-1968>`_
* `Wikipedia - History of the Internet <http://en.wikipedia.org/wiki/History_of_the_Internet>`_
* `Wikipedia - History of videotelephony <http://en.wikipedia.org/wiki/History_of_videotelephony>`_
* `Wikipedia - Speech recognition <http://en.wikipedia.org/wiki/Speech_recognition>`_
* `Wikipedia - History of artificial intelligence <http://en.wikipedia.org/wiki/History_of_artificial_intelligence>`_
* `Wikipedia - AI winter <http://en.wikipedia.org/wiki/AI_winter>`_
* `Wikipedia - History of tablet computers <http://en.wikipedia.org/wiki/History_of_tablet_computers>`_
