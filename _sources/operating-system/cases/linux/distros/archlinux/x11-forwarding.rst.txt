========================================
X11 Forwarding
========================================


.. contents:: 目錄


安裝
========================================

.. code-block:: sh

    sudo pacman -S xorg-xauth xorg-xhost



設定
========================================

Server （ ``/etc/ssh/sshd_config`` ）：

* ``AllowTcpForwarding yes``
* ``X11UseLocalhost yes``
* ``X11DisplayOffset 10``
* ``X11Forwarding yes``


更改設定後記得重開 daemon ：

.. code-block:: sh

    sudo systemctl restart sshd



Client
========================================

使用 ``-X`` 參數：

.. code-block:: sh

    ssh -X myuser@myhost

或是在 Client 的設定檔中把 ``ForwardX11`` 設為 ``yes`` ：

::

    Host myhost
        HostName myhost
        Port 22
        User myuser
        ForwardX11 yes



如果碰到錯誤或顯示問題的話可以嘗試把 ``ForwardX11Trusted`` 設為 ``yes`` ，
或是使用 ``-Y`` 參數。
注意安全問題，
如此一來遠端的 Client 會取得完整的 X11 Display 存取權限：

.. code-block:: sh

    ssh -Y myuser@myhost

::

    Host myhost
        HostName myhost
        Port 22
        User myuser
        ForwardX11Trusted yes



參考
========================================

* `Arch Wiki - Secure Shell #X11_forwarding <https://wiki.archlinux.org/index.php/Secure_Shell#X11_forwarding>`_
