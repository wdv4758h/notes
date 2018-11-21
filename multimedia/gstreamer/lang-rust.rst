========================================
GStreamer & Rust
========================================


.. contents:: 目錄


介紹
========================================

GStreamer 的 Rust binding 目前在
`gstreamer-rs <https://github.com/sdroege/gstreamer-rs>`_ 裡，
binding 是用 `GIR <https://github.com/gtk-rs/gir/>`_ 產生的。
GIR 是基於 GObject-Introspection API metadata 產生 Rust binding 的工具，
適用於任何基於 GLib 的專案，
藉此可以快速地產生品質好的 binding。

另外還有 `gst-plugin-rs <https://github.com/sdroege/gst-plugin-rs>`_
專門為使用 Rust 撰寫 GStreamer plugin 提供資源，
除了提供基礎架構外，
也有數個實做範例可以參考。
