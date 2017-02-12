:title: Vim startup time log
:slug: vim-startup-time-log
:date: 2014-12-23 23:10
:modified: 2014-12-23 23:10
:category: Vim
:tags: Vim
:author: wdv4758h
:summary: vim log ~~~

原本是在找 vim 啟動時間相關的資料，找到了 `這個網站 <http://usevim.com/2012/04/18/startuptime/>`_ ，
發現有 ``--startuptime`` 這個參數可以用，於是就立馬來試一下，

.. code-block:: sh

    vim --startuptime vim.log test.py

接著就可以去 ``vim.log`` 看整個啟動狀況

::

    times in msec
     clock   self+sourced   self:  sourced script
     clock   elapsed:              other lines

    000.013  000.013: --- VIM STARTING ---
    000.142  000.129: Allocated generic buffers
    000.277  000.135: locale set
    000.305  000.028: GUI prepared
    000.313  000.008: clipboard setup
    000.321  000.008: window checked
    000.881  000.560: inits 1
    000.888  000.007: parsing arguments
    000.889  000.001: expanding arguments
    000.903  000.014: shell init
    001.163  000.260: Termcap init
    001.214  000.051: inits 2
    001.356  000.142: init highlight
    042.935  041.473  041.473: sourcing /usr/share/vim/vimfiles/archlinux.vim
    043.008  041.604  000.131: sourcing /etc/vimrc
    044.222  000.267  000.267: sourcing /usr/share/vim/vim74/syntax/syncolor.vim
    044.368  000.480  000.213: sourcing /usr/share/vim/vim74/syntax/synload.vim
    067.980  023.555  023.555: sourcing /usr/share/vim/vim74/filetype.vim
    068.028  024.211  000.176: sourcing /usr/share/vim/vim74/syntax/syntax.vim
    ...
    161.306  000.881: loading plugins
    161.907  000.601: inits 3
    162.125  000.218: reading viminfo
    163.820  001.695: setup clipboard
    163.846  000.026: setting raw mode
    163.855  000.009: start termcap
    163.876  000.021: clearing screen
    ...
    185.539  000.358: BufEnter autocommands
    185.541  000.002: editing files in windows
    190.308  004.767: VimEnter autocommands
    190.311  000.003: before starting main loop
    190.445  000.134: first screen update
    190.447  000.002: --- VIM STARTED ---

manual in Vim : ``:help slow-start``

這個 log 參數剛好拿來解掉一個朋友碰到的問題 ~

他在用 ``mosh`` 連到某台機器上開 vim 時會 hang 住，
藉由這個 log，發現是卡在 clipboard 那裡，
原因是因為程式嘗試和 X server connect，但一直連不到，
接著就找到了解法 ``vim -X``

詳細問題解法可以看 `這篇 stackoverflow <stackoverflow.com/questions/14635295/vim-takes-a-very-long-time-to-start-up>`_ 回答
