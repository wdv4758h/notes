========================================
Statifier
========================================

Statifier 的目標是要建立 portable、self-contained 的 Linux executables，
要達到這樣的目標 Statifier 做的是把原本 dynamic linking 的程式所用到的 shared libraries 都抓進去，
變成單一一個靜態連結執行檔，
不需要外部的 dependency。

不過目前 Statifier 在某些情況下還無法達成效果，
另外非開源的 Ermine 則是說已經成功支援了。

Reference
========================================

* `Statifier <http://statifier.sourceforge.net/>`_
* `Ermine <http://www.magicermine.com/>`_
* `Statifier and Ermine features compared <http://www.magicermine.com/products.html#feature_comparison>`_
