========================================
Role-playing Games (RPG)
========================================

我自己玩遊戲的時間雖然不算多，
但是也算接觸過不少 RPG 遊戲。
要製作 RPG 遊戲的話，
最知名的工具應該是 RPG Maker。
不是要說 RPG Maker 不好，
只是身為一個愛好開放原始碼的工程師，
沒有夠完整的開放專案心理總有些缺憾 :P 。
於是我開始找呀找，
找到了 EasyRPG 這個開放原始碼的專案，
在相似的開放原始碼專案中，
EasyRPG 看起來是完整度最高的！


（遊戲本身要開源很不容易，
但至少讓我追求週邊工具可以開源，
甚至遊戲過了商業期後可以開放出來 :P）


.. contents:: 目錄



EasyRPG
========================================

EasyRPG 是一個社群在維護的 Open Source 專案，
目的是要建立開放的 RPG 製作工具，
現階段目標為相容 RPG Maker 2000/2003 做出的遊戲。


EasyRPG Player - 善用現有生態圈
-------------------------------

EasyRPG Player 為 RPG Maker 2000/2003 的直譯器，
目的是要在各個平台跑起使用 RPG Maker 製作的遊戲，
目前支援的平台有 Linux、Mac、Windows、
Android、HTML5/JavaScript、Wii、Nintendo 3DS 等等。


編譯（Arch Linux）
++++++++++++++++++++

.. code-block:: sh

    git clone https://aur.archlinux.org/liblcf
    cd liblcf && makepkg -si && cd ..
    git clone https://aur.archlinux.org/easyrpg-player
    cd easyrpg-player && makepkg -si



RTP Replacement
-------------------------------


EasyRPG Editor
-------------------------------



參考
========================================

* `EasyRPG <https://easyrpg.org/>`_
* [GitHub] `EasyRPG <https://github.com/EasyRPG>`_
* `RPG製作大師 - 巴哈姆特 <http://forum.gamer.com.tw/A.php?bsn=04918>`_
