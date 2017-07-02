===========
``openssl``
===========
* 產生 hash ::

    $ openssl passwd -crypt -salt 5W 123456

* 讓指令的執行過程被 ``openssl`` 包裝 ::

    $ openssl s_client <cmd>

* 傳輸檔案

  A)  接收端 ::

        $ nc -l 12345 | openssl enc -d -aes-256-cbc -nosalt | base64 -D | <data-sink>

  B)  發送端 ::

        $ <data-source> | base64 | openssl enc -e -aes-256-cbc -nosalt | nc localhost 12345
