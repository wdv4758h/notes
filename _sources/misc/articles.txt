========================================
文章
========================================


.. contents:: 目錄


How we brought HTTPS Everywhere to the cloud
============================================

:來源: CloudFlare
:作者: Ingvar Stepanyan
:URL: https://blog.cloudflare.com/how-we-brought-https-everywhere-to-the-cloud-part-1/

目標是要自動把 ``http://`` 改成 ``https://`` ，
要達到這件事有兩個假設需要成立

1. 所有 HTTP 的子資源都可以經由 HTTPS 取得
2. 取得方式必須是同 Domain 且同路徑

HTTPS Everywhere 利用人力確認哪些網站適用這種自動轉換，
而 CloudFlare 則把這個清單拿來使用在 CDN 上。



Token Capture via an LLVM-based Analysis Pass
=============================================

:作者: Axel Souchet
:URL: https://doar-e.github.io/blog/2016/11/27/clang-and-passes/

稍微簡單介紹 LLVM 的架構和常見的使用領域，
接著介紹 AFL Fuzzing 工具，
以及如何結合 LLVM 做分析。


相關連結：

* https://github.com/0vercl0k/stuffz/blob/master/llvm-funz/afl-llvm-tokencap-pass.so.cc



Short Film: Find my Phone
=============================================

:URL: https://blog.gslin.org/archives/2016/12/25/7046/在手機裡面放木馬後故意讓手機被偷走的紀錄片/

在手機裡面放木馬後，故意讓手機被偷走的紀錄片



djb 的密碼學陰謀論
=============================================

:URL: https://blog.gslin.org/archives/2014/10/29/5228/djb-的密碼學陰謀論/

講述政府不希望有真正安全的密碼系統，
以及已經發生過在演算法裡面藏後門的事件。
科幻作家 Charles Stross 也因為先前作品中所描述的事件已經被 NSA 真實地上演，
而取消了本來在規劃中的續集。

相關連結：

* http://www.antipope.org/charlie/blog-static/2013/12/psa-why-there-wont-be-a-third-.html#more



比 Google 地圖更偉大，七萬多幅百年地圖數位版收藏免費下載
========================================================

:URL: http://www.playpcesor.com/2016/11/David-Rumsey-map-collection.html

「David Rumsey Map Collection 」號稱是世界上最大的古代地圖收藏庫，
由美國私人地圖收藏家 David Rumsey 創立，
存有 16 世紀到 21 世紀的地圖資料，
全部高解析度的數位版地圖都免費授權非商業使用，
也支援和現在的 Google 地圖進行數位疊圖。

相關連結：

* `Google 文化藝術中心與歷史博物館，數位典藏跨界策展 <http://www.playpcesor.com/2013/08/google.html>`_
