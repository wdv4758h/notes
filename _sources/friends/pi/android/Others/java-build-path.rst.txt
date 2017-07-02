20140914
========

今天把舊電腦裡面的 eclipse project 移到新電腦上，出現一些錯誤，像是 java.lang.Object cannot be resolved 之類的

或是 org.json cannot be resolved

總之就是一些路徑沒弄好，Library 找不到

1.  加入 Java 的 lib
    對著 project 點右鍵 > Properties > Java Build Path
    Add Library > JRE System Library
    就可以加入 Java 的 lib，對於 java.lang 相關的錯誤應該可以解決

2.  加入 Android 的 lib
    對著 project 點右鍵 > Properties > Java Build Path
    Add External JARs:
    C:\Users\<Username>\android-sdks\platforms\android-20
    這樣會加入 Android 4.4 的 lib

eclipse project 移到新電腦時，可能是因為 user name 不同了，導致 android 的 lib 找不到，在 Java Build Path 裡面也會多出一個 Unable to find System Library 之類的東西

目前是用上面的方式處理，未來可能要想辦法把 android.jar 也一起移出來，或是直接包進 workspace
