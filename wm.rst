========================================
Window Manager
========================================

X Window
========================================

Xlib
------------------------------

XCB
------------------------------


Wayland
========================================

* `Arch Wiki - Wayland <https://wiki.archlinux.org/index.php/Wayland>`_


Projects
------------------------------

* `Waysome <https://github.com/waysome/waysome>`_
    - Waysome does not define any behaviour. It can be configured and scripted over an API, which allows the user to define the tiling, floating and overall behaviour.


Freedesktop
========================================

* `Extended Window Manager Hints <http://standards.freedesktop.org/wm-spec/wm-spec-latest.html>`_



簡單 WM 範例
========================================

* `tinywm <https://github.com/mackstann/tinywm>`_
* `rust-tinywm <https://github.com/acmiyaguchi/rust-tinywm>`_
* `tinywm-xcb.c <https://gist.github.com/penk/470486>`_
* `wtfwm <https://github.com/Kintaro/wtftw>`
* `A window manager in Rust - 01 <http://kintaro.github.io/rust/window-manager-in-rust-01/>`_
* `eyl-shell - A basic Weston desktop shell client <https://github.com/eyolfson/eyl-shell>`_


想要的狀況
========================================

自己想要的是想 Awesome WM 這樣的 Tilinig WM，
而且可 configure 的空間很大。


心中的理想狀況 (亂列)：

* 使用 Wayland
* 多元設定檔支援 (多語言)
    - 可以用 Python 寫 script
    - 可以用 Lua 寫 script
    - 可以用 Rust (編成 library，提供固定的 entry point，執行的 script 會去用它)
        + [可能] 提供好用的 macro
* Plugin
    - 可以用 Rust 編成 library
    - 可以用 Lua
    - 可以用 Python
* 多螢幕支援
* Awesome WM mode (所有 Awesome WM 的 feature)
* Dependency 儘量少 (多種支援，但是要不要用是 Optional，要用再去裝)
* 速度儘量快
    - 一些 Asynchronous 支援
    - Multi-cores
    - GPU
* 記憶體使用量儘量少
* [極端] 使用者可以藉由編譯的設定檔來選擇要編進去的 feature，沒用到的 feature 就不用編進去，產生一個 library 帶著走
* 可編成一個靜態連結的 standalone 版本
* HiDPI
* 預設有漂亮的外觀，提供多種 theme 的選擇
* 可在 local 只跑 client，遠端有 server 在計算，local 只負責畫圖

----

[TODO]

在不跑一整套原生環境的情況下，
讓 GTK、KDE 程式可以漂亮顯示的注意事項。
