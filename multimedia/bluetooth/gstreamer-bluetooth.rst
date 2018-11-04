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


直接透過 BlueZ
========================================
