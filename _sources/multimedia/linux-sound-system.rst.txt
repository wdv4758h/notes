========================================
Linux Sound System
========================================


.. contents:: 目錄


介紹
========================================

Sound System 分成好幾個層級：

* 硬體支援和控制（需要 Driver & Interface）
* Usermode Library 提供應用程式需要的功能
* [Optional] Usermode Sound Server
* [Optional] Sound Framework


Linux 裝起來後通常會內建 ALSA 這個 kernel sound system
（以前是內建 Open Sound System （OSS））。


Sound Server 則有比較多的選擇，
但是無論選擇哪個 Sound Server，
最底下還是 ALSA：

* PulseAudio： Linux 上常用的 Sound Server，使用比較簡單，但是不是針對 low-latency 設計的
* JACK： 針對 low-latency 設計的 Sound Server（例如 5 ms），使用 C 實做
* JACK2： JACK 的 C++ 實做，支援的 Protocol 一樣，但是後來因為社群和開發者因素沒有完整取代掉 JACK
* JACK2 with D-BUS： JACK2 使用不同啟動架構的版本，可以和其他非 JACK 的應用程式一起使用，像是 PulseAudio


Sound Server 的存在是因為音效卡的存取通常是獨占的，
這會造成只有一個應用程式可以使用音效卡，
因此引入了一個中間層（也就是 Sound Server）處理，
Sound Server 負責跟音效卡溝通，
其他程式則透過 Sound Server 提供的 IPC 機制來存取。

Linux 上常見的 Sound Server 分別是 PulseAudio 和 JACK，
他們都是用 ``mmap`` 來存取，
因此會 block 住音效卡 driver。
但是 PulseAudio 的開發重點著重在提昇桌面環境的使用經驗，
例如網路來的音效、省電、每個應用程式的混合等級等。
而 JACK 則 著重在即時的處理，
強調 low-latency 的操作和 clients 間的緊密同步，
比較適合專業級的應用。

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

* `Arch Wiki - Sound System <https://wiki.archlinux.org/index.php/Sound_system>`_
* `Arch Wiki - Professional Audio <https://wiki.archlinux.org/index.php/Professional_audio>`_
* `Arch Wiki - Advanced Linux Sound Architecture <https://wiki.archlinux.org/index.php/Advanced_Linux_Sound_Architecture>`_
* `Arch Wiki - JACK Audio Connection Kit <https://wiki.archlinux.org/index.php/JACK_Audio_Connection_Kit>`_

* `Wikipedia - Advanced Linux Sound Architecture <https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture>`_
* `Wikipedia - PulseAudio <https://en.wikipedia.org/wiki/PulseAudio>`_
* `Wikipedia - JACK Audio Connection Kit <https://en.wikipedia.org/wiki/JACK_Audio_Connection_Kit>`_

* `Advanced Linux Sound Architecture (ALSA) project homepage <http://www.alsa-project.org/main/index.php/Main_Page>`_
* `JACK Wiki <https://github.com/jackaudio/jackaudio.github.com/wiki>`_
* `Jack vs Pulseaudio -- how is it faster? - Unix & Linux Stack Exchange <https://unix.stackexchange.com/a/181625/98379>`_
* `Linux Kernel - Sound Subsystem <https://wiki.archlinux.org/index.php/PulseAudio/Configuration>`_

* `Design and Development of a mechanism for low-latency real-time audio processing on Linux <https://retis.sssup.it/sites/default/files/realtime_low_latency_audio_on_linux.pdf>`_
    - 一份資訊很多的介紹，值得一看
* `PulseAudio under the hood <https://gavv.github.io/blog/pulseaudio-under-the-hood/>`_
