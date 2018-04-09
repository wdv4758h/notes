========================================
Pacman
========================================


.. contents:: 目錄


常見使用
========================================

尋找特定檔案在哪個套件：

.. code-block:: sh

    pkgfile -s rg


安裝套件：

.. code-block:: sh

    sudo pacman -S ripgrep


強制安裝套件、不要詢問同意：

.. code-block:: sh

    sudo pacman -S ripgrep --force --confirm


移除相關使用說明：

.. code-block:: sh

    $ pacman -R --help
    usage:  pacman {-R --remove} [options] <package(s)>
    options:
      -b, --dbpath <path>  set an alternate database location
      -c, --cascade        remove packages and all packages that depend on them
      -d, --nodeps         skip dependency version checks (-dd to skip all checks)
      -n, --nosave         remove configuration files
      -p, --print          print the targets instead of performing the operation
      -r, --root <path>    set an alternate installation root
      -s, --recursive      remove unnecessary dependencies
                           (-ss includes explicitly installed dependencies)
      -u, --unneeded       remove unneeded packages
      -v, --verbose        be verbose
          --arch <arch>    set an alternate architecture
          --assume-installed <package=version>
                           add a virtual package to satisfy dependencies
          --cachedir <dir> set an alternate package cache location
          --color <when>   colorize the output
          --config <path>  set an alternate configuration file
          --confirm        always ask for confirmation
          --dbonly         only modify database entries, not package files
          --debug          display debug messages
          --gpgdir <path>  set an alternate home directory for GnuPG
          --hookdir <dir>  set an alternate hook location
          --logfile <path> set an alternate log file
          --noconfirm      do not ask for any confirmation
          --noprogressbar  do not show a progress bar when downloading files
          --noscriptlet    do not execute the install scriptlet if one exists
          --print-format <string>
                           specify how the targets should be printed


移除套件：

.. code-block:: sh

    sudo pacman -R mypackage


強制移除套件：

.. code-block:: sh

    sudo pacman -Rdd mypackage


遞迴地移除套件和相依：

.. code-block:: sh

    sudo pacman -Rcussn ocaml


列出已安裝套件：

.. code-block:: sh

    pacman -Q


列出已安裝套件所裝入的檔案：

.. code-block:: sh

    pacman -Ql ripgrep


檢查套件、尋找遺失的檔案：

.. code-block:: sh

    pacman -Qk


列出不在官方套件列表的已安裝套件：

.. code-block:: sh

    pacman -Qem



pacgraph
========================================

.. code-block:: sh

    sudo pacman -S pacgraph
    pacgraph
    # see pacgraph.svg and pacgraph.png
    pacgraph --console | head
    # http://kmkeen.com/pacgraph/



Yaourt
========================================

``/etc/yaourtrc`` :

    EXPORT=2    # save to pacman cache



參考
========================================

* `Pacnew and Pacsave <https://wiki.archlinux.org/index.php/Pacman/Pacnew_and_Pacsave>`_
    - 有一些套件好像不會產生？ e.g. fish
* `Arch Wiki - PKGBUILD <https://wiki.archlinux.org/index.php/PKGBUILD>`_
* `Yet another Yogurt - An AUR Helper written in Go <https://github.com/Jguer/yay>`_
* `pacapt - Arch pacman-like package manager for some Unices <https://github.com/icy/pacapt/>`_
    - ``pacman``-like wrapper for other package manager
* `An AUR helper that minimizes user interaction <https://github.com/rmarquis/pacaur>`_
