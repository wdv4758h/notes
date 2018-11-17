========================================
GStreamer 相關 Dockerfile
========================================


.. contents:: 目錄


Arch Linux
========================================

執行環境
------------------------------

整套裝完輸出成 rootfs.tar 大約 1.4 GB，
可以根據需求刪去不需要的東西。
用 ``gst-inspect-1.0`` 去看的話會有
``255 plugins (7 blacklist entries not shown), 1407 features`` ，
沒有正常顯示的 plugin 是因為需要更多相依套件，
例如 OpenCV。


.. code-block:: dockerfile

    FROM archlinux/base

    RUN pacman -Syu --noconfirm
    RUN pacman -S --noconfirm \
            gstreamer \
            gst-plugins-base \
            gst-plugins-good \
            gst-plugins-bad \
            gst-plugins-ugly \
            gst-libav \
            gst-python \
            gstreamer-vaapi \
            gst-editing-services \
            gst-validate


編譯環境
------------------------------



Alpine Linux
========================================

執行環境
------------------------------

整套裝完輸出成 rootfs.tar 大約 136 MB，
但是 Alpine Linux 上的環境更新比 Arch Linux 慢，
完整度也比較低，
缺不少東西（像是沒有 ``gst-python`` 的套件，沒有出現 ``webrtcbin`` plugin 等等），
用 ``gst-inspect-1.0`` 去看的話會有 ``205 plugins, 1339 features`` 。


.. code-block:: dockerfile

    FROM alpine:3.8

    RUN apk add --no-cache ca-certificates
    RUN apk add --no-cache \
            gstreamer \
            gstreamer-tools \
            gst-plugins-base \
            gst-plugins-good \
            gst-plugins-bad \
            gst-plugins-ugly \
            gst-libav


編譯環境
------------------------------


