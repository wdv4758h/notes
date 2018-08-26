========================================
ChatOps
========================================


.. contents:: 目錄


介紹
========================================

ChatOps 是指 DevOps 以聊天室作為媒介來達成目的，
藉由在聊天室掛上特定的聊天機器人，
在討論的過程中呼叫機器人去做對應的事情，
藉此達到自動化和透明化，
可以明確地看到誰更動了什麼以及現在的狀況。



實際案例
========================================

GitHub 公司
------------------------------

* [2013] `ChatOps at GitHub <https://speakerdeck.com/jnewland/chatops-at-github>`_
* `Hubot <https://hubot.github.com/>`_
* [GitHub] `Hubot <https://github.com/github/hubot>`_


Rust 在 GitHub 上的使用
------------------------------

Rust 團隊在 GitHub 上掛有數個機器人，
當送出 Pull Request 時，
會有 ``highfive`` 機器人指定 Reviewer，
在 Reviewer 確認過後會呼叫 ``bors`` 機器人進行全面的測試，
測試完後會回報結果，
當測試都通過時才會安排 Merge 進 master。



參考
========================================

* `Awesome ChatOps <https://github.com/exAspArk/awesome-chatops>`_
* `Cog + ChatOps = Continuous DevOps <https://operable.io/>`_
* `Wikipedia - DevOps <https://en.wikipedia.org/wiki/DevOps>`_
* [GitHub] `Errbot <https://github.com/errbotio/errbot/>`_
* [GitHub] `Homu <https://github.com/servo/homu>`_
