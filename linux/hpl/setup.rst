========================================
Performance Tuning For HPL
========================================

.. contents:: Table of Contents


OS Installation
========================================

.. code-block:: sh

    ########################################
    # Install Scientific Linux
    # mininal with "Development Tools"
    ########################################

    # make USB installer
    wget http://ftp1.scientificlinux.org/linux/scientific/7x/x86_64/iso/SL-7.2-x86_64-netinst.iso
    sudo dd if=./SL-7.2-x86_64-netinst.iso of=/dev/sdb bs=4M status=progress

    # run installer ...


Basic Setting
========================================

.. code-block:: sh

    # SELINUX=disable
    sed -i "s/^SELINUX=.*/SELINUX=disabled/" /etc/sysconfig/selinux

    # SSH
    sed -i '1s/^/ALL: ALL: ALLOW\n/' /etc/hosts.allow
    systemctl enable sshd
    systemctl start sshd

    # Change SSH Port

    # Packages
    yum install -y yum-plugin-fastestmirror
    cp -r /etc/yum.repos.d/ /etc/yum.repos.d.bak/
    sed -i 's/#mirrorlist/mirrorlist/g' /etc/yum.repos.d/*
    yum update -y


Other Packages - RPMforge
========================================

.. code-block:: sh

    rpm --import http://apt.sw.be/RPM-GPG-KEY.dag.txt
    rpm -ivh http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm

    # install tools
    yum install gcc-c++ -y  # provide some files for later use ... (ICC)
    yum install vim -y
    yum install htop wget net-tools -y


Disable Services
========================================

.. code-block:: sh

    systemctl stop NetworkManager
    systemctl disable NetworkManager

    systemctl stop postfix
    systemctl disable postfix

    systemctl stop firewalld.service
    systemctl disable firewalld.service

    systemctl stop crond
    systemctl disable crond

    systemctl stop rsyslog
    systemctl disable rsyslog

    systemctl stop lvm2-monitor
    systemctl disable lvm2-monitor

    systemctl stop yum-cron
    systemctl disable yum-cron

    systemctl stop crond
    systemctl disable crond

    systemctl disable auditd
    systemctl disable plymouth-start


System Information
========================================

.. code-block:: sh

    yum install -y git
    yum install -y bridge-utils     # for brctl
    yum install -y pciutils         # for lspci

    # SELinux status
    sestatus >> machine.status

    # Services
    systemctl --state=running >> machine.status
    systemd-analyze blame >> machine.status

    # instantly summarize system info
    git clone https://github.com/ryran/xsos
    xsos/xsos -a >> machine.status  # run with root


HPL
========================================

.. code-block:: sh

    # HPL from netlib

    wget http://www.netlib.org/benchmark/hpl/hpl-2.2.tar.gz
    tar xvf hpl-*.tar.gz
    mv hpl-* hpl    # need this to make HPL Makefile happy ...
    cd hpl
    cp setup/Make.Linux_Intel64 ./
    make arch=Linux_Intel64
    cd ..

    # HPL from Intel

    cd /opt/intel/mkl/benchmarks/mp_linpack/
    make arch=intel64
    cd bin/intel64/

    # run HPL
    # /opt/intel/impi/5.0.3.048/bin64/mpirun -np 8 /opt/intel/mkl/benchmarks/mp_linpack/bin/intel64/xhpl
    # /opt/intel/impi/5.1.3.181/bin64/mpirun -np 8 /opt/intel/mkl/benchmarks/mp_linpack/bin_intel/intel64/xhpl_intel64
    # HPL.dat 要放在現在所在的目錄

    # method 1
    mpirun -np 8 `pwd`/xhpl

    # method 2
    mpdboot
    mpdtrace
    mpiexec -n 8 `pwd`/xhpl


Intel ICC, Cluster Edition
========================================

.. code-block:: sh

    tar xvf parallel_studio_xe_2016_update2.tgz
    ./parallel_studio_xe_2016_update2/install.sh

    echo "Red Hat Enterprise Linux release 7" > /etc/redhat-release

    source /opt/intel/bin/compilervars.sh intel64
    source /opt/intel/impi/*/bin64/mpivars.sh

    export CC=icc CXX=icpc LD=xild AR=xiar
    export CFLAGS="-O3 -xHost" CXXFLAGS="-O3 -xHost"
    export LD_LIBRARY_PATH=/opt/intel/lib/intel64:/opt/intel/mkl/lib/intel64/:/opt/intel/compilers_and_libraries/linux/mpi/intel64/lib/:$LD_LIBRARY_PATH


