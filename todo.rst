========================================
Todo
========================================

* FreeBSD Ports - Neovim update
    - 目前 Ports 裡的 Neovim 版本有點舊了，需要更新、修正 dependencies
    - 用 FreeBSD poudriere build 過測試 (會跑在 Jails 裡)

* FreeBSD poudriere-like tool for Linux LXC/Docker
    - 利用 Linux 上的 container 技術做出類似 FreeBSD poudriere 這類在隔離環境裡測試編譯的工具

* Python 3.6 - f-string implementation detail study
    - `PEP 0498 -- Literal String Interpolation <https://www.python.org/dev/peps/pep-0498/>`_
    - `CPython/Lib/test/test_fstring.py <https://github.com/python/cpython/blob/master/Lib/test/test_fstring.py>`_

* Vim/Neovim Syntax Highlight for Literal String Interpolation
    - `f"test"`
    - `u"test"`
    - `r"test"`
    - `b"test"`
