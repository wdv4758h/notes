:title: Django migrations
:slug: django-migrations-ask-log
:date: 2015-04-16 00:23
:modified: 2015-04-16 00:23
:category: Python
:tags: Django, migrations
:author: wdv4758h
:summary: 學弟來詢問的紀錄

前幾天學弟跑來問我說 Django 裡的 migrations 要怎麼用？

本來想說留個筆記，下次碰到問題時可以參考，後來決定紀錄對話 (X

----

學弟 M：「dv ~，Django 的 migrations 要怎麼用啊？」

我：「你就想像是 database 的 version control 啊。用 ``python manage.py makemigrations myapp`` 會把更動 commit 上去。」

----

(幾分鐘後)

學弟 M：「可是我更改後它沒有偵測到耶」

我：「蛤 ~ ?」

我：「我之前用過可以正常偵測到啊，你的東西應該是用 inspectdb 去爬之前用的 database 生出來的吧 (我知道他要接現有的資料庫)，生出來後有先 makemigrations 嗎？」

學弟 M：「有啊，還是沒偵測到。」

----

(我跑過去東看西看)

學弟 M：「dv，還是我開我機器的帳號給你進來看好了？」

我：「喔喔，好窩」

----

(我進去東試試西試試)

我：「真的沒偵測到耶，好奇怪喔 ~ 囧」

----

(開始 Google 各種資訊)

我：「還是它自己的問題？要升升 1.8 看嗎？反正你才剛開始寫。(隨便亂猜)」

----

(我開始看 Django 1.8 的 release 有沒有相關的 change)

學弟 M：「好啊，我不是用 1.8 喔」

我：「我剛剛看你是 1.7.2 啊」

學弟 M：「喔喔，我去升看看」

----

(幾分鐘後)

學弟 M：「我升好了~」

我：「有東西壞掉了耶 XD」

我：「看起來是底下的 db connector」

學弟 M：「真的耶，壞掉惹 Q_Q」

----

(Google 中)

我：「原本你用的 mysql-connector-python 現在還沒支援 Django 1.8」

我：「可以先換 PyMySQL，裝一下 ~」

學弟 M：「好，我用 pip 裝一下」

學弟 M：「裝好啦」

----

(我去改 settings.py 換成 django.db.backends.mysql)

我：「好啦 ~ 正常了，可以開始找剛剛的問題了 ...」

----

(經過一些檔案開開關關和嘗試)

我：「找到問題啦，你的 models 那裡設了 ``manage = False`` 這樣他不會去偵測更動」

我：「inspectdb 出來的就設成 False 了，應該是因為你在用 inspectdb 時，代表你很有可能有另外的程式在負責管理 database，所以 Django 預設就不去做更動。」

學弟 M：「哦哦哦，真的耶，解決啦，感謝 dv ~」

我：「喔，你那邊還會有些訊息說需要 default 值的 field 沒有給 default 值，你去改改後應該就都會 work 了」

----

以上是在剛剛由回憶中撈取，根據修過的心理學，記憶是建構出來的，如有錯誤，我也沒辦法 XD
