========================================
PulseAudio
========================================


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

		$ pacmd list | rg "Default sink"
		Default sink name: alsa_output.pci-0000_00_1f.3.analog-stereo
		$ pacmd set-sink-port "alsa_output.pci-0000_00_1f.3.analog-stereo" analog-output-speaker



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



設定檔
========================================

``/etc/pulse/default.pa``



Echo Cancellation
========================================

在設定檔裡加上：

::

    load-module module-echo-cancel



GUI
========================================

* pavucontrol



參考
========================================

* `Arch Wiki - PulseAudio <https://wiki.archlinux.org/index.php/PulseAudio>`_
* `Arch Wiki - PulseAudio/Examples <https://wiki.archlinux.org/index.php/PulseAudio/Examples>`_
* `Gentoo Wiki - PulseAudio <https://wiki.gentoo.org/wiki/PulseAudio>`_

* `PulseAudio under the hood <https://gavv.github.io/blog/pulseaudio-under-the-hood/>`_
* `Arch Wiki - PulseAudio <https://wiki.archlinux.org/index.php/PulseAudio>`_
* `Beamforming in PulseAudio <https://arunraghavan.net/2016/06/beamforming-in-pulseaudio/>`_
