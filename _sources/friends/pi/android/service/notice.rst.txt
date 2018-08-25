* 若在 TabActivity 中的 Activity 想要啟動 Service，請使用 ``getApplicationContext().startService();`` 而不是 ``startService()`` ，否則在 TabActivity 關閉時，Service 的 ``onDestroy()`` 不會被呼叫
* ``startService()`` 或 ``bindService()`` 會在 Main Thread 上執行，也就是 ``onCreate()`` 結束後，若中途被 Block 住，可能導致 Dead Lock
* ``bindService(_, _, Context.BIND_AUTO_CREATE)`` 並不會觸發 ``onStartCommand()`` ， ``startService()`` 才會
