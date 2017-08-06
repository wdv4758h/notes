=-=======================================
PulseAudio
=========================================


.. contents:: 目錄


更換輸出
=========================================

GUI:

.. code-block:: sh

    $ pavucontrol


CLI:

.. code-block:: sh

    $ pacmd list | rg "active port"
        active port: <analog-output-speaker>
        active port: <analog-output-headphones>
        active port: <analog-input-internal-mic>

    $ pacmd set-sink-port 0 analog-output-speaker
    $ pacmd set-sink-port 0 analog-output-headphones



重啟
========================================

檢查是否已經有在跑：

.. code-block:: sh

    $ pulseaudio --check


kill 掉已經在跑得程式：

.. code-block:: sh

    $ pulseaudio -k


如果沒有 Daemon 就開一個：

.. code-block:: sh

    $ pulseaudio --start



參考
========================================

* `Arch Wiki - PulseAudio <https://wiki.archlinux.org/index.php/PulseAudio>`_
* `Arch Wiki - PulseAudio/Examples <https://wiki.archlinux.org/index.php/PulseAudio/Examples>`_
