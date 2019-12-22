========================================
Packages
========================================


.. contents:: 目錄


Pkg 基本使用
========================================

.. code-block:: julia

    # https://docs.julialang.org/en/v1.0/stdlib/Pkg/
    # 進入 Julia Pkg REPL
    $ julia
    julia>
    julia> ]      # "]" 是從 Julia REPL 進入 Pkg REPL 的按鈕，用 Ctrl+C 離開
    (v1.0) pkg>

    # 安裝 BinaryBuilder
    (v1.0) pkg> add BinaryBuilder@v0.1.2
    (v1.0) pkg> add BinaryBuilder#master

    # 移除 BinaryBuilder
    (v1.0) pkg> rm BinaryBuilder

    # 測試 BinaryBuilder
    (v1.0) pkg> test BinaryBuilder


.. code-block:: julia

    # 製作 Package
    $ julia
    julia> ]
    (v1.0) pkg> generate HelloWorld
    Generating project HelloWorld:
        HelloWorld/Project.toml
        HelloWorld/src/HelloWorld.jl

    # 使用 Package
    $ cd HelloWorld
    $ julia
    julia> ]
    (v1.0) pkg> activate .
    julia> import HelloWorld
    julia> HelloWorld.greet()
    Hello World!



BinaryBuilder
========================================

.. code-block:: julia

    julia> using BinaryBuilder
    # 互動式選擇
    # 後面會提供 shell 來自己下指令編譯
    # 編完後把東西裝到指定資料夾
    # 之後在產生的 binary 中選擇要用的檔案
    # 整個做完後會生出 build_tarballs.jl 和整個專案設定
    julia> BinaryBuilder.run_wizard()



參考
========================================

* `BinaryBuilder.jl <https://github.com/JuliaPackaging/BinaryBuilder.jl>`_
