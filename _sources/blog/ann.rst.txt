:title: [WIP] Artificial Neural Network - Again
:slug: artificial-neural-network-agaion
:date: 2015-04-05 22:48
:modified: 2015-04-05 22:48
:category: Misc
:tags: ANN
:author: wdv4758h
:summary:

**[WIP] 持續更改中**

Artificial Neural Network
========================================

Artificial Neural Network，中文有時翻做「類神經網路」，
顧名思義就是想模擬生物大腦的神經系統來解決生物能迅速做到但電腦還不能做到的事情。

其實當初就覺得有點興趣，想投入時間進去學一下，
所以在大二下的時候就有去修了系上一門叫「類神經網路」的課，
但是中間覺得老師上課實在太無聊 ...，後來就決定退掉，
那時候每次上課都只有個位數的學生到場 Orz ...

這學期 (大三下) 去修了研究所的「電腦視覺」，
剛好也碰到一些跟類神經有關的地方，
再加上近期也一直在各個地方看到相關訊息，
於是還是來好好補強一下 :P (還債)

History
========================================

早在 1943 年的時候，Warren McCulloch 和 Walter Pitts 就基於數學和演算法提出了類神經的計算模型，
被稱為 "threshold logic"。從這模型之後，類神經的研究就分成兩邊，一邊致力於模擬生物的大腦，
另一邊則專注在應用於人工智慧領域。

在 1940 年代晚期，心理學家 Donald Hebb 基於突觸的可塑性提出了學習的假說，
被稱為 Hebbian learning。其理論為持續重複的刺激會讓突觸傳遞效能增加
(像是平常不斷做某個動作，那這個動作的反應時間就會降低)，
常被總結為 "Cells that fire together, wire together"。
Hebbian learning 被視為典型的非監督式學習，其後來的變種成為 long term potentiation (LTP) 的早期模型。
後來在 1948 年和 Turing's B-type machines (Unorganized machine) 開始運用在運算模型。

1954 年，Farley 和 Wesley A. Clark 在 MIT 用實際的機器來模擬 Hebbian network。
其他類神經計算的機器由 Rochester, Holland, Habit, Duda 在 1956 年製造。

1958 年，Frank Rosenblatt 提出了 perceptron (感知器)，
perceptron 是一個用於 pattern recognition 的演算法，
作法是利用簡單的加減法來做兩層的學習。
除了數學式子，Rosenblatt 也說明了基本的 perceptron 不支援一些處理，
例如 exclusive-or，exclusive-or 的問題到了 1975 年 Paul Werbos 提出 backpropagation 的作法才解決。

類神經的發展在 Marvin Minsky 和 Seymour Papert 發表 machine learning 的研究後停滯，
因為裡頭提到了兩個相當重要的問題，
其中一個就是單層的 perceptron 不能解 exclusive-or 的問題，
另一個是電腦還沒複雜到足以有效率地應付類神經所需要的長時間運算。
研究就此緩慢了下來，直到電腦變得更有效率，
以及 1975 年 Paul Werbos 提出 backpropagation 的作法解決了 exclusive-or 的問題。

1980 年代中期，parallel distributed processing 在 connectionism 的發展下流行起來
(parallel distributed processing 有時簡稱為 PDP，跟 DEC 出的 PDP 衝名啦 XD)，
David E. Rumelhart 和 James McClelland 在 1986 年提供了利用 connectionism 來模擬神經運作的完整說明。

類神經在人工智慧領域一向被視為大腦神經運作的簡化模型，
但其實這模型和實際大腦運作的架構的相關性一直遭到質疑，
因為類神經沒有很明確地是模擬大腦哪個部份的功能。

後來類神經在 machine learning 的領域上逐漸被 SVM (support vector machines)
和其他較簡單的方式 (例如 linear classifiers) 取代。
直到 2000 年代末期 deep learning 的到來才讓類神經又逐漸受到更多的注目。

2009 年到 2012 年間，
來自 Swiss AI Lab IDSIA 的 Jürgen Schmidhuber 的研究團隊開發了
recurrent neural networks 和 deep feedforward neural networks
贏得了諸多 pattern recognition 和 machine learning 的比賽。
舉例來說，在 2009 年的 ICDAR (International Conference on Document Analysis and Recognition)，
Alex Graves 等人的 bi-directional 和 multi-dimensional long short term memory (LSTM)
就在沒有三種語言的背景知識下贏了三場手寫辨識比賽。

Dan Ciresan 和 IDSIA 的同事做了利用 GPU 的快速實作，
也因此贏得了諸多比賽 (例如 IJCNN 2011 Traffic Sign Recognition Competition、
ISBI 2012 Segmentation of Neuronal Structures in Electron Microscopy Stacks challenge)。
他們的類神經網路是第一個在辨識上可以跟人類競爭的，
甚至在一些項目中可以達到超過人類的辨識率
(例如 traffic sign recognition (IJCNN 2012)、MNIST handwritten digits problem of Yann LeCun at NYU)。

Reference
========================================

* `Wikipedia - Deep learning <http://en.wikipedia.org/wiki/Deep_learning>`_
* `Wikipedia - Artificial neural network <http://en.wikipedia.org/wiki/Artificial_neural_network>`_
* `Wikipedia - Unorganized machine <http://en.wikipedia.org/wiki/Unorganized_machine>`_
* `Wikipedia - Long-term potentiation <http://en.wikipedia.org/wiki/Long-term_potentiation>`_
* `Wikipedia - Backpropagation <http://en.wikipedia.org/wiki/Backpropagation>`_
* `Wikipedia - Long short term memory <http://en.wikipedia.org/wiki/Long_short_term_memory>`_
* `Wikipedia - Connectionism <http://en.wikipedia.org/wiki/Connectionism>`_
* `Wikipedia - MNIST database <http://en.wikipedia.org/wiki/MNIST_database>`_
