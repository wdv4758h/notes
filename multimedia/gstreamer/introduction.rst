========================================
GStreamer 介紹
========================================


.. contents:: 目錄


設計原則
========================================

GStreamer 希望做到的是讓使用者在撰寫應用程式時，
可以輕易地做出複雜的多媒體處理，
而對於想要擴充的人也可以很容易地撰寫出自己的擴充。



實做
========================================

GStreamer 的物件架構是基於 GLib 2.0 的物件模型，
也就是 ``GObject`` ，
如果使用過 GLib 2.0 或 GTK+ 的人會覺得很熟悉。

在這之上，GStreamer 也利用了 GLib 的 signal 和 object property。

所有物件都可以在執行期間被取出，
支援使用 property 或 capability 來搜尋。

GStreamer 的 plugin 會在執行期間被讀入，
並且藉由 GObject 的屬性來溝通，
不需要額外的 header 檔，
廠商也可以提供自己的 binary 來優化。

GStreamer 核心的部份是 media-agnostic 的，
不依賴於任何多媒體格式，
只專心在處理 bytes 和 blocks，
並且只有非常基本的元件，
剩下都算在擴充元件當中。



效能方面
========================================

* 使用 GLib 的 GSlice allocator
* 元件間的連結非常輕量化，資料傳輸的成本也非常小，通常只是指標的存取
* 擁有直接使用特定記憶體的機制，例如直接使用音效卡內的硬體 buffer
* reference counting 和 copy on write 來撿少 memcpy 的使用
* 獨立的串流 thread，由 kernel 排程
* 支援硬體加速
* 元件只在真正要使用時才讀入
