========
``grep``
========
* 列出含有 ``test`` 的行 ::

    $ cat file | grep "test"

* 列出不含有 ``test`` 的行 ::

    $ cat <file> | grep -v "test"

* 在當前目錄遞迴的尋找所有檔案中的 ``test`` 字串 ::

    $ grep -R "test" .

* 只印出比對到的部份 ::

    $ grep -o "test"

* 印出比對到的前後行

  - 印出比對到的前一行 ::

      $ grep -A 1

  - 印出比對到的後一行 ::

      $ grep -B 1

  - 印出比對到的前後一行 ::

      $ grep -C 1

* ``egrep``

  - 等於 ``grep -E`` ，使用擴充的 regex ::

      $ ls | egrep "mp4|avi"
