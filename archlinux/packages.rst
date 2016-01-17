========================================
Packages
========================================

Install .deb
========================================

* `debtap - A script for converting .deb packages into Arch Linux packages, focused on accuracy <https://github.com/helixarch/debtap>`_

.. code-block:: sh

    $ debtap -u     # create/update pkgfile and debtap database
    $ debtap XXX.deb
    $ ls -l XXX.pkg.tar.xz
    $ pacman -U XXX.pkg.tar.xz


pkgfile
========================================

Installation
------------------------------

.. code-block:: sh

    $ sudo pacman -S pkgfile
    $ sudo pkgfile --update

Usage
------------------------------

.. code-block:: sh

    $ pkgfile -l tree   # 列出 package 的內容 (不限定安裝過的 packages)
    extra/tree	/usr/
    extra/tree	/usr/bin/
    extra/tree	/usr/bin/tree
    extra/tree	/usr/share/
    extra/tree	/usr/share/man/
    extra/tree	/usr/share/man/man1/
    extra/tree	/usr/share/man/man1/tree.1.gz

    $ pkgfile -s tree   # 列出含有這個檔案的 packages
    extra/tree
    community/gtkdialog
    community/openmotif

    $ pkgfile -s tree -b    # 列出含有這個檔案的 packages (只限在 binary folder 裡)
    extra/tree


command not found hook
------------------------------

.. code-block:: sh

    # Bash
    $ source /usr/share/doc/pkgfile/command-not-found.bash

    # Zsh
    $ source /usr/share/doc/pkgfile/command-not-found.zsh

    # Fish
    # Included since version 2.2



    $ sl
    sl may be found in the following packages:
      community/sl 5.02-4	/usr/bin/sl
