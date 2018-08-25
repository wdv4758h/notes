===============================================================================
bash completion
===============================================================================
和 zsh 相比，bash 的 completion 容易許多，當然也會有一些限制。

一個簡單的例子：

.. code:: sh

    _foo () {
        COMPREPLY=(foo bar baz)
    }

    complete -F _foo foo

以上的例子實作了 ``foo`` 指令的 completion，選單內容為 ``bar`` ``baz`` ``foo`` 。

註: bash 預設會對選項排序。

在 completion function 裡面，還有一些工具可以幫忙：

* ``${COMP_CWORD}`` - 現在正在補完的是第幾個字（數字）

  - 每個字可以有不同的補完邏輯
  - ``${COMP_WORDS[COMP_CWORD]}`` 為游標所在的字

* ``compgen`` 指令 - 字串比對工具，從選項中過濾出特定開頭的字

  - 基本形式： ``compgen -W "<options>" -- "<word>"``
  - 範例：

    ..  code:: shell

        $ compgen -W "apple banana blueberry cookie" -- "b"
        banana
        blueberry

  - ``compgen`` 還有 ``-S <suffix>`` 和 ``-P <prefix>`` 可以用

* ``IFS`` - 選項的分隔符號

  - ``compgen`` 在判斷時需要這個值來切分 ``<options>``
  - 預設為空白字元


進階範例
-------------------------------------------------------------------------------
這個範例在 bash 中實作了有 description 的 completion menu。

關鍵在於把 description 當成選項的一部份，並且在只剩下一個選項的時候把 description 去除。

.. code:: sh

    _foo () {
        opts="apple - red
    banana - yellow
    blueberry - blue
    cookie - hey it's not a fruit!"

        local OLDIFS="$IFS"
        local IFS=$'\n'
        COMPREPLY=($(compgen -W "${opts}" -- "${COMP_WORDS[COMP_CWORD]}"))
        IFS="$OLDIFS"
        if [[ ${#COMPREPLY[*]} -eq 1 ]]; then #Only one completion
            COMPREPLY=( ${COMPREPLY[0]%% - *} ) #Remove ' - ' and everything after
        fi
    }

    complete -F _foo foo

可能需要搭配 ``.inputrc`` 的設定，強制讓 completion menu 只有一個 column： ::

  set completion-display-width 1


參考資料
-------------------------------------------------------------------------------
* https://debian-administration.org/article/316/An_introduction_to_bash_completion_part_1
* https://debian-administration.org/article/317/An_introduction_to_bash_completion_part_2
* http://stackoverflow.com/questions/7267185/bash-autocompletion-add-description-for-possible-completions/10130007#10130007
