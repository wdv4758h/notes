=====
Ports
=====


FreeBSD Ports
--------------


簡介
``````
FreeBSD 的 Ports 系統維護一個 Ports Tree，位置在 ``/usr/ports/`` ，每個軟體各自佔一個目錄，裡面存放該軟體的安裝資訊

FreeBSD 的 Ports 設定檔在 ``/etc/portsnap.conf``


Ports Tree
````````````
* 第一次下載 port tree（ ``/usr/ports`` 不存在） ::

    # portsnap fetch extract update

* 指定主機 ::

    # portsnap -s portsnap.freebsd.org fetch extract

* 更新 port tree ::

    # portsnap fetch update

  - 若希望 port tree 定期自動更新，請使用 ``portsnap cron`` ，才可以在非 interactive shell 執行


使用 Make 指令
````````````````
* 搜尋某個 Ports ::

    $ make search name="{name}"
    $ make quicksearch key="{keyword}"

  - 可以列出 Build Dependency、Run Dependency 以及簡介和網頁


Portmaster
````````````
* 務必檢查 ``/usr/ports/UPDATING`` 裡面的資訊

* 更新一個或多個 ports ::

    # portmaster -Bdw editors/vim lang/python

* 直接更新所有已安裝的 ports ::

    # portmaster -Bdwa --no-confirm

  - ``-B``: 不要備份舊的 ports
  - ``-d``: 不要保留 dist file
  - ``-w``: 保留舊的 Share Library
  - ``-a``: 全部更新
  - ``--no-confirm``: 不要問

* 重新編譯某 port，並重新編譯所有 Depend 到該 port 的 ports ::

    # portmaster -r python3-3_2

* 刪除一個 port ::

    # portmaster -e <portname>


pkg
`````
* 檢查已安裝的 ports 中有沒有新版本 ::

    $ pkg version -vl '<'

* 列出所有已安裝的 ports ::

    $ pkg info

  - 列出某 ports 相關的檔案 ::

      $ pkg info -l <package-name>

* 搜尋 ports ::

    $ pkg search -o <package-name>

* Dependency

  - 列出 ``vim`` 的 dependency ports ::

      $ pkg info -d vim

  - 列出 depend on ``python`` 的 ports ::

      $ pkg info -r python

  - 用一個 port 取代另一個 port ::

      $ pkg set -o lang/perl5.12:lang/perl5.14
      $ pkg install -Rf lang/perl5.14

* 安裝新的 ports ::

    # pkg install <package-name>

* 直接更新所有已安裝的 ports ::

    # pkg upgrade

* 刪除沒有用的 ports (沒有被用到) ::

    # pkg autoremove

* 刪除 distfiles ::

    # pkg clean


MacPorts
---------
* 參數格式 ::

    port <action> <option>

  - ``action`` 可以是安裝、刪除、更新等動作
  - ``option`` 可以是某特定的 ports，也可以是一群 ports 的集合如 ``installed``, ``requested``, ``leave`` 等等

* 刪除沒被 reference 到的 ports ::

    # port uninstall leaves

  - 需要手動重覆執行，因為每清理一次就會有別的 port 變成 leaf
  - 建議在更新前先清理乾淨，避免卡在一些其實沒有用到的軟體

* 更新 port tree ::

    # port selfupdate

* 列出已安裝的 ports ::

    $ port echo installed
    $ port echo requested

* 更新 ports ::

    # port upgrade outdated

* 搜尋 ::

    $ port search <package-name>

* 安裝 ::

    # port install <package-name>

* 確認安裝的檔案 ::

    $ port contents <package-name>

* 調整參數

  - 查詢可用參數 ::

      $ port variants vim

  - 安裝時增加參數 ::

      # port install vim +python34

    + 多種 variant 可以同時安裝在系統中，但一次只會有一個為 active


其他
-----
FreeBSD ports ``git`` 若不希望 depend on Python2.7，可以把 ``CONTRIB`` 選項取消

有關 Python 的預設版本設定請見 ``python/freebsd-python-default-version.rst``
