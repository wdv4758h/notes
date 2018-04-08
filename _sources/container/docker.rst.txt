========================================
Docker
========================================


.. contents:: 目錄


介紹
========================================

:Repo: https://github.com/docker/docker-ce
:Repo: https://github.com/docker/compose
:Repo: https://github.com/moby/moby



基本使用
========================================

安裝：

.. code-block:: sh

    sudo pacman -S docker
    sudo pacman -S docker-compose


開啟 daemon：

.. code-block:: sh

    sudo systemctl start docker


Docker without sudo：

.. code-block:: sh

    sudo usermod -aG docker $USER
    newgrp docker


簡單環境測試：

.. code-block:: sh

    $ docker version
    Client:
     Version:	18.01.0-ce
     API version:	1.35
     Go version:	go1.9.2
     Git commit:	03596f51b1
     Built:	Sun Jan 14 23:10:39 2018
     OS/Arch:	linux/amd64
     Experimental:	false
     Orchestrator:	swarm

    Server:
     Engine:
      Version:	18.01.0-ce
      API version:	1.35 (minimum version 1.12)
      Go version:	go1.9.2
      Git commit:	03596f51b1
      Built:	Sun Jan 14 23:11:14 2018
      OS/Arch:	linux/amd64
      Experimental:	false


下載：

.. code-block:: sh

    docker pull archlinux/base


執行：

.. code-block:: sh

    # 開啟
    docker start myorg/myimage
    # 關閉
    docker stop myorg/myimage


開 container 並執行特定指令：

.. code-block:: sh

    docker run -it --rm myorg/myimage
    # 開 TCP port
    docker run -p 45677:45677 -it --rm myorg/myimage
    # 開 UDP port
    docker run -p 45677:45677/udp -it --rm myorg/myimage
    # bridge host network
    docker run --net host -it --rm myorg/myimage



Dockerfile
========================================

撰寫（Arch Linux）：

.. code-block:: dockerfile

    # Pull base image
    FROM archlinux/base
    RUN pacman -Syu
    # other things


撰寫（Ubuntu）：

.. code-block:: dockerfile

    # Pull base image
    FROM ubuntu:16.04
    RUN apt-get update
    # other things


製作 image：

.. code-block:: sh

    docker build /path/to/folder/of/Dockerfile
    # -t for tag
    docker build -t myimage /path/to/folder/of/Dockerfile



清理空間
========================================

.. code-block:: sh

    docker system prune -a --volumes


.. code-block:: sh

    rm -rf /var/lib/docker/devicemapper
    systemctl restart docker



docker-compose
========================================



更新 image
========================================

上傳到 Docker Hub：

.. code-block:: sh

    # 找出想用的 image
    $ docker images
    ...
    # 儲存更動
    $ docker commit 1152c1e8c7f3
    sha256:3a98e8481218c0cbae84311f7d7df1a44edfb23907af5368d0c1363b888defb9
    # 上 tag
    $ docker tag 3a98e8481218 DOCKER_ID_USER/my_image
    # 上傳
    $ docker push DOCKER_ID_USER/my_image



輸出成 rootfs
========================================

.. code-block:: sh

    docker run -it --rm -d 250b5ed4d50f bash
    docker container ls
    docker export e6c0df1d7c43 -o ~/rootfs.tar



壓縮 docker images 大小
========================================

docker-squash
------------------------------

:Repo: https://github.com/goldmann/docker-squash


.. code-block:: sh

    $ docker history myorg/myimage:latest
    # 選擇開始 squash 的 commit
    $ docker-squash -f 2b7782d76911 -t myorg/myimage:squashed myorg/myimage:latest




參考
========================================

* `Arch Wiki - Docker <https://wiki.archlinux.org/index.php/Docker>`_
* `archlinux/base <https://hub.docker.com/r/archlinux/base/>`_
