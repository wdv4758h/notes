===========
expect 筆記
===========
``expect`` 可以模擬使用者的行為，類似按鍵精靈的用途，和 Text-based 程式互動

::

  #!/usr/bin/expect -f
  set filename [lindex $argv 0];

  spawn scp $filename root@192.168.1.88:~/$filename
  expect "password:"
  send "arduino\r"
  interact
