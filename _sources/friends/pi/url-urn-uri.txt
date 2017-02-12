===============
URL / URN / URI
===============
* URL = Uniform Resource Locator

  - URL 代表一個某資源的位置

  - 例如 ``http://www.wikipedia.org/`` 代表某個網路資源

* URN = Uniform Resource Name

  - URN 代表某個資源的名稱

  - 例如 ``urn:isbn:0-486-27557-4`` 代表某特定書籍的特定版本

* URI = Uniform Resource Identifier

  - URI 代表某一個資源，可以用位置表達 (URL)，也可以用名稱表達 (URN)

  - URL 是一種 URI，URN 也是一種 URI


URL
----
* HTTP URL 格式 ::

    <scheme>://<domain>:<port>/<path>?<query_string>#<fragment_id>


URN
----
* URN 格式 ::

    urn:<nid>:<nss>

  - ``<nid>`` 為命名空間的標籤，每個命名空間有自己的 ``<nss>`` 解析方式

    + 例如 ``urn:isbn:0-486-27557-4`` ，後面的 ``<nss>`` 使用 ``isbn`` 方式解讀
