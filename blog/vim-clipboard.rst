:title: Vim - 快快貼
:slug: vim-fast-paste
:date: 2015-01-07 21:38
:modified: 2015-01-07 21:38
:category: Vim
:tags: vim
:author: wdv4758h
:summary: 在 Vim 裡快速的從 system clipboard 貼上資料

我之前在貼上大量文字進 Vim 的時候覺得有點慢，所以搜尋過如何更快速的貼上，
不過也只找到 paste mode 可以用 (應該是當時沒有打到重要的關鍵字)

paste mode 預設就有 toggle key 可以設定

.. code-block:: vim

    " use '<leader>p' to toggle paste mode
    set pastetoggle=<leader>p

或是手動用 ``:set paste`` 來進入 paste mode， ``:set nopaste`` 來離開 paste mode

今天終於找到了我想要的解法，直接從 system clipboard 拿資料，
而不是由 terminal 去慢慢模擬輸入 ...

這邊要用到 Vim 裡的 register，
在 Vim 裡面對應到外面 Linux 的 clipboard 的 register 是 ``+`` ，
所以可以從這裡面快速的拿到資料

方法 1 : 在 insert mode 快速貼上
========================================

在 insert mode 裡面可以用 ``Ctrl+R`` 來 access Vim 的 register，
內容會直接輸入，所以可以使用 ``Ctrl+R`` + ``+`` 來快速的輸入 clipboard 裡的東西

方法 2 : 在 normal mode 快速貼上
========================================

在 normal mode 裡面可以用 ``"`` 來 access Vim 的 register，
所以可以使用 ``"`` + ``+`` + ``p`` 來快速的貼上 clipboard 裡的東西

方便起見，當然還是 map 到某個 key 上面，這樣就可以快速的使用了，
目前我是把自己之前用在 paste mode toggle 的 ``<leader>p`` map 成了 ``"+p`` ，
想說我如果想切到 paste mode 通常也就是我要從外面貼東西進來，
乾脆就直接換成這個快速貼上 ~

先使用一陣子看看，如果真的不習慣再換囉 ~

其他應用 - 從 Vim 裡複製到 system clipboard
===========================================

在 visual mode 或是 visual block mode 裡面可以也可以用 ``"`` 來 access Vim 的 register，
所以可以先選取想要複製的區塊，
接著用 ``"`` + ``+`` + ``y`` 來複製資料到 clipboard 裡 ~~~

然後就可以在其他程式裡快樂的貼上了 ~ ya ~

其他 Vim registers
========================================

想知道其他更多 Vim 裡的 registers 的資料可以下 ``:reg`` ，
更多資訊可以 Vim 的 manual

參考資料
========================================

* `StackOverflow - How to paste text into Vim command line <http://stackoverflow.com/questions/3997078/how-to-paste-text-into-vim-command-line>`_
    - 回應很豐富
* `Vim Tips wiki - In line copy and paste to system clipboard <http://vim.wikia.com/wiki/In_line_copy_and_paste_to_system_clipboard>`_
* `Vim Tips wiki - Accessing the system clipboard <http://vim.wikia.com/wiki/Accessing_the_system_clipboard>`_
