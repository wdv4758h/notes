example
-------
::

    # search aur
    $ yaourt -Ss neovim

    aur/neovim-git 0.1.0.r0.gc4826c3-1 (173)
    Fork of Vim aiming to improve user experience, plugins, and GUIs.
    aur/neovim-gnome-terminal-wrapper 2-1 (0)
    A wrapper for running neovim in a separate instance of gnome-terminal
    ...

    # url: https://aur.archlinux.org/packages/neovim-git/
    # PKGBUILD preview: https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=neovim-git

    # download 
    $ yaourt -G aur/neovim-git

    ==> Download neovim-git sources
    x .SRCINFO
    x .gitignore
    x PKGBUILD
    x neovim-git.install

    # build
    $ cd neovim-git/
    $ makepkg
    # makepkg -s for dependencies?

    # install
    $ pacman -U <package>

More to read
------------
- archwiki: AUR
- archwiki: PKGBUILD
- archwiki: makepkg
