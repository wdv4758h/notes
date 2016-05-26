========================================
Docker
========================================

.. code-block:: sh

    $ docker version
    Client:
     Version:      1.11.1
     API version:  1.23
     Go version:   go1.6.2
     Git commit:   5604cbe
     Built:        Mon May  2 00:06:51 2016
     OS/Arch:      linux/amd64

    Server:
     Version:      1.11.1
     API version:  1.23
     Go version:   go1.6.2
     Git commit:   5604cbe
     Built:        Mon May  2 00:06:51 2016
     OS/Arch:      linux/amd64

    $ docker run -it pyston/pyston
    Unable to find image 'pyston/pyston:latest' locally
    latest: Pulling from pyston/pyston
    51f5c6a04d83: Pull complete
    a3ed95caeb02: Pull complete
    7004cfc6e122: Pull complete
    5f37c8a7cfbd: Pull complete
    8ad7684cace4: Pull complete
    a616f5d9eaa2: Pull complete
    3156a2d9e54f: Pull complete
    c2262e45b26c: Pull complete
    Digest: sha256:9471ffd4d507a14e46f93d7d8bc1f3b3e4b2ca9e10ef2bf9c47ead5ca1ba627e
    Status: Downloaded newer image for pyston/pyston:latest
    (pyston_env)root@2aa2f330d872:/#

    $ docker run -it pyston/pyston:0.5.0
    Unable to find image 'pyston/pyston:0.5.0' locally
    0.5.0: Pulling from pyston/pyston
    51f5c6a04d83: Already exists
    a3ed95caeb02: Already exists
    7004cfc6e122: Already exists
    5f37c8a7cfbd: Already exists
    8ad7684cace4: Already exists
    a616f5d9eaa2: Already exists
    3156a2d9e54f: Already exists
    c2262e45b26c: Already exists
    Digest: sha256:07132f372d10462d28bbbef34f5c021179ec7d6830904bdb46a09fa47d6b9197
    Status: Downloaded newer image for pyston/pyston:0.5.0
    (pyston_env)root@345d2a4fd976:/#


* `Developing with Docker <http://engineering.ifttt.com/oss/2015/10/06/developing-with-docker/>`_
