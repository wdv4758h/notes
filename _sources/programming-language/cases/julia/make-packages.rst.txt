========================================
製作 Packages
========================================


.. contents:: 目錄


PkgDev
========================================

安裝：

.. code-block:: julia

    julia> Pkg.add("PkgDev")


使用：

.. code-block:: julia

    julia> import PkgDev
    julia> PkgDev.generate("MyProj", "BSD")   # 會在 ~/.julia/v0.6/MyProj


結果：


.. code-block:: sh


    $ cd ~/.julia/v0.6/MyProj/
    $ tree
    .
    ├── appveyor.yml
    ├── LICENSE.md
    ├── README.md
    ├── REQUIRE
    ├── src
    │   └── MyProj.jl
    └── test
        └── runtests.jl

    2 directories, 6 files



參考
========================================

* `Julia - Packages <http://docs.julialang.org/en/latest/manual/packages.html>`_
