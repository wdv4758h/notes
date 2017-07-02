安裝 Eclipse
============

1.  下載 Eclipse 並解壓縮

    - https://www.eclipse.org/downloads/

      - 選擇 "Eclipse IDE for Java Developers"

    - Google 提供的 http://developer.android.com/sdk/index.html 解壓縮時有「路徑過長」的問題

2.  開啟 Eclipse

3.  Menu -> Help -> Install New Software

    - Work with: https://dl-ssl.google.com/android/eclipse

    - [v] Developer Tools

    - 安裝完畢後先把 Eclipse 關掉，等 SDK 裝好再開 (就算馬上重開也找不到 SDK)

4.  下載 Android SDK

    - http://developer.android.com/sdk/index.html

      - "GET THE SDK FOR AN EXISTING IDE"

5.  開啟 Android SDK Manager，安裝它預選的套件

6.  安裝 Android USB Driver

    - Google USB Driver

      1.  透過 Android SDK Manager 下載
      2.  用 USB 連接手機和電腦
      3.  右鍵點選 ``我的電腦`` -> ``管理`` -> ``裝置管理員``
      4.  發現 ``Android Device`` 上面會是黃色驚嘆號
      5.  對 ``Android Device`` 點選右鍵 -> ``更新驅動程式`` -> ``瀏覽電腦上的驅動程式軟體``
      6.  瀏覽的位置選擇 ``C:\Users\{username}\android-sdks\extras\google\usb_driver``
      7.  點選 ``讓我從電腦上的裝置驅動程式清單上挑選`` ，選擇 ``Android Device``
      8.  選擇 ``Android ADB Interface``
      9.  選擇 ``從磁片安裝``
      10. 選擇 ``C:\Users\{username}\android-sdks\extras\google\usb_driver\android_winusb.inf``

    - PdaNet
