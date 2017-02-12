==========
``mktemp``
==========
根據 PID 產生暫存檔，並在 script 結束（包含不正常結束）時刪除它

.. code:: sh

  tempfile=$(mktemp /tmp/tempfile-$$)
  trap "rm -f $tempfile >/dev/null 2>&1" EXIT
  trap "exit 2" SIGINT SIGQUIT SIGTERM

  ...

  rm ${tempfile}

第一個 ``trap`` 負責在 sciprt 結束時把暫存檔刪除

第二個 ``trap`` 負責截取 SIGINT、SIGQUIT、SIGTERM，並將 script 關閉

實際測試，若不分成兩個 ``trap`` ， ``rm`` 會在 script 被 kill 時出現 ``No such file or directory`` 訊息，無論加了 ``-f`` 參數或是加上 ``2>/dev/null`` 都無法去除，猜測是 race condition
