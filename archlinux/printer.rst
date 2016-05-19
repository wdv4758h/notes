========================================
Printer
========================================


安裝和使用
========================================

.. code-block:: sh

    # 檢查印表機的 Port 有沒有通
    $ nmap 192.168.0.13
    Starting Nmap 7.12 ( https://nmap.org ) at 2016-05-16 16:26 CST
    Nmap scan report for MYPRINTER (192.168.0.13)
    Host is up (0.0053s latency).
    Not shown: 996 closed ports
    PORT     STATE SERVICE
    21/tcp   open  ftp
    80/tcp   open  http
    515/tcp  open  printer      # !
    9100/tcp open  jetdirect    # !

    Nmap done: 1 IP address (1 host up) scanned in 2.59 seconds

.. code-block:: sh

    # 增加新印表機
    # 印表機 Model 可能會在 /usr/share/cups/model
    # 需要指定對應的 PPD 檔
    sudo lpadmin -p cv -v socket:://192.168.0.13:9100 -m MODEL -E

    # 設成預設印表機
    sudo lpadmin -d cv

    # 刪除印表機
    sudo lpadmin -x cv

    # 查看印表機狀況
    lpstat -a
    lpstat -s
    lpstat -p
    lpstat -t

    # 查看本機的未完成列印 Queue
    lpstat -o

    # 從列印 Queue 中刪除工作
    cancel {printerjobid}

    # 刪除整個列印 Queue
    sudo cancel -a -x

    # 列出系統上的印表機 Driver
    lpinfo -m

    # 列印檔案
    lpr FILE


Reference
========================================

* `Arch Wiki - CUPS <https://wiki.archlinux.org/index.php/CUPS>`_
* `鳥哥的 Linux 私房菜 -- 第二十一章、系統設定工具(網路與印表機)與硬體偵測 <http://linux.vbird.org/linux_basic/0610hardware/0610hardware-centos5.php#cups>`_
