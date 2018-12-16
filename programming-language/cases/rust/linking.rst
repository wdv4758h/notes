========================================
Linking
========================================


.. contents:: 目錄


Cargo Linkage
========================================

Cargo Linkage 支援多種類型，
主要是 library 種類吧，有兩個向度，
第一個是靜態連結或動態連結，
第二個是 system library 或 Rust library，
system library 就是平常 C/C++ 會生出的那種，
Rust library 是會帶更多 Rust 資訊。
這樣就四種，加一種叫編譯器幫自己選 library 格式，
然後再加執行檔和擴充編譯器的 procedural macros，總共變成七種。


* bin:        我要做執行檔
* lib:        我要做 Rust library，格式編譯器幫我選
* staticlib:  靜態連結 system library (e.g. libfoo.a)
* cdylib:     動態連結 system library (e.g. libfoo.so)
* dylib:      動態連結 Rust library (e.g. libfoo.so)
* rlib:       靜態連結 Rust library
* proc-macro: 擴充編譯器的 procedural macros
