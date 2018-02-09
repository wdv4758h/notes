========================================
GLib
========================================


.. contents:: 目錄


介紹
========================================

在 C 語言之上建立物件系統，
並支援 asynchronous 和 event driven，
也提供很多資料結構的實做。


架構：

* GObject
* GIO
* GModule
* GThread
* GLib


使用 GLib 的常見專案：

* GTK+
* GStreamer
* GIMP



除錯
========================================

開啟更多訊息：

.. code-block:: sh

    env G_MESSAGES_DEBUG=all ./my_application_with_glib



注意事項
========================================

一些環境變數(例如 ``LANG``) 很重要，
可能會影響運作行為。



參考
========================================

* `Running GLib Applications <https://developer.gnome.org/glib/stable/glib-running.html>`_
