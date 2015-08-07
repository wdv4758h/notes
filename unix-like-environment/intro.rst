========================================
Some Basic Tools
========================================

OpenSSH & Mosh
========================================

OpenSSH
------------------------------

OpenSSH 全名叫「OpenBSD Secure Shell」，
專案始於 1999 年 12 月 1 日，
目的是要開發 SSH 實作的 Open Source 替代方案
(當時常見的為 Tatu Ylönen 開發由 SSH Communications Security 釋出的非開源實作)，
原本單純只是 OpenBSD 的計劃，
後續發展成為 Unix-like 平台中最常見、最多人使用的 SSH 實作。

OpenSSH 不是一個單一的程式，
而是一套相關的程式集合，
包含以下程式：

* ssh
* scp
* sftp
* sshd
* ssh-keygen
* ssh-add
* ssh-agent
* ssh-keyscan
* ssh-copy-id

Mosh
------------------------------

Mosh 全名叫「mobile shell」，
專案始於 2012 年，
目的是要提供在網路品質不佳的情況下仍能運作的 SSH 實作，
一般的 SSH 在一定時間內沒有送封包維持連線後就會斷線，
這對於網路品質不佳的狀況下會造成使用不易，
而 Mosh 則嘗試解決了這個問題，
在 Server 端會跑一隻 Mosh server，
之後無論是中途斷線或是換 IP，
只要是你那個 Mosh client 連的，
連線就可以繼續維持，
斷線、換 IP 都不用重連，
網路連上後連線就自動恢復，
方便性提升非常多。

Reference
------------------------------

* `Wikipedia - OpenSSH <https://en.wikipedia.org/wiki/OpenSSH>`_
* `Wikipedia - Mosh (software) <https://en.wikipedia.org/wiki/Mosh_%28software%29>`_
* `Mosh: the mobile shell <https://mosh.mit.edu/>`_
