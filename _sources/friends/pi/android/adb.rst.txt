====================
Android Debug Bridge
====================

* 安裝 APK 至手機 ::

    adb install -r SocketSample.apk

  - ``-r`` 為取代舊的 app

* 連接手機並啟動 Logcat ::

    adb logcat | grep com.example.socketsample -A 5

  - ``adb logcat`` 有 filter 可以用，但尚未研究
