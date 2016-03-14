========================================
Performance Tuning For Server
========================================

.. contents:: Table of Contents


Know Your System
========================================

.. code-block:: sh

    git clone https://github.com/ryran/xsos
    xsos/xsos -a >> machine # run with root
    cat machine


Close Services
========================================

.. code-block:: sh

    systemctl --state=running   # 檢查目前有哪些正在跑的 services，關閉不需要的
    systemd-analyze blame       # 檢查開機時跑了哪些東西，各花了多少時間


CPU Frequency Scaling
========================================

.. code-block:: sh

    sudo pacman -S cpupower
    cpupower frequency-info

    ########################################
    # sample 1
    ########################################
    #
    # analyzing CPU 0:
    #   driver: acpi-cpufreq
    #   CPUs which run at the same hardware frequency: 0
    #   CPUs which need to have their frequency coordinated by software: 0
    #   maximum transition latency: 10.0 us.
    #   hardware limits: 2.00 GHz - 2.67 GHz
    #   available frequency steps: 2.67 GHz, 2.00 GHz
    #   available cpufreq governors: conservative, userspace, powersave, ondemand, performance
    #   current policy: frequency should be within 2.66 GHz and 2.67 GHz.
    #                   The governor "conservative" may decide which speed to use
    #                   within this range.
    #   current CPU frequency is 2.67 GHz (asserted by call to hardware).
    #   boost state support:
    #     Supported: no
    #     Active: no

    ########################################
    # sample 2
    ########################################
    #
    # analyzing CPU 0:
    #   driver: intel_pstate
    #   CPUs which run at the same hardware frequency: 0
    #   CPUs which need to have their frequency coordinated by software: 0
    #   maximum transition latency: 0.97 ms.
    #   hardware limits: 1.20 GHz - 3.10 GHz
    #   available cpufreq governors: performance, powersave
    #   current policy: frequency should be within 1.20 GHz and 3.10 GHz.
    #                   The governor "powersave" may decide which speed to use
    #                   within this range.
    #   current CPU frequency is 1.54 GHz.
    #   boost state support:
    #     Supported: yes
    #     Active: yes
    #     25500 MHz max turbo 4 active cores
    #     25500 MHz max turbo 3 active cores
    #     25500 MHz max turbo 2 active cores
    #     25500 MHz max turbo 1 active cores

    cpupower frequency-set -u 2.67GHz   # 設上限
    cpupower frequency-set -d 2.66GHz   # 設下限
    cpupower frequency-set -f 2.67GHz   # 設運轉速度


Arch Build System
========================================

針對自己的硬體來編譯系統上的軟體
(開更多編譯器優化參數)

``/etc/makepkg.conf`` :

    CC="clang"
    CXX="clang++"
    CFLAGS="-std=c11 -Wall -Wextra -pedantic -O3 -march=native -flto -pipe"
    CXXFLAGS="-std=c++14 -Wall -Wextra -pedantic -O3 -march=native -flto -pipe"
    LDFLAGS="-s -Wl,-O1,--sort-common,--as-needed,-z,relro" # -Wl, for linker options


.. code-block::

    sudo pacman -S abs
    sudo abs    # 更新 ABS tree (/var/abs)
    sudo abs <repository>/<package>     # 更新 ABS tree 中特定的 package

    cp -r /var/abs/extra/python/ python
    cd python
    makepkg -s  # -s 來自動處理 build dependency


Linux Kernel
========================================

config :

+-----------------+----------------+---------------------------------------------+
| Tickless System | CONFIG_NO_HZ=y | fewer timer interrupts and context switches |
+-----------------+----------------+---------------------------------------------+

Network
========================================

.. code-block:: sh

    sudo pacman -S ethtool
    ethtool -k ens32
    # Features for ens32:
    # rx-checksumming: off
    # tx-checksumming: on
    # 	tx-checksum-ipv4: off [fixed]
    # 	tx-checksum-ip-generic: on
    # 	tx-checksum-ipv6: off [fixed]
    # 	tx-checksum-fcoe-crc: off [fixed]
    # 	tx-checksum-sctp: off [fixed]
    # scatter-gather: on
    # 	tx-scatter-gather: on
    # 	tx-scatter-gather-fraglist: off [fixed]
    # tcp-segmentation-offload: on
    # 	tx-tcp-segmentation: on
    # 	tx-tcp-ecn-segmentation: off [fixed]
    # 	tx-tcp6-segmentation: off [fixed]
    # udp-fragmentation-offload: off [fixed]
    # generic-segmentation-offload: on
    # generic-receive-offload: on
    # large-receive-offload: off [fixed]
    # rx-vlan-offload: on
    # tx-vlan-offload: on [fixed]
    # ntuple-filters: off [fixed]
    # receive-hashing: off [fixed]
    # highdma: off [fixed]
    # rx-vlan-filter: on [fixed]
    # vlan-challenged: off [fixed]
    # tx-lockless: off [fixed]
    # netns-local: off [fixed]
    # tx-gso-robust: off [fixed]
    # tx-fcoe-segmentation: off [fixed]
    # tx-gre-segmentation: off [fixed]
    # tx-ipip-segmentation: off [fixed]
    # tx-sit-segmentation: off [fixed]
    # tx-udp_tnl-segmentation: off [fixed]
    # fcoe-mtu: off [fixed]
    # tx-nocache-copy: off
    # loopback: off [fixed]
    # rx-fcs: off
    # rx-all: off
    # tx-vlan-stag-hw-insert: off [fixed]
    # rx-vlan-stag-hw-parse: off [fixed]
    # rx-vlan-stag-filter: off [fixed]
    # l2-fwd-offload: off [fixed]
    # busy-poll: off [fixed]

    sudo ethtool -K ens32 tso on

GPU
========================================

.. code-block:: sh

    sudo pacman -S cuda

gpucc


Reference
========================================

* `Arch Wiki - Maximizing performance <https://wiki.archlinux.org/index.php/maximizing_performance>`_
* `Arch Wiki - Arch Build System <https://wiki.archlinux.org/index.php/Arch_Build_System>`_
