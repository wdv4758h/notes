=======
``cut``
=======
* 以 ``,`` 分隔，截取第二個 field ::

    echo c1,c2,c3 | cut -d ',' -f 2

  - 若取到不需要的空格字元，可以再之後用 ``tr`` 取代掉
  - 若分隔字元是空格也可以考慮用 ``awk``

* 截取部份字串 ::

    $ echo abcdefghijklmnopqrstuvwxyz | cut -c 2-10
    bcdefghij
