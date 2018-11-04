========================================
GStreamer & Bluetooth
========================================


.. contents:: 目錄


透過 PulseAudio 串給 BlueZ
========================================

.. code-block:: sh

    # 一般透過 PulseAudio 播放音樂
    $ gst-launch-1.0 -v filesrc location=test.mp3 ! decodebin ! pulsesink

    # 透過 PulseAudio 傳音樂給藍芽喇叭
    # 先用 pacmd 了解裝置名稱
    $ pacmd list-cards | rg "(bluez_sink|alsa_output)" | rg -v monitor
          alsa_output.pci-0000_00_1f.3.analog-stereo/#0: Built-in Audio Analog Stereo
          bluez_sink.FF_FF_FF_FF_FF_FF.a2dp_sink/#1: SRS-XB30
    $ gst-launch-1.0 -v filesrc location=test.mp3 ! decodebin ! pulsesink device=bluez_sink.FF_FF_FF_FF_FF_FF.a2dp_sink



透過 ALSA 和 BlueALSA 串給 BlueZ
========================================

.. code-block:: sh

    # 一般透過 ALSA 播放音樂
    $ gst-launch-1.0 -v filesrc location=test.mp3 ! decodebin ! alsasink


.. code-block:: sh

    # 因為 BlueZ 的限制，只能有一個人控制藍牙音訊裝置，
    # BlueALSA 和 PulseAudio 會互相打架，
    # 要使用 BlueALSA 的話有以下選擇：
    # 1. 關閉 PulseAudio，只開 ALSA
    # 2. 關閉 PulseAudio 對藍牙音訊的掌控，但是保留 PulseAudio 對其他裝置的掌控，讓 BlueALSA 掌控藍牙音訊

    # 抓 Arch Linux 的 BlueALSA 套件
    git clone https://aur.archlinux.org/bluez-alsa-git.git
    # 編譯套件
    makepkg
    # 安裝套件
    sudo pacman -U bluez-alsa-git-*.pkg.tar.xz

    # 根據套件指示更改設定檔：
    # =====->
    # You have to grant BlueZ access to user bluealsa
    # Add those lines to /etc/dbus-1/system.d/bluetooth.conf
    <policy user="bluealsa">
      <allow send_destination="org.bluez"/>
    </policy>
    # Users can use this service when they are members of the "audio" group.
    # <=====

    # 關閉 PulseAudio
    systemctl --user stop pulseaudio.socket
    # 開啟 BlueALSA
    sudo systemctl start bluealsa.service

    # 開啟 BlueZ
    systemctl restart bluetooth 2> /dev/null
    # 連接裝置
    bluetoothctl connect FF:FF:FF:FF:FF:FF

    # 列出 bluealsa 狀態
    sudo amixer -D bluealsa
    # 列出 bluealsa 支援的 simple controls
    sudo amixer -D bluealsa scontrols
    # 透過 bluealsa 設定音量
    sudo amixer -D bluealsa set 'SRS-XB30 - A2DP' 30%

    # 透過 aplay 播放 wav 檔
    sudo aplay -D bluealsa:HCI=hci0,DEV=FF:FF:FF:FF:FF:FF,PROFILE=a2dp test.wav

    # 用 GStreamer 透過 ALSA 和 BlueALSA 傳給 BlueZ
    sudo gst-launch-1.0 -v filesrc location=test.wav ! decodebin ! alsasink device=bluealsa:HCI=hci0,DEV=FF:FF:FF:FF:FF:FF,PROFILE=a2dp



直接透過 BlueZ
========================================
