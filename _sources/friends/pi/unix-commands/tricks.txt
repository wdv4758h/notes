==================
各種指令的組合用法
==================
* 印出一個檔案，但前 5 行不要印出來 ::

    $ cat <file> | awk '{ if(NR > 5) print $0;}'

  - 可以把 ``cat`` 改成用 ``nl`` 確認真的只有前 5 行沒有印出

* 把目錄 ``<dir>`` 從 Host A 丟到 Host B

  - Host A ::

      tar cvf - <dir> | nc -l <port>

  - Host B ::

      nc <host-A-ip> <port> > <arch-file>.tar
      nc <host-A-ip> <port> | tar xvf -

  - 如果 Host A 沒有 public IP 的話就改把 port 開在 Host B 上

* 查看系統安裝的記憶體

  - On Linux ::

      $ free -m
      $ free -h | awk 'NR==2{print $2}'
      $ echo $(free -og | grep Mem | tr -s 'Mem: ' '\n' | head -n 2) GB

  - On FreeBSD ::

      $ sysctl hw.physmem
      $ echo $(expr $(sysctl hw.physmem | tr -C -d 0-9) / 1073741824) GB

  - On Mac OS X ::

      $ hostinfo
      $ echo $(hostinfo | grep memory | tr -dC 0-9.) GB

* [``tcsh`` only] 把 ``rm`` ``alias`` 成 ``mv``, 不直接刪除檔案 ::

    $ alias rm 'mv \!* ~/.trash'

* 把任意一個被 suspend 的 process 叫到 forground ::

    $ %<number>

* 把漫畫檔名重新編為流水號

  - 假設檔案的修改時間是照實際順序的 ::

      $ ls -1tr | \
      nl -rz | \
      awk '{print "mv " $2 " " $1 ".jpg"; }' | \
      sh

  - 想法

    + 先用 ``ls -1tr`` 依序列出檔名
    + 用 ``nl`` 產生流水號， ``-rz`` 會把流水號補滿 ``0``
    + 用 ``awk`` 輸出 ``mv origin.jpg <n>.jpg`` 的 shell script
    + 丟給 ``sh`` 執行

* 可愛的小時鐘 ::

    $ while [ 1 ]; do clear; date '+%H:%M:%S' | figlet -m 4; sleep 1; done

* 檢查 ``git`` 指令是否存在 ::

    if command -v git 2>&1 >/dev/null; then
      ...
    fi

* ``cd`` 進上一個 ``mkdir`` 的目錄 ::

    $ mkdir <dir>
    $ cd !$

  - bash-like shell 限定 (``sh``, ``bash``, ``zsh``, ...)
