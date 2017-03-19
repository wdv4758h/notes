========================================
Sway
========================================


.. contents:: 目錄


編譯、安裝
========================================

Sway 已經可以在 Arch Linux 的套件系統內找到，
直接安裝：

.. code-block:: sh

    $ sudo pacman -S sway


從原始碼編譯：

.. code-block:: sh

    $ git clone https://github.com/SirCmpwn/sway
    $ cd sway
    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_SYSCONFDIR=/etc ..
    $ make
    $ sudo make install
    $ sudo setcap cap_sys_ptrace=eip /usr/local/bin/sway



模擬 Awesome WM 的操作
========================================

目前官方有模擬 Awesome WM 行為的
`設定檔 <https://github.com/SirCmpwn/sway/blob/master/contrib/awesome.config>`_ ，
可以基於這之上再自己做修改。



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
