========================================
date
========================================


.. contents:: 目錄


範例
========================================

.. code-block:: sh

    $ date
    Sat May 19 00:50:28 CST 2018

    $ date "+%Y%m%dT%H%M%S"
    20180519T005058

    $ date -u "+%Y-%m-%dT%H:%M:%SZ"
    2018-05-18T16:51:48Z

    # display specific date
    $ date -d "@1473305798"
    Thu Sep  8 11:36:38 CST 2016

    # set date
    $ date -D '%Y-%m-%dT%H:%M:%SZ' '2018-05-18T16:53:17Z'


輸出其他地區的時間（coreutils 裡的 date 和 busybox 的 date 都支援）：

.. code-block:: sh

    # 時區資料
    # tz database，又稱為 IANA time zone database 和 Olson database
    # 由 David Olson 創立
    # 會放在 /usr/share/zoneinfo/
    $ sudo pacman -S tzdata

    # 使用 IANA time zone
    # 注意：如果輸入不存在的時區將會默認輸出 UTC，時區存在認定為 tzdata 的檔案
    $ echo 'Taiwan'; env TZ=Asia/Taipei date
    $ echo 'California'; env TZ=America/Los_Angeles date
    $ echo 'France'; env TZ=Europe/Paris date



參考
========================================

* `Wikipedia - tz database <https://en.wikipedia.org/wiki/Tz_database>`_
* `How can I have "date" output the time from a different timezone? - Unix & Linux Stack Exchange <https://unix.stackexchange.com/questions/48101/how-can-i-have-date-output-the-time-from-a-different-timezone>`_
