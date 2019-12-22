========================================
Plugins Manager
========================================


.. contents:: 目錄


介紹
========================================

* autoload
* plugged



常見的 Plugins Manager
========================================

* Vundle
* Pathogen
* Neobundle
* VAM
* Vim-plug
* Dein



如何製作 Plugins Manager
========================================



如何製作 Plugin
========================================

* `NeoVim - Remote Plugin <https://neovim.io/doc/user/remote_plugin.html>`_
    - JSON RPC


Python
------------------------------

最小需求：

1. 專案裡提供 ``rplugin/python3/myplugin.py``
2. 在 NeoVim 裡執行 ``:UpdateRemotePlugins``
3. 呼叫對應的名稱 ``:call PyHello()``


.. code-block:: python

    # rplugin/python3/myplugin.py

    import pynvim

    @pynvim.plugin
    class MyPlugin:
        def __init__(self, vim):
            self.vim = vim

        @pynvim.function('PyHello')
        def hello(self, args):
            self.vim.command('echo "hello from python remote plugin"')



參考
========================================
