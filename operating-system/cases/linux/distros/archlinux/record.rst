========================================
錄螢幕、攝影機、Terminal
========================================


.. contents:: 目錄


OBS (Open Broadcaster Software)
========================================

安裝：

.. code-block:: sh

    $ sudo pacman -S obs-studio


開啟：

.. code-block:: sh

    $ obs


打開後可以選擇要加入哪些來源，
音訊例如：PulseAudio (Audio Input/Audio Output)、ALSA 等，
視訊例如：Camera（V4L2）、Screen、Window（Xcomposite）等。

另外可以選擇錄成檔案或直接串流出去。

（目前在 Linux 上用過最好用的）



asciinema (專錄 Terminal）
========================================

asciinema 是專門錄 Terminal 並重新播放的程式，
並不是一個 General 的錄製程式，
會把指令的輸入和執行結果錄起來，
之後可以在 Terminal 播放。


.. code-block:: sh

    $ sudo pacman -S asciinema

.. code-block:: sh

    # 錄製
    $ asciinema rec asciicast.json

    # 播放
    $ asciinema play asciicast.json



參考
========================================

* `How it works - asciinema <https://asciinema.org/docs/how-it-works>`_
* `asciinema - 2.0 <http://blog.asciinema.org/post/two-point-o/>`_
    - standard JSON -> newline-delimited JSON
    - real-time streaming friendly
    - recording session is interruptable
