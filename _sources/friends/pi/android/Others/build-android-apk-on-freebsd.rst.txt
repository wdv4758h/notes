============================
Build Android APK on FreeBSD
============================

本文說明如何在 FreeBSD Server 上編譯 Android APK

若原本使用 Eclipse 編譯，請先用 Eclipse 的工具把專案 Export 成 Gradle 專案

* 有些專案會依賴別的專案，例如 ``appcompat_v7`` ，請全都 Export

主要工具
--------

* Android SDK

  - 用來編譯 Android APK

* Gradle

  - Gradle 是一個類似 ``make`` 的工具，用來自動化編譯的各個過程

工具間的依賴鏈
--------------

* Gradle

  - Android SDK

    + Java
    + Bash
    + GCC
    + Linux Compatible Layer

步驟
----

1.  安裝 Android SDK ::

    $ cd
    $ fetch http://dl.google.com/android/android-sdk_r24.0.2-linux.tgz
    $ tar xvf android-sdk_r24.0.2-linux.tgz
    $ rm android-sdk_r24.0.2-linux.tgz
    $ cd android-sdk-linux/tools/
    $ ./android list sdk --no-ui

  - 按照自己的需求安裝需要的 SDK ::
  
      $ ./android update sdk --filter 1,2,5,6,7,8,9,10,11,15,16,17,56,57,59 --no-ui

    + 有些 SDK 和 Android 版本無關，筆者安裝的有

      * Android SDK Platform-tools
      * Android SDK Build-tools
      * Android Support Repository
      * Android Support Library
      * Google Play services

2.  安裝 Java ::

    # pkg install openjdk-7.71.14_1,1

3.  安裝 ``gcc`` ::

    # pkg install gcc-4.8.4

  - 安裝 ``gcc`` 是為了它提供的 Library ``libstdc++.so.6``

4.  安裝 ``bash`` ::

    # pkg install bash
    # ln -s /usr/local/bin/bash /bin/bash

  - 第二步非常重要，因為 Gradle 編譯的腳本是用 Bash 寫的，要是不做這個 link 就會出錯

5.  安裝 Linux Compatible Layer ::

    # pkg install linux_base-c6-6.6_1
    # kldload linux

  - 在 ``/etc/fstab`` 加好需要的設定 ::

      fdesc  /dev/fd  fdescfs  rw  0  0
      proc   /proc    procfs   rw  0  0

  - 設定 Compatible Layer 的 Kernel 版本 ::

      # echo compat.linux.osrelease=2.6.18 >> /etc/sysctl.conf
      # service sysctl restart

    + 根據測試， ``2.6.16`` 會讓 Gradle（或是 Android SDK）出錯而編譯失敗

6.  整理 workspace ::

    $ cd
    $ mkdir workspace
    $ cd workspace/

  - 放置全域的檔案

    + ``settings.gradle`` ::

        include ':CICBrick2OpenMTC'
        ...

      * 把所有專案列出

    + ``build.gradle`` ::

        // Top-level build file where you can add configuration options common to all sub-projects/modules.
        buildscript {
          repositories {
            mavenCentral()
          }
          dependencies {
            classpath 'com.android.tools.build:gradle:1.0.0'
          }
        }

  - 把專案們放進 ``workspace/``

  - 在專案中的 ``build.gradle`` 中加上設定，讓 Lint 不要阻止編譯 ::

      lintOptions {
        abortOnError false
      }

7.  設定 Java 以及 Android SDK 的環境變數 ::

    $ export JAVA_HOME=/usr/local/openjdk7
    $ export ANDROID_HOME=~/android-sdk-linux

  - 實際路徑依實際情況決定

8.  編譯 ::

    $ cd CICBrick2OpenMTC
    $ ./gradlew
    $ ./gradlew tasks
    $ ./gradlew build

  - 編譯出來的 APK 會在 ``專案/build/output/apk/`` 內

