========================================
GStreamer 編譯 (GStreamer Build)
========================================


.. contents:: 目錄


一般平台編譯
========================================

以前都要靠 Autotools，
現在有基於 Meson 的 `gst-build <https://github.com/GStreamer/gst-build>`_ ，
gst-build 可以控制要編譯哪些專案，
必要時也會自動抓其他相依 library 進來編譯，
跟以前的編譯流程比起來方便很多。



Cross Compile
========================================

Meson
------------------------------

現在 GStreamer 官方的專案都可以用 Meson 來編譯，
整合好的編譯設定在 `gst-build <https://gitlab.freedesktop.org/gstreamer/gst-build>`_ ，
通常用來在同架構下編譯，
但是如果要 Cross Compile 也可以利用 Meson 的設定達成，
但是一些不支援 Meson 的外部相依套件就要自己額外處理（部份外部專案有 GStreamer 開發者的 Meson port）。


.. code-block:: sh

    $ git clone https://gitlab.freedesktop.org/gstreamer/gst-build.git
    $ cd gst-build/
    # Meson 的 Cross Compile 設定，如果要編原生版可以不需要
    # 參考： https://gitlab.freedesktop.org/gstreamer/gst-build/blob/master/cross-files/android_arm64_api28.txt
    $ cat <<EOF > meson.ini
# 自己更換 "{XXX}" 的設定
[host_machine]
system = '{system}'
cpu_family = '{cpu_family}'
cpu = '{cpu}'
endian = '{endian}'

[properties]
{extra_properties}

[binaries]
c = {CC}
cpp = {CXX}
ar = {AR}
strip = {STRIP}
windres = {WINDRES}
pkgconfig = 'pkg-config'
{extra_binaries}
EOF
    # Meson 設定，可以根據自己需求調整，或者都不設定使用預設值
    $ env INSTALLDIR="/tmp/mybuild" MESONSETTING="meson.ini" ORIGIN="MYBUILD" \
        meson build . \
        --buildtype=release --prefix=$INSTALLDIR --cross-file=$MESONSETTING \
        -Dpython=enabled \
        -Dlibav=enabled \
        -Dugly=disabled \
        -Dbad=enabled \
        -Ddevtools=disabled \
        -Dges=disabled \
        -Drtsp_server=disabled \
        -Domx=disabled \
        -Dvaapi=disabled \
        -Dsharp=disabled \
        -Dexamples=disabled \
        -Dgtk_doc=disabled \
        -Dintrospection=disabled \
        -Dnls=disabled \
        -Dlibnice:gupnp=disabled \
        -Dlibnice:gstreamer=enabled \
        -Dlibnice:examples=disabled \
        -Dlibnice:tests=disabled \
        -Dlibnice:gtk_doc=disabled \
        -Dlibnice:introspection=disabled \
        -Dglib:iconv=gnu \
        -Dglib:gtk_doc=false \
        -Dgstreamer:package-origin=$ORIGIN \
        -Dgstreamer:gtk_doc=disabled \
        -Dgstreamer:tools=enabled \
        -Dgstreamer:examples=disabled \
        -Dgstreamer:tests=disabled \
        -Dgstreamer:benchmarks=disabled \
        -Dgstreamer:gst_debug=true \
        -Dgstreamer:gst_parse=true \
        -Dgstreamer:introspection=disabled \
        -Dgst-plugins-base:package-origin=$ORIGIN \
        -Dgst-plugins-base:gtk_doc=disabled \
        -Dgst-plugins-base:examples=disabled \
        -Dgst-plugins-base:tests=disabled \
        -Dgst-plugins-base:introspection=disabled \
        -Dgst-plugins-base:gl_api=gles2 \
        -Dgst-plugins-base:gl_platform=egl \
        -Dgst-plugins-base:gl_winsys=android \
        -Dgst-plugins-base:gl-jpeg=disabled \
        -Dgst-plugins-base:gl-png=disabled \
        -Dgst-plugins-base:alsa=disabled \
        -Dgst-plugins-base:x11=disabled \
        -Dgst-plugins-good:package-origin=$ORIGIN \
        -Dgst-plugins-good:examples=disabled \
        -Dgst-plugins-good:tests=disabled \
        -Dgst-plugins-good:v4l2-probe=false \
        -Dgst-plugins-good:v4l2=disabled \
        -Dgst-plugins-good:pulse=disabled \
        -Dgst-plugins-good:cairo=disabled \
        -Dgst-plugins-good:png=disabled \
        -Dgst-plugins-bad:package-origin=$ORIGIN \
        -Dgst-plugins-bad:androidmedia=enabled \
        -Dgst-plugins-bad:webrtcdsp=disabled \
        -Dgst-plugins-bad:gl=disabled \
        -Dgst-plugins-bad:examples=disabled \
        -Dgst-plugins-bad:tests=disabled \
        -Dgst-plugins-bad:wayland=disabled \
        -Dgst-plugins-bad:vulkan=disabled \
        -Dgst-plugins-bad:librfb=disabled \
        -Dgst-plugins-bad:kms=disabled \
        -Dgst-plugins-bad:dash=disabled \
        -Dgst-plugins-bad:smoothstreaming=disabled \
        -Dwebrtc-audio-processing:gnustl=disabled \
        -Dgst-libav:package-origin=$ORIGIN \
        -Dgst-python:pygi-overrides-dir=$INSTALLDIR/lib/python3.7/site-packages/gi/overrides \
        -Dpygobject:pycairo=false
    # 編譯
    $ ninja -C build/ -v
    # 安裝
    $ ninja -C build/ install



