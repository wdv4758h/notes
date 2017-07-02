當要看系統上的 process 資訊時, 有 ps 可以看靜態的資料(snapshot), 有 top/htop 可以看動態的資料.

- Linux: ps auxww
- FreeBSD: ps -auxww

Thread 資訊
-----------
ps in Linux:

- ps 顯示 thread

  - ps -eLf

- thread 相關欄位

  - LWP: thread id, 類似 process id. LWP 為 light weight process 的縮寫
  - NLWP: 該 process 有幾個 thread

.. image:: linux_psthread.png

- example: 4 thread in 1 process

  - NLWP: 4
  - PID: 523
  - LWP: 523, 544, 555, 556 

.. image:: linux_psthread_ex1.png

ps in FreeBSD:

- ps 顯示 thread

  - ps -H[auxww]

- thread 相關欄位

  - LWP, NLWP

- ps 顯示 thread 相關欄位 (-u + LWP/NLWP)

  - ps -Haxww -o "user, pid, lwp, nlwp %cpu, %mem, vsz, rss, tt, state, start, time, command"

.. image:: bsd_psthread.png

htop:

- -H/-K: 顯示/隱藏 user/kernel thread
- 隱藏(可從上方標示看出)

.. image:: htop_hide_thread.png

- 顯示(可從上方標示看出)

.. image:: htop_show_thread.png

