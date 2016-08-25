========================================
文章閱讀（Articles）
========================================

.. contents:: 目錄


Lossless compression with Brotli in Rust for a bit of Pied Piper on the backend
===============================================================================

:來源: Dropbox
:作者: Daniel Horn and Mehant
:URL: https://blogs.dropbox.com/tech/2016/06/lossless-compression-with-brotli/

Dropbox 希望他們的壓縮、解壓縮演算法可以有三個性質：

1. 安全
2. 可預期
3. 快速

先前 Dropbox 使用的是 C 語言實作的 Brotli 壓縮，
只達到第三個條件「快」，
於是 Dropbox 選用 Rust 這個注重記憶體安全性的語言來實作 Brotli，
再搭配上 Linux kernel 內的 SECCOMP 功能來增加安全性。
剛實作完的 Rust 版 Brotli 只達到原本 C 版本效能的七成多，
在經過些許調整後已經達到原本效能的八成。

（背景知識填補）
`Zopfli <https://github.com/google/zopfli>`_ 是一個壓縮 Library，
目標是高壓縮率（所以壓縮時間可能會比較久），
支援了 DEFLATE、gzip、zlib，
在官方的說明裡就寫著「perform very good, but slow, deflate or zlib compression」。
`Brotli <https://github.com/google/brotli>`_ 也是壓縮 Library，
使用的是和 gzip 以及 Zopfli 一樣的 LZ77 壓縮演算法，
跟 Zopfli 比起來有更多 trade off，
可以有更好的壓縮品質又有更快的壓縮速率。


目前（2016）Zopfli 有以下優勢：

* Zopfli 被視為目前壓縮率最有效的 DEFLATE，被認為是目前 DEFLATE 演算法的工藝水平
* `ZopfliPNG <https://github.com/google/zopfli/blob/master/README.zopflipng>`_ 利用 Zopfli 來壓縮 PNG，被視為目前壓縮效果最好的 PNG optimizer。


相關資源：

* [2015] `Introducing Brotli: a new compression algorithm for the internet <https://google-opensource.blogspot.tw/2015/09/introducing-brotli-new-compression.html>`_
* `Quora - What is Brotli? How is it different from Zopfli? <https://www.quora.com/What-is-Brotli-How-is-it-different-from-Zopfli/answer/Cody-Ray-Hoeft>`_
* `Comparison of Brotli, Deflate, Zopfli, LZMA, LZHAM and Bzip2 Compression Algorithms <https://www.gstatic.com/b/brotlidocs/brotli-2015-09-22.pdf>`_
