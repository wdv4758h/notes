========================================
PipeWire
========================================


.. contents:: 目錄


介紹
========================================

:site: https://pipewire.org/


* 涵蓋目前 PulseAudio 和 Jack 的使用情境，具有相容層
* 提供一致的方式來同時支援一半桌面應用和專業低延遲應用
* 除了音訊外，還支援影像，提供和音訊同等的彈性和管理給攝影機、桌面視窗等
* 提供 sandbox 應用程式的支援
* 支援 GStreamer


.. code-block:: sh

    sudo pacman -S pipewire pipewire-pulse


如果使用比較輕量的視窗管理而沒有 D-Bus 啓動的話，
可以在 ``~/.xinitrc`` 裡面補上：

.. code-block:: sh

   if which dbus-launch >/dev/null && test -z "$DBUS_SESSION_BUS_ADDRESS"; then
       eval `dbus-launch --sh-syntax --exit-with-session`
   fi


可以使用以下指令檢查：

.. code-block:: sh

    systemctl status --user pipewire
    # 如果有使用 pipewire-pulse 的話
    systemctl status --user pipewire-pulse
    # 如果有使用 pipewire-pulse 的話，
    # 會看到類似「Server Name: PulseAudio (on PipeWire 0.3.20)」
    pactl info



PipeWire v.s. PulseAudio
========================================

PulseAudio 的目標是桌面應用，
這也包含在 PipeWire 的目標內。
既有的 PulseAudio 在一些情境下有使用過多 CPU 的問題，
而且延遲的問題在既有設計下無法定改善。

使用 pipewire-pulse 的話可以直接把 PipeWire 當做 PulseAudio 使用，
藉此可以輕易的替換測試！



PipeWire v.s. JACK
========================================



參考
========================================

* `Wikipedia - PipeWire <https://en.wikipedia.org/wiki/PipeWire>`_
* `Arch Wiki - PipeWire <https://wiki.archlinux.org/index.php/PipeWire>`_
* `Gentoo Wiki - PipeWire <https://wiki.gentoo.org/wiki/Pipewire>`_
* `PipeWire FAQ <https://github.com/PipeWire/pipewire/wiki/FAQ>`_
* [2020] `PipeWire: a low-level multimedia subsystem <https://lac2020.sciencesconf.org/307881/document>`_
    - 古早的 Linux 音訊支援是 OSS (Open Sound System)，而且是 Linux 2.4 以前唯一的音訊 API，基於 open/close/read/write/ioctl
    - Linux 2.5 用 ALSA (Advanced Linux Sound Architecture) 取代了 OSS
    - OSS 和 ALSA 都有同時只能有一個應用程式能使用特定裝置的限制
    - 後來 ALSA 實作了軟體混音器插件（Dmix），但是有很多缺陷，使用也不夠有彈性
    - EsoundD (ESD) 爲早期的 sound server 之一，使用 socket 來接收許多音訊，在送出去之前先混合，使用 TCP，而且不支援低延遲
    - BSD 有另一套簡單的音訊 API 叫 sndio，這 API 也支援 midi，它用 Unix pipe 來傳送音訊，而且也不支援低延遲
    - 2002 年，Paul Davis 基於 Ardour 內的音訊引擎實作了 JACK，提供及時、低延遲的應用給音訊和 midi
        + JACK 內維護一個應用程式的流線圖，各個點之間用 port 連接，使用 device interrupt 來叫醒程式去處理資料
        + JACK 雖然支援低延遲，但是缺少一些桌面應用需要的功能，例如 format support/power saving/dynamic devices/volume control/security/...
    - PulseAudio 是模組化的現代音訊伺服器，和先前的實作相比，可以支援自動且動態地建立和配送給多裝置
        + PulseAudio 雖然支援省電應用，但是需要花費過多 CPU 來叫醒程式
    - PipeWire 基於先前的經驗，提供改善和相容
        + 起源於要在 sandbox 環境內使用音訊硬體，但是後來設計上又有了更多改進
        + 有相容層給 JACK 和 PulseAudio，既有的應用程式不需要改動就能使用
        + 架構中一個重要的角色是 session manager，管理裝置的設定和控制策略
        + 應用程式和音訊伺服器的協定本身爲非同步
        + 格式溝通採用和 GStreamer 一樣的格式描述，可以在兩端點間取交集找到合適的溝通格式

* `Getting the team together to revolutionize Linux audio <https://blogs.gnome.org/uraeus/2018/09/24/getting-the-team-together-to-revolutionize-linux-audio/>`_
* `FOSDEM 2019 - Pipewire <https://fosdem.org/2019/schedule/event/pipewire/attachments/slides/2826/export/events/attachments/pipewire/slides/2826/PipeWire.pdf>`_
* `PipeWire, the media service transforming the Linux multimedia landscape <https://www.collabora.com/news-and-blog/blog/2020/03/05/pipewire-the-media-service-transforming-the-linux-multimedia-landscape/>`_
