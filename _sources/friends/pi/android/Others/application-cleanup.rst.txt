Android App Activity 的生命週期有許多步驟，每個步驟對應到 Java Code 的 ``on-...`` 事件

生命週期如下

* ``onCreate()``

  - Activity 被產生後的事件
  - 下一步： ``onStart()``

* ``onRestart()``

  - Activity 被停止後，重開時的事件
  - 下一步： ``onStart()``

* ``onStart()``

  - Activity 開始可見
  - 下一步： ``onStop()`` 或是 ``onResume()``

* ``onResume()``

  - Activity 開始和 User 互動前的事件
  - 下一步：Activity 運作

* Activity 運作中

  - 下一步： ``onPause()``

* ``onPause()``

  - 別的 Activity 要 Resume 時的事件
  - 下一步： ``onStop()`` 或是 ``onResume()`` 或是 **直接結束**

* ``onStop()``

  - Activity 被停止時的事件
  - 下一步： ``onRestart()`` 或是 ``onDestroy()`` 或是 **直接結束**

* ``onDestroy()``

  - Activity 結束時的事件

因為種種原因（記憶體不足、使用者強制關閉等等）， ``onStop()`` 和 ``onDestroy()`` 步驟不保證會被執行

App 結束時的收尾動作應在 ``onPause()`` 實作，但不應有太多步驟，避免 Android 被卡住

``isFinishing()`` 可檢查 Activity 是否即將進入 ``onDestroy()``

（手機直接爆炸是例外狀況，每個步驟都可能中斷）

ref: http://stackoverflow.com/questions/8515936/android-activity-life-cycle-what-are-all-these-methods-for
