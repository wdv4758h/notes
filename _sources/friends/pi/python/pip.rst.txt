===========================
Python Package Index - PyPI
===========================

取得
-----

* Python3.4

  - ``python -m ensurepip`` (可能會需要 root 權限)
  - 從 Python3.4 開始， ``venv`` 預設會自帶 pip

* Python2

  - Fedora: ``yum -y install python-pip``
  - FreeBSD Ports: ``devel/py27-pip``

簡易使用
---------

::

  pip install --upgrade pip
  pip search pycurl
  pip install pycurl
  pip list
  pip show pycurl
  pip uninstall pycurl

進階使用
---------

* ``pip install -e {path}`` 可以把一個目錄做為 Python package 安裝，並且可以隨時修改
* [第三方] ``pipdeptree`` 可以較清楚的列出 module 間的相依關係
* ``pip list --outdated`` 可以列出可更新的 packages
