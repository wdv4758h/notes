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



HarfBuzz 1.4 Brings OpenType GX / Font Variations
========================================================

:URL: https://www.phoronix.com/scan.php?page=news_item&px=HarfBuzz-1.4-Released

HarfBuzz 新版加入了 OpenType 1.8 Font Variations 支援，
Font Variations 可以用來描述字的各種變化，
藉此可以不用設計多份字型塞進字型檔裡，
而是使用描述變化的方式來製造不同變化，
如此一來可以大幅減少字型檔的大小。

相關連結：

* `OpenType Font Variations - Gea-Suan Lin <https://blog.gslin.org/archives/2016/09/21/6857/opentype-font-variations/>`_
* `Introducing OpenType Variable Fonts <https://medium.com/@tiro/https-medium-com-tiro-introducing-opentype-variable-fonts-12ba6cd2369>`_
* [Video] `TYPO Talks » Videos » OpenType GX: Bringing font variations to OpenType <http://www.typotalks.com/videos/opentype-gx-bringing-font-variations-to-opentype/>`_



Irssi 1.0.0 Released
========================================================

:URL: https://irssi.org/2017/01/05/irssi-1.0.0-released/

irssi 釋出了 1.0.0 版，
之前用了那麼久沒注意版本，
原來現在才 1.0 版，
不過說穿了版本號也只是數字而已。



GNOME's SVG Rendering Library Migrating To Rust
========================================================

:URL: https://www.phoronix.com/scan.php?page=news_item&px=librsvg-2.41-Rust

GNOME 的 Librsvg 正式轉成 Rust codebase 了，
在利用 Rust 提供的各項功能下（Memory Safety、抽象化等等），
外包一層 C API 以確保原本使用 Librsvg 的其他程式依然可以正常運作。

* `Librsvg 2.41.0 is released <https://mail.gnome.org/archives/desktop-devel-list/2017-January/msg00001.html>`_



Google 再次改善 Android 的 APK 更新，讓下載的量更小
===================================================

:URL: https://blog.gslin.org/archives/2016/12/11/7021/google-再次改善-android-的-apk-更新，讓下載的量更小/

其實就是對檔案做 bsdiff 後再壓縮，
Client 端再用 bspatch 打上去，
相關的技術在 Chromium 上很久以前就用過了。

相關連結：

* `Chromium - Software Updates: Courgette <https://www.chromium.org/developers/design-documents/software-updates-courgette>`_



創造AlphaGo的台灣「土博士」，他們眼中的黃士傑
=============================================

:URL: https://theinitium.com/article/20170116-taiwan-AlphaGo/

講述黃士傑在進入 DeepMind 之前的經歷，
大多是在臺師大讀博士班的時期。



Why RethinkDB failed ?
============================================

:URL: https://github.com/coffeemug/defstartup/blob/master/_drafts/why-rethinkdb-failed.md

講述 RethinkDB 的一群工程師當初是如何決定這個開源產品的走向，
以及後來在產品銷售上碰到的困境，
包含使用者對於這開源產品不願意付錢，
還有大家都跑去使用他們當時覺得設計不良的 MongoDB，
在產品失敗後檢討當初出錯的環節。

最後作者給了三個建議：

* 選一個較大的市場，並為特別的使用者打造產品
* 學習如何辨別出你缺少的才能，並竭盡所能把相關人才招攬到團隊
* 多閱讀 The Economist

相關連結：

* `The Rise of Worse is Better <https://dreamsongs.com/RiseOfWorseIsBetter.html>`_
