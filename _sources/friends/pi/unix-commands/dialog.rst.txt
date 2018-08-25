==========
``dialog``
==========
紀錄一些 ``dialog`` programming snippet

* 普通的 message box，長寬為 (20, 50)

  .. code:: sh

    dialog --title 'Title' --msgbox 'Hello world' 20 50

* 產生 menu 並取得使用者選擇的選項

  .. code:: sh

    items="option1 option2 option3"

    items=$(echo "$items" | tr ' ' '\n')
    b=$(echo "$items" | nl)
    selection=$(dialog --menu "Description" 20 50 50 $b 3>&1 1>&2 2>&3)
    if [ $? -eq 0 ]; then
        selection=$(echo "$items" | head -n ${selection} | tail -n 1)
        echo ${selection}
    fi

  - 註： ``echo $items`` 會把換行字元破壞掉， ``echo "$items"`` 則不會

* 產生 inputbox 並取得使用者輸入的字串

  .. code:: sh

    user_input=$(dialog --inputbox "Description" 20 50 "initial text" 3>&1 1>&2 2>&3)
    if [ $? -eq 0 ]; then
        echo ${user_input}
    fi

* 產生進度條

  .. code:: sh

    (for i in $(seq 1 100); do
        echo $i
        sleep 0.01
    done) | dialog --title Title --gauge text 20 50

  - 實際測試，在 FreeBSD 上 ``gauge`` 需要搭配 ``--title`` 選項，否則會 core dump
