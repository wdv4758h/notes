========================================
使用 Docker 跑 GUI 程式
========================================


.. contents:: 目錄


顯示畫面
========================================

Xorg
------------------------------

.. code-block:: sh

    # 自動給現在的桌面顯示的權限
    xhost +local:docker
    # 或者指定桌面顯示的權限
    env DISPLAY=:0 xhost +local:docker

    docker run -it --rm \
        -e DISPLAY=${DISPLAY} \
        -v /tmp/.X11-unix:/tmp/.X11-unix \
        mycontainer



Wayland
------------------------------




攝影機
========================================

PipeWire
------------------------------

.. code-block:: sh

    docker run -it --rm \
        --device /dev/video0:/dev/video0 \
        -e XDG_RUNTIME_DIR=${XDG_RUNTIME_DIR} \
        mycontainer



音效卡
========================================

ALSA
------------------------------

要在 container 內透過 ALSA 使用音效卡只需要把 ``/dev/snd`` 傳入即可。


.. code-block:: sh

    docker run -it --rm \
        --device /dev/snd \
        mycontainer


PulseAudio
------------------------------

PulseAudio 有功能可以透過 socket 溝通，
container 可以透過 socket 操作 PulseAudio，
socket 可以是 Unix domain socket 也可以是 TCP socket。


不同作法：

1. [container 內不需要 libpulse] 開啟 socket，把現有 cookie 傳進去給 container 用
    - 適用：container 內有程式需要使用，但是不需要直接對 PulseAudio 進行操作
    - 例如：使用 GStreamer 的 pulsesrc/pulsesink
2. [container 內  需要 libpulse] 開啟 socket，設定 container 不開 PulseAudio server，讓它自己建 cookie


container 內不需要 libpulse:

.. code-block:: sh

    # 開 Unix domain socket
    ls /tmp/pulseaudio.socket || pactl load-module module-native-protocol-unix socket=/tmp/pulseaudio.socket
    # 開 containter，傳入 socket 和 cookie
    docker run -it -rm \
        --volume /tmp/pulseaudio.socket:/tmp/pulseaudio.socket \
        --volume ~/.config/pulse/cookie:/tmp/pulseaudio.cookie \
        --env PULSE_SERVER=unix:/tmp/pulseaudio.socket \
        --env PULSE_COOKIE=/tmp/pulseaudio.cookie \
        mycontainer


container 內需要 libpulse:

.. code-block:: sh

    # 開 Unix domain socket
    ls /tmp/pulseaudio.socket || pactl load-module module-native-protocol-unix socket=/tmp/pulseaudio.socket

    # 建立 PulseAudio client 設定檔
    cat > /tmp/pulseaudio.client.conf <<EOF
    default-server = unix:/tmp/pulseaudio.socket
    # Prevent a server running in the container
    autospawn = no
    daemon-binary = /bin/true
    # Prevent the use of shared memory
    enable-shm = false
    EOF

    # 開 containter，傳入 socket 和 cookie
    docker run -it -rm \
        --volume /tmp/pulseaudio.socket:/tmp/pulseaudio.socket \
        --volume /tmp/pulseaudio.client.conf:/etc/pulse/client.conf \
        --env PULSE_SERVER=unix:/tmp/pulseaudio.socket \
        --env PULSE_COOKIE=/tmp/pulseaudio.cookie \
        mycontainer



參考
========================================

* `x11docker wiki <https://github.com/mviereck/x11docker/wiki/>`_
