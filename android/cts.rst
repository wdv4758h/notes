========================================
Android CTS (Compatibility Test Suite)
========================================

CDD
========================================

CDD 全名是 Compatibility Definition Document，
就是 Android 的相容性相關的定義，
照這份定義實作的系統可以確保跟不同 device 上的相容，
讓上面的程式可以正常運作。



CTS
========================================

CTS 全名是 Compatibility Test Suite，
顧名思義是在做軟體的相容性測試 (裡面包含大量的 test case)，
Google 要求所有跑 Android 系統得 device 都要通過 CTS 測試，
目的是確保 Android 生態系的品質，
包含實作品質、完程度、使用者體驗等，
所以供應商在依照 CDD 實作後，
執行 CTS 做測試，
通過後即可確保符合規範。
通過測試的硬體理論上能夠執行 Google Play Store 上的所有程式，
讓開發者做出來的 Application 可以跑在所有 Android 系統上。
通過 CTS 測試的硬體可以把結果送到 cts@android.com，
最後會被加到一個 list 上做紀錄，
原則上通過 CTS 的硬體才能正式上市。



授權
========================================

Google 的相關授權：

+--------+----------+--------------------+----------+-------------------+---------------------------------+
| 種類   | 通過 CTS | Android 商標使用權 | GMS 授權 | Google 商標使用權 | 結果                            |
+========+==========+====================+==========+===================+=================================+
| Type 1 | O        | O                  | X        | X                 | device 預設沒有任何 Google 服務 |
+--------+----------+--------------------+----------+-------------------+---------------------------------+
| Type 2 | O        | O                  | partial  | X                 | device 預設有部份 Google 服務   |
+--------+----------+--------------------+----------+-------------------+---------------------------------+
| Type 3 | O        | O                  | O        | O                 | device 預設有完整 Google 服務   |
+--------+----------+--------------------+----------+-------------------+---------------------------------+



GMS (Google Mobile Service)
========================================

Google 相關服務的套件，
包含 Google Play Store、Gmail、Google Map、... 等等



Reference
========================================

* `Android - Compatibility Test Suite <https://source.android.com/compatibility/cts/index.html>`_
* `Android - Compatibility Definition Document <http://source.android.com/compatibility/android-cdd.pdf>`_
