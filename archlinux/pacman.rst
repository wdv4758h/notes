========================================
Pacman
========================================

* check packages, find missing files

.. code-block:: sh

    pacman -Qk

----

* list explicitly installed packages not available in official repositories

.. code-block:: sh

    pacman -Qem

----

* remove all packages no longer required as dependencies (orphans):

.. code-block:: sh

    pacman -Qdt | awk '{print $1}' | xargs sudo pacman -R --noconfirm

----

* force remove specific packages

.. code-block:: sh

    pacman -Rdd mypackage

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
        --logfile <path> set an alternate log file
        --noconfirm      do not ask for any confirmation
        --noprogressbar  do not show a progress bar when downloading files
        --noscriptlet    do not execute the install scriptlet if one exists
        --print-format <string>
                        specify how the targets should be printed

----

* `pacapt - An Arch's pacman-like package manager for some Unices <https://github.com/icy/pacapt/>`_
    - ``pacman``-like wrapper for other package manager

----

* `Arch Wiki - PKGBUILD <https://wiki.archlinux.org/index.php/PKGBUILD>`)
