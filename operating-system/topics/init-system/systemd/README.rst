========================================
systemd
========================================


.. contents:: 目錄


指令
========================================

* Portable Services: ``portablectl``
     - `Portable Services with systemd v239 <http://0pointer.net/blog/walkthrough-for-portable-services.html>`_
* interact with D-Bus object system: ``busctl``
* DNS settings: ``resolvectl``
* ``systemd-nspawn``
* ``coredumpctl``
* ``hostnamectl``
* ``journalctl``
* ``systemd-analyze``
* ``networkctl``



業界使用
========================================

Facebook
------------------------------

* `pystemd <https://github.com/facebookincubator/pystemd>`_
    - Cython-based wrapper on top of libsystemd, focused on exposing the dbus API via sd-bus
* systemdmon
    - daemon for feeding systemd metrics to external monitoring systems



範例
========================================

簡單 service，會自動重開
------------------------------

.. code-block:: systemd

      [Unit]
      Description=example daemon

      [Service]
      Type=simple
      WorkingDirectory=/tmp
      ExecStart=/usr/bin/ls
      Restart=always

      [Install]
      WantedBy=multi-user.target


.. code-block:: sh

      sudo systemctl daemon-reload
      sudo systemctl start    example.service   # 手動啟動
      sudo systemctl stop     example.service   # 手動關閉
      sudo systemctl enable   example.service   # 開機自動啟動
      sudo systemctl disable  example.service   # 取消開機自動啟動
      sudo systemctl daemon-reload && systemctl enable example.service && systemctl start example.service

      systemctl show example.service               # 列出 service 所有設定
      systemctl show example.service -p NRestarts  # 列出 service 特定設定

      journalctl -u example.service    # 看 service log


在 sandbox 裡執行
------------------------------



參考
========================================

* `Wikipedia - systemd <https://en.wikipedia.org/wiki/Systemd>`_
* `systemd - System and Service Manager <https://www.freedesktop.org/wiki/Software/systemd/>`_
* `ArchWiki - systemd <https://wiki.archlinux.org/index.php/Systemd>`_
* `The new sd-bus API of systemd <http://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html>`_
* `Blog - Pid Eins <http://0pointer.net/blog/>`_
* [GitHub] `systemd <https://github.com/systemd>`_
