========================================
Expression Templates
========================================

藉由紀錄資料中間的操作來減少計算中需要的暫時物件 (例如 vector)，
例如三個 vector a, b, c 相加，
一般會先做 a + b 產生出暫時的 vector 後，
再加上 c 產生出最後的 vector，
而在 Expression Templates 下會直接對每個元素做 a + b + c 的運算，
避免中間產生的暫時 vector。

* `Wikipedia - Expression templates <https://en.wikipedia.org/wiki/Expression_templates>`_
