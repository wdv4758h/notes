========================================
Linux Sound System
========================================


.. contents:: 目錄


概覽
========================================

Linux 聲音生態系中的東西可以分成：

* 硬體層（Hardware Layer）：硬體裝置，輸入和輸出
* 核心層（Kernel Layer）：溝通和管理各個硬體的介面（OSS、ALSA）
* Libraries：操控影音的介面與產生串流（GStreamer、Libcanberra、libpulse、libalsa、...），標準的格式（LADSPA）
* 聲音伺服器（Sound Server）：讓使用者操控起來更簡單（sndio、ESD、aRts、PulseAudio、PipeWire）
    - Sound Server 的存在是因為音效卡的存取通常是獨占的，造成只有一個應用程式可以使用音效卡
    - 因此引入了一個中間層（也就是 Sound Server）處理
    - Sound Server 負責跟音效卡溝通，其他程式則透過 Sound Server 提供的 IPC 機制來存取


簡易發展史：

* 古早的 Linux 音訊支援是 OSS (Open Sound System)，而且是 Linux 2.4 以前唯一的音訊 API，基於 open/close/read/write/ioctl
* 2002 年，Linux 2.5 用 ALSA (Advanced Linux Sound Architecture) 取代了 OSS
* OSS 和 ALSA 都有同時只能有一個應用程式能使用特定裝置的限制
* 後來 ALSA 實作了軟體混音器插件（Dmix），但是有很多缺陷，使用也不夠有彈性
* EsounD (ESD) 爲早期的 sound server 之一，使用 socket 來接收許多音訊，在送出去之前先混合，使用 TCP，而且不支援低延遲
    - 全名爲 Enlightened Sound Daemon
    - 當時使用於 Enlightenment 和 GNOME
* aRts 爲 KDE 社群開發出來的 sound server，支援模擬類比合成器，現今已經被淘汰
* BSD 有另一套簡單的音訊 API 叫 sndio，這 API 也支援 midi，它用 Unix pipe 來傳送音訊，而且也不支援低延遲
* 2002 年，Paul Davis 基於 Ardour 內的音訊引擎實作了 JACK，提供及時、低延遲的應用給音訊和 midi
    - JACK 內維護一個應用程式的流線圖，各個點之間用 port 連接，使用 device interrupt 來叫醒程式去處理資料
    - JACK 雖然支援低延遲（例如 5 ms，硬體夠好搭配正確的設定的話，有機會達到 1ms），但是缺少一些桌面應用需要的功能，例如 format support/power saving/dynamic devices/volume control/security/...
* 2004 年，PulseAudio 釋出，是模組化的現代音訊伺服器
    - 和先前的實作相比，可以支援自動且動態地建立和配送給多裝置
    - PulseAudio 雖然支援省電應用，但是需要花費較多 CPU 來叫醒程式（因爲採用 timer based）
    - 設計上專注在桌面應用
    - 有非常模組化的設計，可以支援各式各樣的應用
* 2017 年，PipeWire 基於先前的經驗，提供改善和相容
    - 由 Wim Taymans 建立（GStreamer 的共同創造者）
    - 一開始叫 PulseVideo，但後來加入音訊支援
    - 起源於要在 sandbox 環境內使用影音硬體，但是後來設計上又有了更多改進
    - 有相容層給 JACK 和 PulseAudio，既有的應用程式不需要改動就能使用
    - 架構中一個重要的角色是 session manager，管理裝置的設定和控制策略
    - 應用程式和音訊伺服器的協定本身爲非同步
    - 格式溝通採用和 GStreamer 一樣的格式描述，可以在兩端點間取交集找到合適的溝通格式
    - `Launching Pipewire <https://blogs.gnome.org/uraeus/2017/09/19/launching-pipewire/>`_



其他
========================================

在討論延遲的時候要考慮到物理限制，
例如聲音在空氣中的傳播速度約為 330 ~ 350 公尺/秒，
如果喇叭在聽眾 5 公尺外的地方，
那物理限制就是聽眾會感受到至少 14 ~ 15 毫秒的延遲。
網路傳輸也是，
如果使用光纖傳輸，
光速大約是 300000 公里/秒，
假如傳輸距離是 12000 公里，
那物理限制就是至少會有 40 毫秒的延遲。



參考
========================================

* [2021] `Making Sense of The Audio Stack On Unix <https://venam.nixers.net/blog/unix/2021/02/07/audio-stack.html>`_
    - 非常值得一讀的文章

* `Arch Wiki - Sound System <https://wiki.archlinux.org/index.php/Sound_system>`_
* `Arch Wiki - Professional Audio <https://wiki.archlinux.org/index.php/Professional_audio>`_
* `Arch Wiki - Advanced Linux Sound Architecture <https://wiki.archlinux.org/index.php/Advanced_Linux_Sound_Architecture>`_
* `Arch Wiki - JACK Audio Connection Kit <https://wiki.archlinux.org/index.php/JACK_Audio_Connection_Kit>`_

* `Wikipedia - Sound Server <https://en.wikipedia.org/wiki/Sound_server>`_
* `Wikipedia - Advanced Linux Sound Architecture <https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture>`_
* `Wikipedia - PulseAudio <https://en.wikipedia.org/wiki/PulseAudio>`_
* `Wikipedia - JACK Audio Connection Kit <https://en.wikipedia.org/wiki/JACK_Audio_Connection_Kit>`_

* `Advanced Linux Sound Architecture (ALSA) project homepage <http://www.alsa-project.org/main/index.php/Main_Page>`_
* `JACK Wiki <https://github.com/jackaudio/jackaudio.github.com/wiki>`_
* `Jack vs Pulseaudio -- how is it faster? - Unix & Linux Stack Exchange <https://unix.stackexchange.com/a/181625/98379>`_
* `Linux Kernel - Sound Subsystem <https://wiki.archlinux.org/index.php/PulseAudio/Configuration>`_
* `JACK Latency tests <https://wiki.linuxaudio.org/wiki/jack_latency_tests>`_

* `Design and Development of a mechanism for low-latency real-time audio processing on Linux <https://retis.sssup.it/sites/default/files/realtime_low_latency_audio_on_linux.pdf>`_
    - 一份資訊很多的介紹，值得一看
* `PulseAudio under the hood <https://gavv.github.io/blog/pulseaudio-under-the-hood/>`_