CUDA
========================================

.. code-block:: sh

    export PATH=/usr/local/cuda-7.0/bin:$PATH


Linux Kernel
========================================

.. code-block:: sh

    export KERNEL_VERSION="4.5"

    # http://www.devops-blog.net/linux-tweaks/compiling-your-own-kernel-for-debian-and-centos-or-alike
    # RHEL / Fedora / CentOS
    yum groupinstall -y "Development Tools"
    yum install -y ncurses ncurses-devel

    # fetch kernel source
    wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-${KERNEL_VERSION}.tar.xz
    tar xJf linux-${KERNEL_VERSION}.tar.xz
    cd linux-*/

    # cleanup
    make mrproper
    make clean

    # copy current kernel config as a base to use. Note: 'make mrproper' deletes .config
    cp ${MY_KERNEL_CONFIG} .config
    # get local config :
    # make localyesconfig

    # edit config and save
    # http://www.linux.org/threads/the-linux-kernel-configuring-the-kernel-part-2.4318/
    make menuconfig

    # ``CONFIG_HZ`` : 100 Hz
    # ``PREEPT`` : Server
    # ``NUMA``

    # build kernel
    # RHEL / Fedora / CentOS
    make -j rpm

    # install kernel after build
    rpm -ivh /root/rpmbuild/RPMS/x86_64/kernel-${KERNEL_VERSION}-*.x86_64.rpm

    # RHEL / Fedora / CentOS
    mkinitrd initramfs-${KERNEL_VERSION}.img ${KERNEL_VERSION}
    grubby --add-kernel=/boot/vmlinuz-${KERNEL_VERSION} --initrd=/boot/initramfs-${KERNEL_VERSION}.img --title=${KERNEL_VERSION} --make-default --copy-default
    grep ^menuentry /etc/grub2.cfg | cut -d "'" -f2
    grub2-set-default "Scientific Linux (4.4.4) 7.2 (Nitrogen)"
    grub2-mkconfig -o /etc/grub2.cfg
    # check /etc/grub.conf and modify kernel flags if necessary


Set CPU Frequency
========================================

.. code-block:: sh

    # https://wiki.archlinux.org/index.php/CPU_frequency_scaling

    # SL:
    #   /usr/lib/systemd/system/cpupower.service
    #   /etc/sysconfig/cpupower

    cpupower frequency-info
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

    export MAX_CPU_FREQ=`cpupower frequency-info | grep 'hardware limits' | cut -d '-' -f2 | tr -d ' '`
    export MIN_CPU_FREQ=`python -c "n='${MAX_CPU_FREQ}'; print('{}{}{}'.format(n[:-4], int(n[-4])-1, n[-3:]))"`

    cpupower frequency-set -g performance
    cpupower frequency-set -u ${MAX_CPU_FREQ}   # 設上限
    cpupower frequency-set -d ${MIN_CPU_FREQ}   # 設下限
    cpupower frequency-set -f ${MAX_CPU_FREQ}   # 指定運轉速度


Reference
========================================

* `Red Hat Enterprise Linux 7 - Performance Tuning Guide <https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html-single/Performance_Tuning_Guide/>`_

* `Interrupts and IRQ Tuning <https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/6/html/Performance_Tuning_Guide/s-cpu-irq.html>`_

    cat /proc/interrupts
    cat /proc/irq/${IRQ_NUMBER}/smp_affinity
