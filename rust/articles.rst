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
