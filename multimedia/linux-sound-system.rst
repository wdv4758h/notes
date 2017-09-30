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


Sound Server 則有比較多的選擇：

* PulseAudio： Linux 上常用的 Sound Server，使用比較簡單，但是不是針對 low-latency 設計的
* JACK： 針對 low-latency 設計的 Sound Server，使用 C 實做
* JACK2： JACK 的 C++ 實做，支援的 Protocol 一樣，但是後來因為社群和開發者因素沒有完整取代掉 JACK
* JACK2 with D-BUS： JACK2 使用不同啟動架構的版本，可以和其他非 JACK 的應用程式一起使用，像是 PulseAudio



參考
========================================

* `Arch Wiki - Sound System <https://wiki.archlinux.org/index.php/Sound_system>`_
* `Arch Wiki - Professional Audio <https://wiki.archlinux.org/index.php/Professional_audio>`_
* `Arch Wiki - Advanced Linux Sound Architecture <https://wiki.archlinux.org/index.php/Advanced_Linux_Sound_Architecture>`_
* `Wikipedia - Advanced Linux Sound Architecture <https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture>`_
* `Advanced Linux Sound Architecture (ALSA) project homepage <http://www.alsa-project.org/main/index.php/Main_Page>`_
* `JACK Wiki <https://github.com/jackaudio/jackaudio.github.com/wiki>`_
