========================================
Arch Install Scripts
========================================

.. code-block:: sh

    $ git clone git://projects.archlinux.org/arch-install-scripts.git
    $ cd arch-install-scripts
    $ make
      GEN      arch-chroot
      GEN      genfstab
      GEN      pacstrap
    $ tree
    .
    ├── arch-chroot
    ├── arch-chroot.in
    ├── common
    ├── COPYING
    ├── genfstab
    ├── genfstab.in
    ├── Makefile
    ├── pacstrap
    ├── pacstrap.in
    ├── README.md
    ├── test
    │   ├── common
    │   ├── test_mangle
    │   ├── test_option_twiddling
    │   └── test_valid_number_of_base
    └── zsh-completion

* `Arch Packages - arch-install-scripts <https://www.archlinux.org/packages/extra/any/arch-install-scripts/>`_
