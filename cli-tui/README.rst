========================================
CLI/TUI 工具
========================================


.. contents:: 目錄


簡表
========================================

* Shell
    - Bourne shell
    - tcsh
    - `Bash <bash.rst>`_
    - zsh
    - ⭐ fish
* 產生程式碼相關的函式、變數等等資訊的列表
    - ⭐ `universal ctags <https://ctags.io/>`_
    - ⭐ `ptags - parallel universal ctags <https://github.com/dalance/ptags>`_
* 字串搜尋
    - grep
    - ⭐ ripgrep
* 檔案搜尋
    - find
    - ⭐ fd
* 檔案搜尋加字串取代
    - find/sed
    - fd/sed
    - ⭐ amber
* Binary 搜尋
    - `bingrep <https://github.com/m4b/bingrep>`_
* 搜尋引擎
    - `Tantivy <https://github.com/tantivy-search/tantivy>`_
* 字串取代
    - sed
    - `fastmod <https://github.com/facebookincubator/fastmod>`_
    - ⭐ `amber <https://github.com/dalance/amber>`_
* 以十六進位輸出 Binary
    - xxd
    - hexdump
    - ⭐ `hex <https://github.com/sitkevij/hex>`_
* 讀檔案內容
    - cat
    - `bat <https://github.com/sharkdp/bat>`_
* 檔案系統
    - `du <du.rst>`_
    - df
    - ⭐ dutree
* 系統監控
    - top
    - ⭐ htop
    - ⭐ dmesg
        + ``dmesg -T`` 使用人類可讀的時間，而不是以開機時間為基準
* 壓縮、解壓縮
    - pixz
    - pigz
* 時間
    - `date <date.rst>`_
    - `timedatectl <timedatectl.rst>`_
* 硬體時間
    - `hwclock <hwclock.rst>`_
* 檔案類別偵測
    - `file <file.rst>`_
* 檔案下載
    - `curl <curl.rst>`_
    - wget
    - HTTPie
* 指令文件、範例
    - ⭐ man
    - ⭐ tldr
* pager
    - less
    - more
    - head
    - tail
        + tail -f
* SSH server/client
    - OpenSSH
    - dropbear
* 編輯器
    - vim
    - ⭐ neovim
    - emacs
    - pyvim
    - busybox vi
* session persistence
    - dtach
    - screen
    - ⭐ tmux
    - pymux
* 平行化
    - GNU parallel
    - `Rust parallel <https://github.com/mmstick/parallel>`_
* 去除整行重複的內容
    - uniq
    - ⭐ runiq
* 指令效能測量
    - GNU time
    - ⭐ hyperfine
* 列出檔案和資料夾
    - ls
    - exa
    - `lsd <https://github.com/Peltoche/lsd>`_
* Terminal Emulator
    - xterm
    - urxvt
    - GNOME Terminal
    - Terminator
    - Guake
    - Kconsole
    - LXTerminal
    - `alacritty <https://github.com/jwilm/alacritty/>`_
    - `kitty <https://sw.kovidgoyal.net/kitty/>`_
* 圖片優化
    - oxipng
* fuzzy finder
    - `fzf <https://github.com/junegunn/fzf>`_
* JSON 處理工具
    - jq
    - jid
    - jiq
* JavaScript bundler
    - `pax <https://github.com/nathan/pax>`_
* misc
    - rfkill
        + rfkill unblock bluetooth
    - lspci
        + -k
    - hciconfig
    - hcitool scan
    - bluetoothctl
    - xargs
    - netcat
    - readelf
    - rsync
    - lsof
    - sort
    - ps
    - cut
    - join
    - wc
    - tee
    - nohup
    - timeout
    - yes
    - env
    - dd
    - tree
    - time
    - lockfile
    - logrotate
    - watch
    - iconv
    - ldd
    - strace
    - awk
    - sudo
    - `busybox <busybox.rst>`_



參考
========================================

* `The Art of Command Line <https://github.com/jlevy/the-art-of-command-line>`_
