:title: [PyPy] IO improvements
:slug: pypy-io-improvements
:date: 2014-11-06 00:15
:category: Python
:tags: pypy
:author: wdv4758h
:summary: from PyPy status blog

剛剛看到 `PyPy status blog 上的新文章 <http://morepypy.blogspot.tw/2014/11/pypy-io-improvements.html>`_ ，
以下是大概的內容

PyPy 在 Warsaw (為波蘭的首都及最大的城市) 的 sprint 順利結束了 (wrapped up)，
有些 branch (gc_no_cleanup_nursery, gc-incminimark-pinning) 已經順利 merge 回 master (improve I/O & GC)

改變一 - gc_no_cleanup_nursery
------------------------------

PyPy GC 會把 new objects allocate 在 young object area (就是 GC 上慣稱的 **nursery** 啦)，
每經過一個 minor collection 都要把 nursery 清理。簡單起見，GC 通常會把整個 nursery 清成 0。

這樣作法對於 cache 會有 bad effects，因為你一次把一大塊 memory 清成 0，
而且把一些不需要清成 0 的資料也清了 (例如 large strings)。對於這個問題，
可以用 incremental nursery zeroing 來減輕，
但是 gc_no_cleanup_nursery 這個 branch 把 zeroing 整個拿掉，
因此提升了 **string handling** 和 **recursive code** 的效率 (因為 jitframes 也不再需要把 memory 清成 0)

改變二 - gc-incminimark-pinning
-------------------------------

隨著時間的過去 PyPy GC 會把 objects 在 memory 裡做移動，也就是說 memory address 會改變，
因此要把 pointer 傳給 C function 時，必須確保指到 objects 不會被 GC 移動。

PyPy 2.4 以前，用 copying the data into or from a non-movable buffer 來解決，
顯然這沒有效率。這個 branch 使用了 "pinning" 的概念，
這讓程式可以知會 GC 某些 objects 在一段時間內不允許被移動。
這會讓 GC 的複雜度稍微上升，但是可以大幅提升 I/O performance。
