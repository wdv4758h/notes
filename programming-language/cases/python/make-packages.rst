========================================
製作 Packages
========================================


.. contents:: 目錄


基本 setup.py
========================================

:URL: https://github.com/pypa/setuptools


.. code-block:: python

    from setuptools import setup

    setup(name='funniest',
          version='0.1',
          description='The funniest joke in the world',
          url='http://github.com/storborg/funniest',
          author='Flying Circus',
          author_email='flyingcircus@example.com',
          license='MIT',
          packages=['funniest'],
          zip_safe=False)



install_requires & requirements.txt
========================================

install_requires 通常是這專案需要的最少相依套件，
裡面寫的是抽象（Abstract）的套件，
只有名稱和版本範圍限制，
install_requires 會在使用 pip 安裝時進行處理。

而 requirements.txt 則通常是定義完整的 Python 環境，
也可能包含明確指定的套件版本，
用於重建一樣的安裝環境，
也可能包含特定的 URL 來指定套件來源（Concrete），
requirements.txt 不會自動在使用 pip 安裝時進行處理，
除非使用 ``pip install -r`` 特別指定。



在 setup.py 內重複利用 requirements.txt
========================================

.. code-block:: python

    import os

    from pip.req import parse_requirements


    ROOT_DIR = os.path.dirname(os.path.realpath(__file__))


    # parse_requirements() returns generator of pip.req.InstallRequirement instance
    install_requires = parse_requirements(
        os.path.join(ROOT_DIR, 'requirements.txt'),
        session=False
    )

    # requirements is a list of requirement
    # e.g. ['requests==2.13.0', ...]
    requirements = list(map(lambda x: str(x).split()[0], install_requires))

    setup(
        ...
        install_requires=requirements,
        ...
    )



額外的 dependencies 來源（setup.py）
========================================

.. code-block:: python

    setup(
        ...
        dependency_links=['http://github.com/user/repo/tarball/master#egg=package-1.0']
        ...
    )



安裝額外的檔案
========================================

.. code-block:: python

    ...

    setup(
        ...
        package_data={'': ['*.txt', 'path/to/resources/*.txt']},
        include_package_data=True,
        ...
    )


MANIFEST.in:

.. code-block:: txt

    include path/to/resources/*



參考
========================================

* `Python Packaging User Guide - install_requires vs Requirements files <https://packaging.python.org/requirements/>`_
