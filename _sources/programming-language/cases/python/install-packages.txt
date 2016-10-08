========================================
Python - Install Packages
========================================

我之前在 bs2 上回應了一篇文章，
轉移到這邊來 :P


要如何安裝 Python 的第三方套件 ?
========================================

(這邊事主問的是 matplotlib)

每個作業系統的狀況不一樣，
pip 是方便的跨平台解決方案，
基本上就是 ``pip install XXX`` 打完收工 (各平台都適用)。
Python 3.4 和 Pytho 2.7.9 開始內建 pip (舊版就要額外安裝)，
不過如果直接拿來裝東西的話會需要系統權限，
通常會搭配 virtualenv 做出個 local 的隔離環境來安裝開發用的套件，
如果是作業系統是 Linux 的話，
還可以用內建的套件管理裝 (大部分的 distribution 應該都有 matplotlib)，
Mac 的話則還有 MacPorts 或 Homebrew 等解決方案。
Windows 的話就比較麻煩，
還要先把 Python 裝起來 ... (Linux 是內建會有 Python)
Windows 去裝包好的一整套工具應該比較容易 @@...
