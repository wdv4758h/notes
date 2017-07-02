============
``ifconfig``
============
* 把 ``em0`` interface 關掉 ::

    $ ifconfig em0 down

* 把 ``em0`` interface 打開 ::

    $ ifconfig em0 up

* 手動設定 IP 給 ``em0`` ::

    $ ifconfig em0 inet x.x.x.x netmask x.x.x.x
