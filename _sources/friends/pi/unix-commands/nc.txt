======
``nc``
======
* listen ::

    $ nc -l <port>

* send ::

    $ nc <ip> <port>

* 嘗試連線, 但不送出資料 ::

    $ nc -zv <ip> <port>

* 範例: ``nc`` as TCP proxy

  - From wiki: netcat ::

      #!/usr/bin/sh
      if [ -p "backpipe" ]; then
        echo "backpipe exists."
      else
        mkfifo backpipe
      fi

      if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then
        echo "Usage: $0 port host port"
        exit
      fi

      while [ 1 ]; do
        echo "listening on port $1 and redirect to $2:$3"
        nc -l $1 0<backpipe | nc $2 $3 1>backpipe
        echo "one connection ends, start another."
      done

* 有些機器需要加上 ``-N`` option 才能正常結束連線

  - 有些 FreeBSD 10 需要
  - Mac OS X 沒有這個 option