Cerbero
------------------------------

Cerbero 是 GStreamer 針對各平台編譯的整套系統，
除了 GStreamer 自身的專案以外，
還整合了眾多相關依賴套件的編譯，
這套編譯系統被 GStreamer 用於發佈新版的 SDK，
已經為各平台設定好許多適合的調整。

不同平台的環境建立可以看
`cerbero/bootstrap <https://gitlab.freedesktop.org/gstreamer/cerbero/tree/master/cerbero/bootstrap>`_ ，
如果要編 Linux 版就會根據 distro 安裝套件，
如果要編 Android 版就會去抓 Android NDK，
如果要編 Windows 版則會安裝 MinGW。

每個相依專案都會有 Recipe，
所有支援的專案可以看
`cerbero/recipes <https://gitlab.freedesktop.org/gstreamer/cerbero/tree/master/recipes>`_ ，
裡面有 ``PROJ.recipe`` 和 ``PROJ`` 資料夾，
資料夾內會有相關的 patches，
Recipe 會有編譯和安裝設定。

最後產生的釋出稱為 Package，
所有支援的 Package 可以看
`cerbero/packages <https://gitlab.freedesktop.org/gstreamer/cerbero/tree/master/packages>`_ ，
Package 會把數個 Recipes 整合成一包最終的檔案。

Toolchain 設定在
`cerbero/config <https://gitlab.freedesktop.org/gstreamer/cerbero/tree/master/config>`_ ，
包含 Cross Compile 的設定也在這邊，
例如 ``cross-android-arm64.cbc`` 、 ``cross-android-universal.cbc`` 、 ``cross-lin-arm.cbc`` 等等。


.. code-block:: sh

    $ git clone https://gitlab.freedesktop.org/gstreamer/cerbero.git
    $ cd cerbero/
    $ ./cerbero-uninstalled -h
    # 支援的 Recipes
    $ ./cerbero-uninstalled list
    # 支援的 Packages
    $ ./cerbero-uninstalled list-packages

    # 安裝基本環境需求（Native Build）
    $ ./cerbero-uninstalled bootstrap
    # 安裝基本環境需求（Cross Compile for Android ARM64）
    $ ./cerbero-uninstalled -c config/cross-android-arm64.cbc bootstrap
    # 安裝基本環境需求（Cross Compile for Android universal）
    $ ./cerbero-uninstalled -c config/cross-android-universal.cbc bootstrap

    # 編譯特定 Recipe
    $ ./cerbero-uninstalled -c config/cross-android-arm64.cbc build libffi
    # 重新編譯特定 Recipe
    $ ./cerbero-uninstalled -c config/cross-android-arm64.cbc buildone libffi

    # 製作特定 Package（會自動進行需要的編譯）
    # 會產生類似以下的兩包：
    # * gstreamer-1.0-android-arm64-1.15.1-runtime.tar.bz2 (動態 library、執行檔)
    # * gstreamer-1.0-android-arm64-1.15.1.tar.bz2 (靜態 library)
    $ ./cerbero-uninstalled -c config/cross-android-arm64.cbc package gstreamer-1.0


其他：

* 原始碼和 SDK 資料夾： ``~/.cache/cerbero-sources/``
* 編譯結果： ``build/``
    - ``dist/android_arm64/`` ，有 ``bin`` 、 ``lib`` 等等
    - ``dist/android_universal/``
    - ``dist/linux_x86_64/``
* 如果編譯出狀況失敗的話會提供選擇，看是要直接從失敗處重新編譯，該 Recipe 整個重編，提供 shell 做調整，或是放棄等等，不需要整個重頭開始
