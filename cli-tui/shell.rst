========================================
Shell
========================================


.. contents:: 目錄


Thompson shell - first Unix shell - 1971
========================================

:Wikipedia: https://en.wikipedia.org/wiki/Thompson_shell



Bourne Shell - 1977
========================================

Bell Labs 當初釋出的實做



csh - 1978
========================================



tcsh - 1983
========================================



ksh (Korn Shell)
========================================



pdksh (Public Domain Korn Shell)
========================================



mksh
========================================



ash (Almquist shell)
========================================

* FreeBSD ``sh`` 是基於 ``ash`` (Almquist shell) 再去改的
* BusyBox 裡面也是基於 ``ash``
    - `BusyBox - shell <https://git.busybox.net/busybox/tree/shell/>`_



Bash (Bourne-again shell) - GNU Project
========================================

:Site: https://www.gnu.org/software/bash/
:Repo: https://git.savannah.gnu.org/cgit/bash.git
:Extend Framework: https://github.com/Bash-it/bash-it



dash
========================================

:Site: http://gondor.apana.org.au/~herbert/dash/
:Repo: https://git.kernel.org/pub/scm/utils/dash/dash.git/



zsh
========================================

:Site: https://www.zsh.org/
:Repo: https://sourceforge.net/p/zsh/code/ci/master/tree/
:Repo-GitHub: https://github.com/zsh-users/zsh/
:Repo-GitLab: https://sourceforge.net/p/zsh/code/ci/master/tree/
:Extend Framework: https://github.com/robbyrussell/oh-my-zsh



fish - friendly interactive shell
========================================

:Site: http://fishshell.com/
:Repo: https://github.com/fish-shell/fish-shell
:Extend Framework: https://github.com/oh-my-fish/oh-my-fish


fish 3.0
------------------------------

* 支援 ``&&`` ``||`` ``!`` 以便從相容 POSIX 規範的 shell 遷移過來
* ``math`` 不再是 ``bc`` 的包裝

* `[GitHub] fish 3.0 <https://github.com/fish-shell/fish-shell/releases/tag/3.0.0>`_
* `[HN] fish 3.0 <https://news.ycombinator.com/item?id=18776765>`_



xonsh - cross-platform, Unix-gazing shell in Python
===================================================

:Site: http://xon.sh/
:Repo: https://github.com/xonsh/xonsh


Shell Language 是 Python 3.4+ 的 superset，
藉由 prompt-toolkit 撰寫互動界面，
使用 pip 安裝後即可使用。



Oil - bash-compatible shell in Python
========================================

:Site: https://www.oilshell.org/
:Repo: https://github.com/oilshell/oil


Oil 使用自己 fork 出去的 CPython 2.7，
會搭配自己的修改後包在最後釋出的執行檔裡。



Elvish - friendly interactive shell in Go
=========================================

:Site: https://elv.sh/
:Repo: https://github.com/elves/elvish



Ion - RedoxOS shell in Rust
========================================

:Repo: https://gitlab.redox-os.org/redox-os/ion



工具
========================================

* `ShellCheck - static analysis tool for shell scripts <https://github.com/koalaman/shellcheck>`_



增加 Shell Script 品質的技巧
========================================

* 函式命名使用 ``::`` 作為 namespace 的方式（只是函式名稱剛好有這字串）
