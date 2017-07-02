========================================
Graphic
========================================


.. contents:: 目錄


OpenGL
========================================

Rust 有一個叫做 `Glium <https://github.com/tomaka/glium>`_ 的 OpenGL API 包裝，
藉此可以方便地在 Rust 中操作，
比起自己直接呼叫 OpenGL 方便許多，
也避免很多問題。



Vulkan
========================================

Rust 有一個叫做 `Vulkano <https://github.com/tomaka/vulkano>`_ 的 Vulkan API 包裝，
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

* `Glium <https://github.com/tomaka/glium>`_
* `Vulkano <https://github.com/tomaka/vulkano>`_
* `inspirv-rust <https://github.com/msiglreith/inspirv-rust>`_
