========================================
SSH Config
========================================


.. contents:: 目錄


介紹
========================================

我們可以在 ``~/.ssh/confg`` 內設定機器的資訊，
如此一來就可以更方便的使用 SSH。



一般設定
========================================

使用密碼：

.. code-block:: sshconfig

    Host machine1
        HostName machine1.mydomain.com
        Port 7788   # default is 22
        User username


使用 Key：

.. code-block:: sshconfig

    Host machine1
        HostName machine1.mydomain.com
        User username
        Port 7788   # default is 22
        IdentityFile ~/.ssh/machine   # your private key



SOCKS5 Proxy
========================================

.. code-block:: sshconfig

    Host machine1
        HostName machine1.mydomain.com
        User username
        Port 7788   # default is 22
        DynamicForward 1234   # proxy at localhost port 1234
        IdentityFile ~/.ssh/machine   # your private key



Jump Host
========================================

.. code-block:: sshconfig

    Host machine1
        HostName machine1.mydomain.com
        User username
        IdentityFile ~/.ssh/machine

    # machine1 -> machine2
    Host machine2
        HostName machine2.mydomain.com
        ProxyJump machine1

    # machine1 -> machine2 -> machine3
    Host machine3
        HostName machine3.mydomain.com
        ProxyJump machine2



參考
========================================

* `Gentoo Wiki - SSH jump host <https://wiki.gentoo.org/wiki/SSH_jump_host>`_
