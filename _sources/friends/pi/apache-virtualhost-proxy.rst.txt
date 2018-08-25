=====================================================
使用 Apache 的 Virtualhost & Proxy 處理 Django 的網站
=====================================================

情境
----

* Host 有兩個 Domain Name: ``pi314.nctucs.net``, ``nctuhl.nctucs.net``
* Host 上執行 Apache
* 另一個 Django 的網站在 Jails 裡面

  - 內部的 port 是 8000
  - 外部的 port 是 61000
  - 可以用 ``http://pi314.nctucs.net:61000`` 取得 Django 的網站

目標
----

* 連往 ``http://pi314.nctucs.net`` 時出現 Apache 的網站
* 連往 ``http://nctuhl.nctucs.net`` 時出現 Django 的網站

解法
----

httpd.conf ::

  LoadModule proxy_module libexec/apache24/mod_proxy.so
  LoadModule proxy_http_module libexec/apache24/mod_proxy_http.so

  <VirtualHost *:80>
      ServerName nctuhl.nctucs.net
      ProxyPass / http://pi314.nctucs.net:61000/
      ProxyPassReverse / http://pi314.nctucs.net:61000/
  </VirtualHost>
  
  <VirtualHost *:80>
      ServerName pi314.nctucs.net
      DocumentRoot /usr/local/www/apache24/data
  </VirtualHost>

註
----

* 經過測試，若 ``ProxyPass`` 尾端的 ``/`` 忘記加，會造成 ``DNS lookup failure``

* ``pf`` 會造成影響，由於 jails 放在 ``lo0`` 的內網上，可能要把 ``set skip lo0`` 關掉，並做 ``rdr``

