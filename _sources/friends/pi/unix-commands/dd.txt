======
``dd``
======
* 低階檔案輸出寫入工具

* 指定輸出到 ``<target>`` ::

    $ echo test | dd of=<target>

  - ``TARGET`` 可以是檔案或是硬碟的 device file

* 指定從 ``<target>`` 輸入 ::

    $ dd if=<target>

* 刷新硬碟上的 bit（治療可復原的 bit error） ::

    $ dd if=/dev/da0 of=/dev/da0

* 把硬碟資料透過網路傳送 ::

    $ dd if=/dev/da0 | nc <server-ip> <port>
