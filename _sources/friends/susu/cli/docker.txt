名詞
----
- image
- container

installation
------------
- `docker - installation guide <https://docs.docker.com/installation/>`_
- `archwiki - docker <https://wiki.archlinux.org/index.php/Docker>`_

archlinux::

    yaourt -S community/docker
    sudo systemctl start docker

    # auto start at boot time
    sudo systemctl enable docker

make non-root to run docker::

    gpasswd -a user docker # 把 user 加入 docker group
    newgrp docker          # 把 gid(group id) 換成 docker

check installation::

    docker version

base image
----------
choose the userspace environment. e.g. archlinux, ubuntu ... etc

search images from registry, default registry is dockerhub::

    docker search archlinux
    # docker search <KEYWORD>

pull the image you want::

    docker pull base/archlinux
    # docker pull <USERNAE>/<IMAGE_NAME>
    
list local images::

    docker images

run the container base on image <IMAGE>, using bash shell as UI::

    docker run -t -i base/archlinux bash 
    # docker run <IMAGE> <COMMAND>

指令
----
- `門外漢的 Docker 小試身手 <http://www.codedata.com.tw/social-coding/docker-layman-abc/>`_

- ``docker run <IMAGE> <COMMAND>``
  
  - 以此 image 為基礎開啟一個新的 container, 在 container 中執行 <COMMAND>
  - e.g. ``docker run -t -i <IMAGE> bash``

  
- ``docker ps [-a|-l]`` 

  - 列出 containers 跟 container id
  - -a: 列出所有, 包含還活著(還在執行程式的)跟執行完程式關閉的 container.
  - -l: 列出最後一次執行的 container
  - -n=<NUM>: 列出最後 n 次

- ``docker commit [-m="commit log"] [-a="author name"] <CONTAINER_ID> <IMAGE>``

  - 把該 container 現在的狀態, 作為一個 commit 存到 image 上.
  - 也可存成一個新的 image
  - 要保留 container 做過的事(ex. 安裝軟體)必須 commit 到 image 上, ``docker run`` 只能以 image 為基礎啟動.

- ``docker help <SUBCOMMAND>`` (e.g. run)

  - 看 <SUBCOMMAND> 的說明

more
++++
- ``docker run``

  - ``-d`` # daemon
  - port forwarding

    - ``-P`` # all exposed port
    - ``-p <HOST_PORT>:<CONTAINER_PORT>`` # specific port

- ``docker stop <CONTAINER_NAME>``
- ``docker rm <CONTAINER_ID>``
  
  - remove all containers: ``docker rm $(docker ps -aq)``

- ``docker rmi <IMAGE>``

  - remove all images: ``docker images -a | awk '{print "docker rmi "$3""}' | sh``

- ``docker logs <CONTAINER_NAME>``

version control
+++++++++++++++
- docker diff <CONTAINER_ID>|<CONTAINER_NAME> # git status
- docker history <IMAGE> # git log
- docker commit/push/pull

20150721
--------
- docker build -t="<IMAGE_NAME>" <DOCKERFILE_DIR>

    - build a image by dockerfile.

- docker run -ti --name <CONTAINER_NAME> <IMAGE_NAME> bash 

    - enter a bash in container which is based on image 
    - volume: ``-v=<HOST_DIR>:<CONTAINER_DIR>``

- docker rm <CONTAINER_NAME/CONTAINER_ID>
- docker inspect <CONTAINER_NAME/CONTAINER_ID>

docker volume
+++++++++++++
http://dockone.io/article/128

概念
----
- daemon?
- 前端1: container + version control
- dockerhub: docker 版的 github, 有 version control 的功能後有這個也不意外.
- 後端1: pid 的 namespace 機制, container 跟外部 OS 的 pid 獨立. (process id)
- 後端2: control group, 限制每個 container 的資源使用.

- `docker 原理簡介 <http://blog.blackwhite.tw/2013/12/docker.html>`_
  
  - kernel namespace(pid, mount, network, user, ipc, uts)
  - lxc + aufs

dockerfile
----------
開啟 container 時自動執行指令, 通常用於自動化環境安裝跟佈署.
build 相似的 dockerfile 超過一次時, 如果指令相同會去取 cache (ex. apt-get 不重裝軟體).

ex::

    FROM u1240976/arch-kivy-py2
    MAINTAINER susu <u1240976@gmail.com>
    RUN pacman -Syu
    RUN pacman-db-upgrade
    ...

- `dockerfile reference <https://docs.docker.com/reference/builder/>`_
- `dockerfile 5 best practice <http://crosbymichael.com/dockerfile-best-practices.html>`_

reference
---------
- `Docker official website 10 mins tutorial - try it <https://www.docker.com/tryit/>`_
- `Introduction to Docker (這篇比較偏向 docker 的使用方式) <http://hungmingwu-blog.logdown.com/posts/196996-introduction-to-docker>`_

- `Docker Getting Start: Related Knowledge <http://tiewei.github.io/cloud/Docker-Getting-Start/>`_
- `小心暗藏惡意軟件：淺談 Docker 安全性 <http://www.hkitblog.com/?p=22552>`_
- `Docker 中文指南 <http://www.widuu.com/chinese_docker/>`_

More
----
- run gui apps
  
  - http://fabiorehm.com/blog/2014/09/11/running-gui-apps-with-docker/

- thinking: chroot, lxc, and docker (and other containers: OpenVZ, jails, zone)

  - `What does Docker add to just plain LXC? <https://docs.docker.com/faq/#what-does-docker-add-to-just-plain-lxc>`_
