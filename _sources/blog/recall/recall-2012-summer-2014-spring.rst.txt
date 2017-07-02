:title: [回憶] 2012 年夏 ~ 2014 年春
:slug: recall-2012-summer-2014-spring
:date: 2014-02-18 21:00
:category: Misc
:tags: recall
:author: wdv4758h
:summary: 回想一些經過


一年半內除了學校的課程能學到些什麼？

不多也不少，這樣而已

(想到什麼就紀錄些什麼吧)

起頭
------------------------------

2012 年夏，正值升大學的時期，雖然進了資工系，但其實什麼都還不會，
暑假期間開始常上 BBS，後來看到上面的色碼還有其他的控制碼覺得很有趣，
接著就開始在上面試了一下，然後又看到某人在上面搞出一堆神奇的東西 (?)，
再來是開到上面的 vim mode (當時還不會用 vim)，
這算是初步接觸到 vim 的地方之一吧 XD (另外是鳥哥寫的文章)。

之後拿到了社團 server 上的帳號，開始連進去亂試指令 w，
從此掉進無底的坑洞 (X，這時間大概有時候會翻翻鳥哥吧，
到了學校後開始接觸 FreeBSD，
就裝來玩玩看，翻翻 FreeBSD handbook，開始認識 configure、make、ports ... etc，
當時在 FreeBSD 上用的是 tcsh (因為社團 server 預設是 tcsh，所以先接觸到 XD)，
因為一些原因開始看怎麼寫 shell script (Bourne Shell 的)，
慢慢知道有 sed、awk 這些東西，
開始使用 regular expression (已經想不起來從哪個時間點開始了)。

----

寫到這裡開始回去翻以前寫在 BBS 的文章回想 XD

阿對一開始還去玩了 pi 的貪吃蛇 ~

哦哦哦！BBS 上看到的有石頭文、guest 發文、... (?)

原來暑假就有翻過 regular expression，只是沒有碰到要使用的地方就不熟 XD，
後來有在用就比較 OK 了 ~

喔對，BBS 有聊天指令 XD

看到移位碼就想起之前試一試發現，
原本應該擋掉的名片檔移位碼在我亂試的情況下發現有 bug XDDDD，
後來被 PO 到 sysop，之後又修掉了。

原來當初 9 月開始就有去過 PyHUG，但是當時完全不會 Python zzz

找到了 ~ **2012/10/17 拋棄 Windows，轉用 Linux** ，
當時裝了 Ubuntu，DE 預設是 Unity，用沒多久後換成 Gnome 2，大概就這樣用了一學期。
寒假換成 LXDE 又用了一學期，中間好像有試過 Gnome 3 一陣子吧，
一下學期末把 WM 換成了 awesome wm，然後就離不開 awesome 一直到現在，
一下結束的暑假把 Ubuntu 換成了 Arch Linux ，變成 Arch Linux + awesome。

----

Vim
------------------------------

說到 Vim 啊 ...

一開始其實看到很多次，但是都沒有真的把它拿來用，所以不熟 zzz。
後來毅然決然把所有編輯純文字的東西都只用 vim ，一陣子後就習慣整個操作，
不過當時對 hjkl 的移動還不是很熟，索性在 .vimrc 裡把方向鍵 map 掉，
只用 hjkl 移動，後來也就習慣了。

一上結束的寒假稍微看了一下 .vimrc 的設定，調了一些東西和試了一些 plugin (雖然最後大多把 plugin 關了 XD)，
做的設定中幾個最常用到的是 paste mode 切換的快捷鍵、儲存時自動移除行尾多餘空白、下次開啟時回到關閉前的位置 ... etc。

plugin 部份的話用 Vundle 管理很方便，在加上一小段 script 後，
到新的地方只要打開 vim 就會自動裝好 vundle，
接著就可以利用 vundle 很快的把你的 plugin 裝起來，
利用 vundle 後 update plugin 也一樣只需要一個 command。

現在只要是純文字的東西我都用 vim，可以說是離不開了 XD，就連這篇文章也是我用 vim 打出來的 ~

Python
------------------------------

到底是從什麼時候開始比較常寫 Python 的我又忘了 (X

剛開始因為別人介紹，陸陸續續有看一點 Python 的東西，社課後知道了 list、tuple，
不過這時還是沒有在使用它，後來假期有人約讀書會所以看了 Python tutorial 的前部份。

一下結束後的暑假 (不知道是不是這個時期開始)，因為在跟高中同學打 game，
那遊戲在有人踩到紀錄點時會存資料在 host user，
而在某次遊戲中有人不小心在很糟糕的時間點踩到了，
結果只能回溯到那悲慘的時間點，
後來我就想說寫個程式讓他去 check 有新紀錄時就 backup 一次，
就開始用 Python 寫個小程式去 check，
東查西查，開始對 Python 變比較熟一點，
後來為了能一次 check 多個檔案又嘗試了 Python 的 multiprocessing，
而另一個同學則是去寫了簡單的 GUI，
在看了他的 code 並幫忙修改後，稍微對 Python 的 class 有點感覺了，
然後這也是我第一次使用內建的 tkinter 做簡單的 GUI。

之後開始愈來愈常寫 Python，慢慢的學會愈來愈多東西 XD

筆記
------------------------------

做筆記的方式嘛 ...

高中用過 Evernote 記了一點東西(不多)，
後來大一有陣子是 Google Docs + Markdown (本機)。

一下結束後的暑假聽到 Sphinx 這玩意，
看起來還不錯，也看到別人寫出來的東西，
所以就開始變成寫 reStructuredText 、用 Sphinx generate HTML，
不過 Markdown 也還是有再用 (這篇就是用 Markdown 寫的)，
所以目前是 Markdown & reStructuredText 亂用中 (X

Version Control
------------------------------

我現在常用的 Version Control 是 git，
一開始也是不熟 (看了看還是沒常用)，後來把一些東西用 git 上去後，
變成只熟 add & commit (X，後來碰到一些狀況而對 checkout、push、partial add、cherry-pick、stash 比較熟一點，
目前是基本操作還 OK 啦 (自己說

mercurial ...，目前無緣 XD，只在別人教的時候試過一次，不過因為已經慣用 git 了，所以 ... XD

cvs 只在抓 FreeBSD kernel source 的時候用過 zzz

Linux
------------------------------

一個無底洞 (X

我掉進去後就再也出不來了 XD

因為已經太融入生活了，不知道該說什麼 ~

現在用 Arch Linux 用的很開心  O w O

改天想到再補東西吧 ~

FreeBSD
------------------------------

FreeBSD 的部份算是配合修課做了點基本的學習，
內容大概有 FTP、Samba、ZFS、FAMP (FreeBSD + Apache + MySQL + PHP)、
NFS、amd (Berkeley Automounter)、NIS、PF、NAT、DHCP、SSL/TLS、Proxy、DNS、Postfix ...

這些算是有基本的接觸過了 (有架出東西)，最不熟的大概是最後的 Mail Server 部份吧 zzz，
東西弄起來有點麻煩，最後交作業的時候 ClamAV 偵測病毒信件的部份沒弄好 = =。

以前課程有 VPN，修課的時候剛好沒有，想之後找時間架來玩玩。

HTML, CSS, Javascript
------------------------------

這邊要從一下結束的暑假開始，
社團決定大家要一起用 Django 寫社團網站，
這時候就開始摸索 Django 和認識基本的 HTML，
不過 CSS 部份是由另一位負責，所以沒接觸。

後來進 OH 去用 Django 改寫目前的網站，
OH 原本的網站是套 Bootstrap 2，我在做新網站的時候改用了 Bootstrap 3，
接著就因為 Bootstrap 3 改了很多地方，所以要到處去修 Orz，
中間調樣式的時候開始認識一些 CSS 的東西，
某些地方因為用到 Javascript 所以也開始有了點接觸。

2014 2月，開始想用 GitHub Pages 來寫 blog，
於是開始使用 Pelican 這個 Python 寫的 static site generator，
因為可以用 Markdown 和 reStructuredText 所以可以很開心的用 vim 寫文章 ~~~

在使用 Pelican 寫 blog 後，想說順便來試著自己寫個 theme 來看看，
所以就開始寫更多的 CSS，中間在調某些功能的時候用到了 Javascript，
所以也寫了一小段的 Javascript code。

Database
------------------------------

Database 的話只會一點點簡單的 SQL 語法，
大多是寫東西需要去查的，用一用就知道了幾個，
只用過 SQLite、MySQL、MariaDB，不過都不熟就是了 XD，
因為碰到的東西重點都不是在調 Database，
很多都只是接上去而已。

C
------------------------------

說實話，C 其實只會些基本的東西，沒有很熟 XD

現在只想到好幾個月前在 Wikipedia 的 Multiple dispatch 頁面看到的 C code 感覺還蠻有趣的 (X

C++
------------------------------

一下的 OOP 課開始頻繁接觸 C++，
因為老師的課程安排，所以學了一些 C++11 的東西，
老師在 constructor 那部份講了好一陣子，
後來作業的關係寫了自己的 vector 和 list Orz，
還記得那時候在講 new，new operator、operator new、placement new ...

某次作業好像用到了 C++11 加進來的 lambda expression。

其實老師的講義寫了很多東西，只是我還沒能好好吸收起來 ...，
只好一定要好好補起來 = =

Makefile
------------------------------

曾經在某陣子因為寫 C++ 作業的關係看了些 Makefile 的東西，
也寫了些簡單的 Makefile ...，不過現在差不多忘了 (X

awk
------------------------------

awk 好像寫過那麼一下 ...

sed
------------------------------

sed 好像在某次作業用過，還有自己寫的 shell script 裡用過，
不過基本上 ... 不熟 XD

shell script (Bourne Shell)
------------------------------

shell script 少數時候會因需求寫一點，
不過都是寫純 Bourne Shell 的 (X，
Bash 的只有在 .bashrc 裡寫過 XD

lua
------------------------------

接觸到 lua 是因為轉用 awesome wm 的關係 XD，
awesome wm 的設定檔是用 lua 寫的，
所以改的時候會看到一些 lua 語法 ~，
前陣子在看 coroutine 的時候又看到用 lua 去說明的文章，
不過說那麼多其實還是沒在寫 lua XD (根本沒好好學過)

Perl
------------------------------

Perl 只有在寫作業 (irc bot、大量寄信程式、登入時間統計) 的時候用過，
寫完之後就沒用過了 (X，現在可以說是完全不會了 XD

Functional Programming
------------------------------

有想要接觸 Functional 的東西耶

之後想找時間學 Haskell ~ (曾經在某天翻過，連基本的都差不多忘光了 XD

最近寫 Python 開始慢慢使用 lambda、filter、map、reduce (X
