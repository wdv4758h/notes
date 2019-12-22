========================================
圖片處理 (Image Manipulation)
========================================


.. contents:: 目錄


imageflow
========================================

:Site: https://www.imageflow.io/
:Repo: https://github.com/imazen/imageflow
:FAQ: https://www.kickstarter.com/projects/njones/imageflow-respect-the-pixels-a-secure-alt-to-image/faqs


imageflow 是一套處理圖片大小、格式等等操作的 library，
提供 HTTP API server、嵌入程式或是 CLI 的方式操作，

imageflow 跟 ImageMagick 相比，
ImageMagick 比較偏平日桌面應用，
imageflow 比較偏 server 上使用。
imageflow 所提供的功能較少，
但是更適於使用在輸入圖像不可信的情況，
提供更快更安全的方案。



Image - encoding and decoding images
========================================

:Repo: https://github.com/image-rs/image


由 Piston 社群開發的圖像 encode/decode library，
目標是要提供純 Rust 的實做，
後來從 Piston 專案轉移到 image-rs 組織底下。


* `Transitioning to Image-rs <https://blog.piston.rs/2019/04/15/transitioning-to-image-rs/>`_



圖片優化
========================================

Oxipng - lossless PNG optimizer
-------------------------------

:Repo: https://github.com/shssoichiro/oxipng

目標是要提供快速地無損 PNG 壓縮優化，
重寫自原本的 OptiPNG 專案。


* `[2018] PNG tools overview (benchmark) <https://css-ig.net/png-tools-overview>`_


svgcleaner - lossless SVG optimizer
------------------------------------

:Repo: https://github.com/RazrFalcon/svgcleaner
