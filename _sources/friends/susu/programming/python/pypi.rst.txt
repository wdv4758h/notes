- pip

  - 安裝 package

    - pip install <PKG_NAME>
    - pip install <PKG_NAME>==<VERSION>
    - pip install -r requirement.txt

  - 升級 package

    - pip install --upgrade <PKG_NAME>

  - 列出已安裝 package
  
    - pip list
    - pip freeze # 以 requirement.txt 的格式倒出來

  - 搜尋

    - pip search <KEYWORD>

  - 解除安裝

    - pip uninstall <PKG_NAME>

- pypi package version
  
  - Newest version: https://pypi.python.org/pypi/Cython
  - old version 0.20.2: https://pypi.python.org/pypi/Cython/0.20.2
  - list all version in pypi: https://pypi.python.org/simple/cython

Misc
----
- purelib directory
  
  - Distutil install pure python code in the purelib directory.
  - ``lib/python_version/site-packages`` in unix-like
  - ``Lib/site-packages`` in Windows
  - `PEP 376 Database of Install Python Distribution <https://www.python.org/dev/peps/pep-0376/#how-distributions-are-installed>`_

- `Full Stack Python - Application Dependencies <http://www.fullstackpython.com/application-dependencies.html>`_

  - requirement.txt
  - pip freeze

- virtualenv and real OS-level virtualization(container)

  - `Why I hate virtualenv and pip <https://pythonrants.wordpress.com/2013/12/06/why-i-hate-virtualenv-and-pip/>`_
