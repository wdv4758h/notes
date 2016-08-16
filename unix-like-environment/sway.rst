========================================
Sway
========================================


.. contents:: 目錄


擴充
========================================

i3status
------------------------------

.. code-block:: sh

    sudo pacman -S i3status


設定 Window Manager 使用 i3staus（ ``~/.config/sway/config`` ）：

::

    bar {
        status_command i3status
    }


i3status 內容的設定在  ``~/.config/i3status/config`` ，
可以先去 ``/etc/i3status.conf`` 複製預設設定後做客製化。

* `i3status 支援的設定 <https://i3wm.org/i3status/manpage.html>`_



參考
========================================

* `Sway <http://swaywm.org/>`_
* `i3 WM <https://i3wm.org/>`_
* `Arch Wiki - Sway <https://wiki.archlinux.org/index.php/Sway>`_
* `Arch Wiki - Wayland <https://wiki.archlinux.org/index.php/wayland>`_
