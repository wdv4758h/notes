========================================
字型相關處理 (Font)
========================================


.. contents:: 目錄


font-kit - cross platform font loading
========================================

:Repo: https://github.com/pcwalton/font-kit


font-kit 主要功能是在系統上尋找特定字型，
並且製作 rasterize glyph。
font-kit 底下會利用系統的 library 來處理，
但是包裝好各平台的功能，
提供一致的界面來操作。


Backends:

* Loader (讀取 TTF、OTF 等等)
    - Core Text (macOS)
    - DirectWrite (Windows)
    - FreeType (cross platform)
* Source (字型資料庫)
    - Core Text (macOS)
    - DirectWrite (Windows)
    - Fontconfig (cross platform) - Unix 類平台常見的字型搜尋工具
    - Filesystem (cross platform) - 在硬碟特定路徑尋找字型
    - Memory (cross platform) - 直接使用已經在記憶體中的字型
    - 多個 Sources 同時使用


Loader 和 Source 可以混合使用，
例如用 DirectWrite 找到的字型透過 FreeType 繪製。



Pathfinder
========================================

:Repo: https://github.com/pcwalton/pathfinder


> A fast, practical GPU rasterizer for fonts and vector graphics


目前大部分的主流字型繪圖 (Font Rendering) 都是靠 CPU，
而 Pathfinder 想要做的是把這塊用 GPU 加速並整合到既有生態圈內，
目標是成為最快的二維 SVG 和字型 rasterizer。
然而 CPU 字型繪圖目前還會持續存在，
因為有些特別的 glyph (例如 PNG emoji) 並不適合使用 GPU 來處理。
有趣的是，VR 應用圈也對於 Pathfinder 所能提供的改善有興趣，
因為既有的引擎所產生出的品質在 VR 應用下效果並不好。


Pathfinder 目前還沒有跟 font-kit 整合，
但是預計未來會成為其中一個可選的後端。


功能：

* GPU SVG rendering
    - WebRender 先前是用 Skia 的 CPU rasterize 來處理，但是 Pathfinder 3 有 GPU 可以用


版本演進：

* Pathfinder
* Pathfinder 2
* Pathfinder 3



未來可能的整合方向
========================================

整合以下工具組成新的 UI library：

* `WebRender - GPU renderer for the Web content <https://github.com/servo/webrender>`_
* `Pathfinder - GPU renderer for fonts and SVG <https://github.com/pcwalton/pathfinder>`_
* `Stretch - Flexbox implementation <https://github.com/vislyhq/stretch>`_



參考
========================================

* `An introduction to glyphs, as used and defined in the FreeType engine <http://chanae.walon.org/pub/ttf/ttf_glyphs.htm>`_
* `Wikipedia - Font Rasterization <https://en.wikipedia.org/wiki/Font_rasterization>`_
* `Wikipedia - Fontconfig <https://en.wikipedia.org/wiki/Fontconfig>`_
* [2016] `Inside the fastest font renderer in the world – Raph Levien – Medium <https://medium.com/@raphlinus/inside-the-fastest-font-renderer-in-the-world-75ae5270c445>`_

* [2019] `The sad state of font rendering on Linux | Infosec scribbles <https://pandasauce.org/post/linux-fonts/>`_
* [2012] `State of Text Rendering <http://behdad.org/text/>`_
* `FreeType <https://www.freetype.org/>`_
* `Cairo <https://www.cairographics.org>`_
* `Skia Graphics Library <https://skia.org/>`_
    - `Google/Skia <https://github.com/google/skia>`_
