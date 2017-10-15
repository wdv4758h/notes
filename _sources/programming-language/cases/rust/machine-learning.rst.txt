========================================
機器學習 (Machine Learning)
========================================


.. contents:: 目錄


Leaf - The Hacker's Machine Intelligence Platform
=================================================

:Repo: https://github.com/autumnai
:Repo(cont.): https://github.com/spearow


.. image:: /images/rust/autumn-platform.png


Leaf 是 Autumn 所實做的 framework，
在其之下還有叫做 Collenchyma 的 framework 負責把各種運算方式抽象化成統一界面。
Autumn 公司後來收掉了，但是所有專案都 Open Source，
後續也有人在其之上開發，
目前還在持續開發的 fork 為 Juice （整合了一些其他人的更改，例如 Parenchyma）。


* Collenchyma: Extendable HPC-Framework for CUDA, OpenCL and common CPU
    - https://github.com/autumnai/collenchyma
    - https://github.com/spearow/coaster
* Leaf: Open Machine Intelligence Framework for Hackers
    - https://github.com/autumnai/leaf
    - https://github.com/spearow/juice
* Cuticula: Machine Intelligence Preprocessing Framework
    - https://github.com/autumnai/cuticula
    - https://github.com/spearow/greenglas



Weld -  High-performance runtime for data analytics
===================================================

:Site: http://weld.stanford.edu/
:Repo: https://github.com/weld-project/weld


Weld 是 Stanford 開發的一套 runtime，
目的是要提昇資料科學上一些套件的效能，
處理上會針對整個處理流程做優化，
而不是針對單一操作做優化，
目前已經可以整合 Python 的 Pandas 其中的子集。


論文：

* `Weld: Rethinking the Interface Between Data-Intensive Applications <https://arxiv.org/abs/1709.06416>`_

文章：

* `Implementing Weld in Rust <http://dawn.cs.stanford.edu/2017/04/25/weld/>`_



參考
========================================

* `Are we learning yet? <http://www.arewelearningyet.com/>`_
