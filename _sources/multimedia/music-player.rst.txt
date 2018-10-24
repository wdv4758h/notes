========================================
Music Player
========================================


.. contents:: 目錄


介紹
========================================

這邊紀錄的是專注於音樂的播放器，
針對音樂需求做客製化。


個人需要的功能：

* 歌曲清單
* 多種播放模式
    - 順序播放
    - 循環播放
    - 隨機播放
* 手機播放
* 搜尋
    - 作者
    - 專輯
    - 歌名
* 歌詞下載
* 支援多種格式
* 支援多種來源
    - Spotify
    - YouTube


以往的實做通常會把各種功能整合在一起，
使操作界面和底下功能綁在一塊。
後來出現像是 MPD 和 Mopidy 的實做，
採用 client/server 的架構，
藉此可以共享功能實做，
大家再根據需求和喜好調整操作界面，
也可以把 server 跑在隨意一台機器上後再用 client 遠端連過去操控。



MPD - Music Player Daemon
========================================

:site: https://www.musicpd.org/
:repo: https://github.com/MusicPlayerDaemon/MPD


首次釋出於 2003 年，
廣泛用於眾多音訊設備。




Mopidy
========================================

:site: https://www.mopidy.com/
:repo: https://github.com/mopidy
:docs: https://docs.mopidy.com/en/latest/


支援眾多 extension 支援，例如:

* Spotify
* YouTube
* Pandora
* SoundCloud


Mopidy 也可以透過內建的
`Mopidy-MPD <https://github.com/mopidy/mopidy/tree/master/mopidy/mpd>`_
成為 MPD server，藉此也可以使用 MPD 的 client。



參考
========================================

* `Wikipedia - Music Player Daemon <https://en.wikipedia.org/wiki/Music_Player_Daemon>`_
* `Arch Wiki - Music Player Daemon <https://wiki.archlinux.org/index.php/Music_Player_Daemon>`_
* `Music Player Daemon <https://github.com/MusicPlayerDaemon/MPD>`_
* `GitHub Topics - mpd <https://github.com/topics/mpd>`_


GNOME:

* Rhythmbox
* Lollypop
* Snappy
* Totem
