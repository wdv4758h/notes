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

* `pacapt - An Arch's pacman-like package manager for some Unices <https://github.com/icy/pacapt/>`_
    - ``pacman``-like wrapper for other package manager
