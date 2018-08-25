========================================
Rust & Graphic
========================================


.. contents:: 目錄


底層架構介紹 - gfx
========================================

專案目標
------------------------------

`gfx-rs <https://gfx-rs.github.io/>`_
的目標是要提供高效能、易用、健全的圖形 API。


抽象層 - gfx-hal
------------------------------

:repo: https://github.com/gfx-rs/gfx
:site: https://gfx-rs.github.io/

``gfx-hal`` TL;DR:

* 單一的 API，多樣的後端
* 單一的 Shader 語言 SPIR-V，根據後端自動轉換
* 支援 Compute Shaders


在不同平台中，
圖形架構有不同的 API，
例如 OpenGL、Metal、DirectX、Vulkan。
``gfx-hal`` 是 gfx 社群在 2017 年提出來的抽象層，
API 設計借鏡 Vulkan 的經驗，
提供跟 Vulkan 相似的 API，
藉由一致的 API 來快速地支援多種平台。
（與此同時也移除了本來的 ``gfx-core`` ，
並把舊的 gfx API 放到 ``gfx-render`` 以便大家轉移）


支援的後端：

* Vulkan
* DirectX 12/11
* Metal
* OpenGL 2.1+
* OpenGL ES2+
* WebGL


::

    +----------------------------------------------------------+
    |             HAL (Hardware Abstraction Layer)             |
    +--------+------------+-------+--------+-----------+-------+
    |        | DirectX 12 |       |        |           |       |
    | Vulkan |            | Metal | OpenGL | OpenGL ES | WebGL |
    |        | DirectX 11 |       |        |           |       |
    +--------+------------+-------+--------+-----------+-------+


Shader 語言方面提供單一的 SPIR-V 來撰寫，
會根據不同的後端自動轉換成適用的形式。


Vulkan Portability Initiative 實做 - gfx-portability
----------------------------------------------------

:repo: https://github.com/gfx-rs/portability

``gfx-portability`` 是基於 gfx 的 Vulkan Portability Initiative 實做，
藉此可以讓「非 Rust 的專案」使用這 API 跑在各種不同的平台上，
（Rust 專案可以直接使用 gfx 本身的 API）。


::

    +-------------------------------+
    | Vulkan based Application      |
    +-------------------------------+
                  |
                  v
    +-------------------------------+
    | Vulkan Portability Initiative |
    +-------------------------------+
                  |
                  v
    +-------------------------------+
    | gfx-portability               |
    +-------------------------------+
         |         |       |       |
         v         v       v       v
    +----------+-------+--------+-----+
    | DirectX  | Metal | OpenGL | ... |
    +----------+-------+--------+-----+


在 `Portability benchmark of Dota2 on MacOS <https://gfx-rs.github.io/2018/08/10/dota2-macos-performance.html>`_
這篇文章中，
作者把 ``gfx-portability`` 跟 ``MoltenVK`` 做比較，
用的是 Valve 釋出的 Dota2 on Vulkan，
在測試中 gfx 測了兩種 Metal 後端，
分別是 Immediate mode 和 Deferred mode，
兩種模式都表現出足以跟 MoltenVK 競爭的效能，
而 Deferred mode 還稍微超越當下的 MoltenVK 版本。


兩種 Metal 後端：

* Immediate
    - command 會直接被送到 Metal command buffers
* Deferred
    - command 會被內部的 buffer 先存起來，在最後送出時才放到 Metal command buffers
    - MoltenVK 採用這種方式


Shader
------------------------------

Shader parameters (或稱為 uniforms) 為使用者提供的繪製執行的數值，
例如：

* material properties
* textures
* screen size
* MVP matrix


為了減少程式設計師跟底層圖形 API 直接溝通而容易產生錯誤的問題，
通常會有一些 shader 界面來減少出錯的可能。

現有的一些 shader 界面：

* UDK
* Unity3D
* Irrlight
* Ogre3D
* Horde3D
* Three.js
* gfx-rs

大部分的 shader 界面實做都把參數名稱設計為字串，
這造成不必要的效能損失，
而且也容易發生打錯字的狀況而難以發現。

``gfx-rs`` 把參數設計成型別，
用一般 Rust 結構的宣告方式使用，
利用 Rust macro 產生相關需要的程式碼，
藉此可以除去不必要地字串比對及呼叫效能損失，
也可以讓編譯器事先檢查相關錯誤。


PSO (Pipeline State Objects)
------------------------------


Programming Model
------------------------------



OpenGL
========================================

Rust 有一個叫做 `Glium <https://github.com/tomaka/glium>`_ 的 OpenGL API 包裝，
藉此可以方便地在 Rust 中操作，
比起自己直接呼叫 OpenGL 方便許多，
也避免很多問題。



Vulkan
========================================

:site: https://vulkano.rs/

Rust 有一個叫做 `Vulkano <https://github.com/vulkano-rs/vulkano>`_ 的 Vulkan API 包裝，
藉此可以操控相關行為和處理 GLSL 或 SPIR-V。




從 Rust 程式碼轉成 GLSL/SPIR-V
========================================

也就是說類似 GLSL 擴充 C 語言一樣，
藉由擴充 Rust 來直接用 Rust 的語法和工具撰寫 GPU 的 Shader 程式碼。
目前這塊並沒有很大量的成果，
但是有一些相關專案在嘗試，
例如 `inspirv-rust <https://github.com/msiglreith/inspirv-rust>`_
就嘗試透過 attribute 提供資訊的方式讓部份 Rust 編譯器的 MIR 直接轉成 SPIR-V。



參考
========================================

Repos
------------------------------

* `Glium - safe OpenGL wrapper <https://github.com/tomaka/glium>`_
* `Glutin - pure Rust alternative to GLFW <https://github.com/tomaka/glutin>`_
* `Vulkano - safe and rich Rust wrapper around the Vulkan API <https://github.com/tomaka/vulkano>`_
* `inspirv-rust <https://github.com/msiglreith/inspirv-rust>`_
* `winit - cross-platform window creation and management in Rust <https://github.com/tomaka/winit>`_


圖形相關專案
------------------------------

* `MoltenVK - Vulkan based on Metal <https://github.com/KhronosGroup/MoltenVK>`_
* Vulkan Portability Initiative
* `Vulkan CTS - Vulkan 實做檢查、測試 <https://github.com/KhronosGroup/VK-GL-CTS/blob/master/external/vulkancts/README.md>`_
