:title: Celery - Distributed Task Queue
:slug: celery
:date: 2015-01-26 23:45
:modified: 2015-01-26 23:45
:category: Python
:tags: Celery, RabbitMQ
:author: wdv4758h
:summary:

.. contents::

試到一半的 Celery ~"~ (未來會繼續)

Introduction
========================================

simple, flexible and reliable distributed system to process vast amounts of messages

task queue with focus on real-time processing, while also supporting task scheduling

BSD license

Tutorial
========================================

Choosing a Broker
------------------------------

Broker 的功能是收發 messages，這邊通常會用專門的 **message broker** 來處理，
例如 :

* RabbitMQ
    - feature-complete
    - stable
    - durable
    - excellent choice for a production environment

* Redis
    - feature-complete
    - more susceptible to data loss in the event of abrupt termination or power failures

* Database
    - 不推薦拿 database 來當 message queue
    - 但對於小需求可能就足夠

* Other Brokers
    - Amazon SQS
    - MongoDB
    - IronMQ



`Broker Overview <http://celery.readthedocs.org/en/latest/getting-started/brokers/index.html>`_
: (2015-01-27)

.. table::
    :class: table table-bordered

    +------------+--------------+------------+----------------+
    | Name       | Status       | Monitoring | Remote Control |
    +============+==============+============+================+
    | RabbitMQ   | Stable       | Yes        | Yes            |
    +------------+--------------+------------+----------------+
    | Redis      | Stable       | Yes        | Yes            |
    +------------+--------------+------------+----------------+
    | Mongo DB   | Experimental | Yes        | Yes            |
    +------------+--------------+------------+----------------+
    | Beanstalk  | Experimental | No         | No             |
    +------------+--------------+------------+----------------+
    | Amazon SQS | Experimental | No         | No             |
    +------------+--------------+------------+----------------+
    | Couch DB   | Experimental | No         | No             |
    +------------+--------------+------------+----------------+
    | Zookeeper  | Experimental | No         | No             |
    +------------+--------------+------------+----------------+
    | Django DB  | Experimental | No         | No             |
    +------------+--------------+------------+----------------+
    | SQLAlchemy | Experimental | No         | No             |
    +------------+--------------+------------+----------------+
    | Iron MQ    | 3rd party    | No         | No             |
    +------------+--------------+------------+----------------+



command on Arch Linux :

.. code-block:: sh

    yaourt -S rabbitmq

    sudo systemctl start rabbitmq


安裝 Celery
------------------------------

要裝 Celery 沒有什麼特別的，用 ``pip`` 就可以裝，
通常再搭配上 virtualenv 做隔離

command :

.. code-block:: sh

    pip install celery

Application
------------------------------

Celery 裝完後要做的就是先建立一個 Celery instance (Celery application)，
這個 instance 會是所有要交給 Celery 完成的事的 entry-point，
所以要讓各 modules 都可以 import

.. code-block:: python

    # proj/celery.py

    from celery import Celery

    app = Celery('proj',
                 broker='amqp://localhost:5672',    # 沒寫 port 的話會自動找 5672 port
                 backend='amqp://',
                 include=['proj.tasks'])    # include 裡面是要跑的 tasks

    # Optional configuration, see the application user guide.
    app.conf.update(
        CELERY_TASK_RESULT_EXPIRES=3600,
    )

    if __name__ == '__main__':
        app.start()


寫完 instance 後，可以開始給 task 了

.. code-block:: python

    # proj/tasks.py

    from proj.celery import app

    @app.task
    def add(x, y):
        return x + y

    @app.task
    def mul(x, y):
        return x * y

    @app.task
    def xsum(numbers):
        return sum(numbers)

啟動 Celery
------------------------------

接下來可以用 command 啟動 celery

.. code-block:: sh

    # celery -A ${app instance} worker -l info
    # 如果 -A 後面接的 folder 的話，會去找裡面的 celery.py
    # 等同於 "celery -A proj.celery worker -l info"
    # 如果在 proj 底下的 app instance 檔案叫 mycelery.py 的話
    # command 就變成 "celery -A proj.mycelery worker -l info"

    celery -A proj worker -l info

    # More Help

    celery worker --help

    celery help


啟動畫面 :

