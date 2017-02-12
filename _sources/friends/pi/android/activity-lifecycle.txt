===============================
Lifecycle of Android Activities
===============================
Android Activity 的生命週期有許多步驟，每個步驟都有對應的函式

這些函式都是在 Main Thread 上執行，使得它們不可能重疊發生

若在這些函式中觸發了別的事件，該事件會在當下的函式結束後才觸發，例如 ``finish()`` 函式其實並不會立刻使 Activity 結束，開啟服務亦同，使用時需注意不要產生 Deadlock

列表
-----
* ``public void onCreate (Bundle savedInstanceState);``

  - Activity 做一般初始化，如產生 views，把資料 binding 到 List 上等等
  - 在這個函式呼叫 ``finish()`` 會導致 ``onDestroy()`` 被呼叫
  - Next: ``onStart()``

* ``public void onRestart ();``

  - 在 Activity ``onStop()`` 後又再度被放回前景時觸發的事件
  - Next: ``onStart()``

* ``public void onStart ();``

  - Activity 開始可見
  - Next: ``onResume()``

* ``public void onResume ();``

  - Activity 開始和 User 互動
  - Next: ``onPause()``

* ``public void onPause ();``

  - Activity 被放到背景
  - 可用 ``isFinishing()`` 檢查 Activity 是否確定要關閉
  - 需在第一行呼叫 ``super.onPause()``
  - Next: ``onStop()``

* ``public void onStop ()``

  - Activity 不再可見
  - **可能不會被呼叫**
  - Next: ``onDestroy()``

* ``public void onDestroy ()``

  - Activity 被清除前觸發的事件
  - **可能不會被呼叫**

* ``public void onBackPressed ()``

  - 使用者按下 Back 鍵時觸發的事件

* ``public boolean onKeyDown (int keyCode, KeyEvent event)``

  - ``return false`` 代表不處理

* ``public boolean onKeyLongPress (int keyCode, KeyEvent event)``

  - ``return false`` 代表不處理
