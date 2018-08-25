* 編譯時發生 ``Conversion to Dalvik format failed with error 1`` 與 ``Dx bad class file magic (cafebabe) or version (0033.0000)``

  - 可能是外部的 ``.jar`` 檔與目前的環境使用不同的 Java 版本

* 避免在 ``.jar`` 裡面包 ``.jar``

  - 案例：

    + 專案 A 引入了 ``outer.jar``
    + ``outer.jar`` 裡面包含 ``inner.jar``
    + ``outer.jar`` 的 public function ``cls1.foo()`` 有呼叫 ``inner.jar`` 提供的 public function ``cls2.bar()``
    + 專案 A 有呼叫 ``cls1.foo()`` ，除此之外沒有直接呼叫任何 ``inner.jar`` 的功能
    + 結果

      * 編譯成功
      * 執行期間發生 ``java.lang.NoClassDefFoundError: inner.cls2``

    + 解法：

      * ``inner.jar`` 在輸出時只公開自己的 source code 以及 class file，其他使用到的所有 external jar 都隱藏
      * ``outer.jar`` 在輸出時只公開自己的 source code 以及 class file，其他使用到的所有 external jar 都隱藏
      * 專案 A 引入 ``outer.jar`` 以及 ``inner.jar``
      * 實際上 ``inner.jar`` 應該是佔了兩份空間，但其中一份被藏在 ``outer.jar`` 中，外部無法存取
      * ``outer.jar`` 所呼叫到的 ``cls2.bar()`` 應是被專案 A 另外引入的，而不是本身包含的