::

     -------------- celery@linux-dv v3.1.17 (Cipater)
    ---- **** -----
    --- * ***  * -- Linux-3.17.3-1-ARCH-x86_64-with-arch
    -- * - **** ---
    1. ** ---------- [config]
    2. ** ---------- .> app:         __main__:0x7fc92f14e0f0
    3. ** ---------- .> transport:   amqp://guest:**@localhost:5672//
    4. ** ---------- .> results:     amqp://
    5. *** --- * --- .> concurrency: 8 (prefork)
    -- ******* ----
    --- ***** ----- [queues]
      -------------- .> celery           exchange=celery(direct) key=celery


    [tasks]
       . proj.task.add
       . proj.task.mul
       . proj.task.xsum

開始丟 Task
------------------------------

.. code-block:: python

    from proj.tasks import add

    add(4, 5)           # 直接 call 不換產生 task 給 Celery，而是會直接做
    add.delay(4, 5)     # 用 delay 會產生 task 交給 Celery，所以是 asynchronous 的
                        # delay 其實 "apply_async" 的 shortcut
                        # add.delay(4, 5) 等同於 add.apply_async((4, 5))

    data = add.delay(8, 9)  # type(data) : celery.result.AsyncResult
    data.get(timeout=1) # 取值，等超過 1 秒還沒完成就 timeout，會 raise TimeoutError

    data.revoke(terminate=True) # 強制停止 task

強制停止 task (from outside) :

.. code-block:: python

    from celery.task.control import revoke

    # 參數一是 task id，可以從 celery 的 log 中的得知
    revoke("69511b35-dcbc-4f93-9252-e428ed8114f5", terminate=True)


保存結果
------------------------------

如果要持續監控 tasks 的狀態的話，需要把 Celery 接上 backend 來儲存，
內建的 backend 支援有很多種，
例如: SQLAlchemy、Django ORM、Memcached、Redis、AMQP (RabbitMQ)、MongoDB 等，
或者是可以自己接新的 backend。

backend 的設定在 "Celery" 的 ``backend`` argument 或是 configuration module 裡的 ``CELERY_RESULT_BACKEND``

AMQP 當 backend :

.. code-block:: python

    app = Celery('tasks', backend='amqp', broker='amqp://')

Redis 當 backend :

.. code-block:: python

    app = Celery('tasks', backend='redis://localhost', broker='amqp://')


在用 delay 來丟 task 的時候，回傳的會是一個 ``AsyncResult`` instance，
接著可以用 ``ready()`` 這個 method 來確認完成了沒。

.. code-block:: python

    result = add.delay(4, 4)    # AsyncResult
    result.ready()              # True / False

另外可以用 ``get()`` method 來一段等待時間，超過時間還沒完成就 timeout，
最後就會拿到 TimeoutError 這個 exception。

.. code-block:: python

    result.get(timeout=1)       # result value / TimeoutError exception / exception in task

如果 task 裡 raise 了 exception， ``get()`` 會再 re-raise exception，
如果不想要再 re-raise 的話，就在 get 裡加上 ``propagate=False`` 這參數，
加上這參數後，如果 task 裡 raise 了 exception 的話，
"get()" 拿到的會是 exception instance，
而不是直接 re-raise exception，
另外有 exception 的時候可以在 ``traceback`` 這個 attribute 裡看到原本的 traceback。

假設現在寫了一種新的 task :

.. code-block:: python

    # proj/tasks.py

    from proj.celery import app

    @app.task
    def exception():
        raise ValueError("just kidding")

接著在別的地方來丟出 task :

.. code-block:: python

    from proj import tasks

    result = tasks.exception.delay()

    result.get()    # exception and traceback
                    # ValueError: just kidding

    tmp = result.get(propagate=False)   # instance of ValueError
    print(tmp)          # just kidding
    print(repr(tmp))    # ValueError('just kidding',)
    isinstance(tmp, ValueError)     # True
    print(result.traceback)

Configuration
------------------------------

用預設的東西，不太別去調設定，其實就可以良好運作了。
但是 Celery 也有提供更多的設定讓使用者可以自己調整，

serializer
++++++++++++++++++++


Celery with non-Python
========================================

* https://groups.google.com/forum/#!topic/celery-users/K5i4r1rh4vU

