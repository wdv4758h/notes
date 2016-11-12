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



ripgrep is faster than {grep, ag, git grep, ucg, pt, sift}
==========================================================

:作者: Andrew Gallant
:URL: http://blog.burntsushi.net/ripgrep/
:HackerNews: https://news.ycombinator.com/item?id=12564442

稍微介紹 Regex Engine 的差異、ripgrep 有哪些特色、有哪些地方可以加速字串的尋找，
最後做一些效能測試



Incremental Compilation
==========================================================

:作者: Michael Woerister
:URL: https://blog.rust-lang.org/2016/09/08/incremental.html
:HackerNews: https://news.ycombinator.com/item?id=12457942

介紹 Rust 編譯器正在開發的 Incremental Compilation 功能



Pretty State Machine Patterns in Rust
========================================

:作者: Andrew Hobden
:URL: https://hoverbear.org/2016/10/12/rust-state-machine-pattern/



Thoughts on DX: GNOME and Rust
========================================

:作者: Alberto Ruiz
:URL: https://siliconislandblog.wordpress.com/2016/10/31/thoughts-on-dx-gnome-and-rust/

相關 repo：

* `GNOME/librsvg - branch rustification <https://github.com/GNOME/librsvg/tree/rustification/rust>`_


後續相關發展：

* `Rust and GNOME meeting notes <https://internals.rust-lang.org/t/rust-and-gnome-meeting-notes/4339>`_
* `Rust and GObject <https://blogs.gnome.org/despinosa/2016/11/01/rust-and-gobject/>`_
* `Rust and Vala <https://blogs.gnome.org/despinosa/2016/11/01/rust-and-vala/>`_



Fixing Python Performance with Rust
========================================

:作者: Armin Ronacher
:URL: https://blog.sentry.io/2016/10/19/fixing-python-performance-with-rust.html



Refactoring std for ultimate portability - libs - Rust Internals
================================================================

:作者: Brian Anderson
:URL: https://internals.rust-lang.org/t/refactoring-std-for-ultimate-portability/4301



2016 Rust Commercial User Survey Results
========================================

:作者: Jonathan Turner
:URL: https://internals.rust-lang.org/t/2016-rust-commercial-user-survey-results/4317



Paradigms of Rust for the Go developer
========================================

:作者: Ralph Caraveo
:URL: https://medium.com/@deckarep/paradigms-of-rust-for-the-go-developer-210f67cd6a29

講解在 Go 發生的 data race 問題，
而在 Rust 中會怎樣被編譯器避免，
最後建立出沒有 data race 的程式碼。
