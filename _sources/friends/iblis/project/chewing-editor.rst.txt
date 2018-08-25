Chewing Editor
===============================================================================

Installation
----------------------------------------------------------------------

My env is Arch Linux.


Requirements
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QT = 5

- `qt5-tools`
- `qt5-base`

::

    pacman -Ss qt5-base qt5-tools

``qt5-tools`` will provide ``/usr/lib/qt/bin/lrelease``.
When building ``chewing-editor``, we will need it.


Issues
----------------------------------------------------------------------

#43 - Use system gtest
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

If ``gtest`` do not ship with share library, the default cmake module,
`FindGTest <https://cmake.org/cmake/help/latest/module/FindGTest.html>`_,
will raise error.

ref:

- `module FindGTest source <https://github.com/Kitware/CMake/blob/master/Modules/FindGTest.cmake>`_

- https://github.com/dmonopoly/gtest-cmake-example

- http://stackoverflow.com/questions/9689183/cmake-googletest

- http://stackoverflow.com/questions/21237341/testing-with-gtest-and-gmock-shared-vs-static-libraries

- http://stackoverflow.com/questions/10765885/how-to-install-your-custom-cmake-find-module

- `Ubuntu libgtest-dev package list <http://packages.ubuntu.com/zh-tw/trusty/all/libgtest-dev/filelist>`_
  It's source only.