Frequently Asked Questions
========================================

Celery 的 FAQ 的節錄 (2015-01-27)

* `Celery - Frequently Asked Questions <http://celery.readthedocs.org/en/latest/faq.html>`_

General
------------------------------

我該拿 Celery 做什麼 ?
++++++++++++++++++++++

* `Queue everything and delight everyone <http://decafbad.com/blog/2008/07/04/queue-everything-and-delight-everyone/>`_

* 把東西放在 background 跑
    - 例如 web request 盡可能地早點回傳給使用者，接著再把耗時的東西陸續傳給使用者，這會讓使用者感覺回應時間減少、performance 變好
* 在 web request 結束後跑其他額外的工作
* 確保工作有完成 (asynchronously 執行，定期檢查、重試)
* 定期執行的工作


* 分散式計算
* 平行化執行

Misconceptions
------------------------------

Celery 一定需要 pickle ?
++++++++++++++++++++++++

No.

Celery 支援各種 serialization scheme，
目前內建支援的有 JSON、YAML、Pickle、msgpack，
每個 task 要用什麼 serialization scheme 是可以分別指定的，
預設使用 pickle 是因為可以傳送複雜的 Python objects，
如果需要跟不同語言溝通的話可以選擇其他適合的 format。

Troubleshooting
------------------------------

清除所有 waiting tasks ?
++++++++++++++++++++++++

.. code-block:: sh

    celery -A proj purge

Results
------------------------------

取得某 task id 的東西
+++++++++++++++++++++

.. code-block:: python

    result = my_task.AsyncResult(task_id)
    result.get()

Security
------------------------------

用 pickle 會有 security 問題吧 ?
+++++++++++++++++++++++++++++++++

是，用 pickle 會有安全疑慮，
基本上你要確保不該有 access 權限的地方不能 access 到你的 broker、databases、other services。

可以設定 ``CELERY_TASK_SERIALIZER`` 來改變 task messages 格式成 json 或 yaml 之類的。

我想要加密
++++++++++++++++++++

對於支援 SSL 的 AMQP brokers 可以設定 ``BROKER_USE_SSL`` 來加密

Tasks
------------------------------

用名稱來 call task ?
++++++++++++++++++++

.. code-block:: python

    app.send_task('tasks.add', args=[2, 2], kwargs={})

取得 task id ?
++++++++++++++++++++

.. code-block:: python

    @app.task(bind=True)
    def mytask(self):
        cache.set(self.request.id, "Running")

我要跑連續的 task
++++++++++++++++++++

.. code-block:: python

    from celery.utils.log import get_task_logger

    logger = get_task_logger(__name__)

    @app.task
    def add(x, y):
        return x + y

    @app.task(ignore_result=True)
    def log_result(result):
        logger.info("log_result got: %r", result)


    # run task
    # 這邊注意到用的是 ".s" 而不是直接 call ".delay"
    # 詳細看 celery.canvas.Signature
    (add.s(2, 2) | log_result.s()).delay()

Reference
========================================

* `Celery <http://www.celeryproject.org/>`_
* `Celery Documentation <http://celery.readthedocs.org/en/latest/index.html>`_
* `GitHub - celery/celery <https://github.com/celery/celery>`_
* `Celery - Community Links <http://www.celeryproject.org/community/>`_
* `Celery - Frequently Asked Questions <http://celery.readthedocs.org/en/latest/faq.html>`_
* `Full Stack Python - Task Queues <http://www.fullstackpython.com/task-queues.html>`_
* `Queues - Job queues, message queues and other queues. Almost all of them in one place <http://queues.io/>`_
* `Wikipedia - Message broker <http://en.wikipedia.org/wiki/Message_broker>`_
* `Wikipedia - Celery Task Queue <http://en.wikipedia.org/wiki/Celery_Task_Queue>`_
* `Wikipedia - Advanced Message Queuing Protocol <http://en.wikipedia.org/wiki/Advanced_Message_Queuing_Protocol>`_
* `Wikipedia - Distributed computing <http://en.wikipedia.org/wiki/Distributed_computing>`_
* `Wikipedia - Parallel computing <http://en.wikipedia.org/wiki/Parallel_computing>`_
