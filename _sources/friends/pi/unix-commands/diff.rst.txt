========
``diff``
========
* 比較兩個目錄的差異, 另有參數可以只比較檔案列表 ::

    $ diff -r <dir1> <dir2>

* 對兩個檔案做 ``diff`` ，並將結果並排輸出，最大寬度設為 ``width`` ::

    $ diff -y -W <width> <file1> <file2>

  - ``sdiff`` 和 ``diff -y`` 效果相同

* 產生 patch 檔 ::

    $ diff -u file1 file2
