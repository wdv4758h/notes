========================================
CPU Frequency
========================================


.. contents:: 目錄


CPU frequency driver
========================================

.. code-block:: sh

    ls /usr/lib/modules/$(uname -r)/kernel/drivers/cpufreq/


Intel CPU 可能會使用 P-state driver，
但是可以透過以下更動來關閉，
藉此切換到 acpi-cpufreq driver：

``/etc/default/grub``:

.. code-block:: conf

    GRUB_CMDLINE_LINUX_DEFAULT="... intel_pstate=disable"


使用 acpi-cpufreq driver 後，
Linux 5.10 以上會讓 schedutil 來控制速度。


看現在的機制：

.. code-block:: sh

    cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor



工具 - cpupower
========================================

.. code-block:: sh

    sudo pacman -S cpupower

    # 看現在狀態
    cpupower frequency-info
    # 設定上限
    sudo cpupower frequency-set -u 3900000
    # 設定下限
    sudo cpupower frequency-set -d 3900000
    # 設定速度
    sudo cpupower frequency-set -f 3900000



參考
========================================

* `Arch Wiki - CPU frequency scaling <https://wiki.archlinux.org/index.php/CPU_frequency_scaling>`_
