=========
``pfctl``
=========
* 在 ``<table>`` 裡增加 ``<IP>`` ::

    pfctl -t <table> -T add <IP>

* 從 ``<table>`` 中刪除 ``<IP>`` ::

    pfctl -t <table> -T delete <IP>

* 測試 ``<IP>`` 是否在 ``<table>`` 中 ::

    pfctl -t <table> -T test <IP>

* 重新載入設定檔 ::

    pfctl -f /etc/pf.conf
