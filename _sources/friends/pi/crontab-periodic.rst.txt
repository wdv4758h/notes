==================
Crontab & Periodic
==================

Crontab
-------

cron daemon 可以週期性的執行一些指令，不需要人工去執行

``/etc/crontab`` 格式 ::

  #minute>hour>---mday>---month>--wday>---who>----command
  14>-----3>------*>------*>------*>------root>---portsnap cron

上面的範例會使 cron 在每天凌晨 03:14 時執行 ``portsnap cron`` 這個指令

要注意的是，由 cron 所執行的指令不在 interactive shell 裡面，有些指令例如 ``portsnap fetch`` 會拒絕執行

Periodic
--------

periodic 機制依賴 crontab，在 crontab 中有三行 ::

  #minute>hour>---mday>---month>--wday>---who>----command
  1>------3>------*>------*>------*>------root>---periodic daily
  15>-----4>------*>------*>------6>------root>---periodic weekly
  30>-----5>------1>------*>------*>------root>---periodic monthly

分別是

* daily - 在每日 03:01 執行 ``/etc/periodic/daily/`` 裡的 script
* weekly - 在每週六 04:15 執行 ``/etc/periodic/weekly/`` 裡的 script
* monthly - 在每月一日 05:30 執行 ``/etc/periodic/monthly/`` 裡的 script

``/etc/periodic/`` 內的 script 檔名為 ``999.local`` 格式，前面的數字是順序

若不想要自己寫 crontab，可以把 script 放進去，並記得在 ``/etc/defaults/periodic.conf`` 裡面 enable
