========================================
Hardware & Programming
========================================

* `What every programmer should know about memory <http://lwn.net/Articles/250967/>`_
* `Huge pages <https://lwn.net/Articles/374424/>`_

----

Scott Meyers 在 2014 年 NDC Conference 分享了 CPU 的重要性，
整場下來給予聽眾一個觀念「只要沒有充份利用 CPU Cache，效能就會有極大的損失。」。
當中並舉出微軟當初發現 Windows CE 在處理封包時，
和 Linux 比起來多出了非常多的 cache miss，
造成效能低落的實際案例。
最後則說明在撰寫 multithread 程式時，
可能在不注意下產生 False Sharing，
造成 CPU 需要不斷更新 cache，
導致效能再度低落 ..

(片長 1 小時，Scott Meyers 演講的很好，不會想睡覺 :D)

keyword: data cache, instruction cache, TLB, cache coherency, false sharing

* `Scott Meyers - CPU Caches and Why You care <https://vimeo.com/97337258>`_

    - Eliminate False Sharing
    - `Dr.Dobb's - Eliminate False Sharing <http://www.drdobbs.com/parallel/eliminate-false-sharing/217500206>`_

