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
