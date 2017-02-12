:title: neovim first try
:slug: neovim-first-try
:date: 2014-12-12 20:26
:modified: 2014-12-12 20:26
:category: Vim
:tags: Vim
:author: wdv4758h
:summary: neovim first try

Vim is a wonderful editor which appears long long ago.
Now, a project called Neovim wants to refactor Vim and simplify maintenance and improve plugin architecture and many thing else. It's making progress now, you can see `Neovim - Progress - GitHub wiki <https://github.com/neovim/neovim/wiki/Progress>`_ for more information.

Today, I install neovim on my computer, and it seems to work fine as original Vim (with a lots of change that user hard to detect)

Now, Neovim is working on port all IO to libuv and a VimL to Lua transpiler.
I hope another language will replace the Vimscript soon ...

`The Neovim Website <http://neovim.org/>`_

`Neovim - GitHub <https://github.com/neovim/neovim>`_

Install
========================================

I install it on my Arch Linux

.. code-block:: sh

    yaourt -S neovim-git python2-neovim-git

After installation, you can use ``nvim`` to start neovim, and the config is ``.nvimrc``
