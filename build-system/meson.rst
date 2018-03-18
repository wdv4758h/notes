========================================
Meson
========================================


.. contents:: 目錄


介紹
========================================

:Site: http://mesonbuild.com/
:Repo: https://github.com/mesonbuild/meson/


Meson 是用 Python 撰寫的編譯工具，
可以幫忙維護複雜的專案，
支援多種程式語言，
可以藉由實做 ``Compiler`` class 來擴充語言支援。



使用範例
========================================

假設我們有這樣的程式碼：

.. code-block:: c

    // main.c

    #include <stdio.h>

    int main(int argc, char **argv) {
        printf("Hello there.\n");
        return 0;
    }


接下來寫搭配的 ``meson.build`` ：

.. code-block:: meson

    project('tutorial', 'c')
    executable('demo', 'main.c')


使用 meson 指令準備編譯的資料夾，
準備過編譯資料夾後就只要執行 ninja 即可，
就算改過 meson 設定也會自動重生：

.. code-block:: sh

		# meson <build_dir_name>
    $ meson builddir
    The Meson build system
    Version: 0.44.0
    Source dir: /tmp/myproj
    Build dir: /tmp/myproj/builddir
    Build type: native build
    Project name: tutorial
    Native C compiler: clang (clang 5.0.1)
    Appending CFLAGS from environment: ' -Wall -Wextra -std=c11'
    Build machine cpu family: x86_64
    Build machine cpu: x86_64
    Build targets in project: 1
    Found ninja-1.8.2 at /usr/bin/ninja


編譯：

.. code-block:: sh

		# ninja -C <build_dir_name>
    $ ninja -C builddir

    # 使用 4 個 jobs 編譯
    $ ninja -C builddir -j 4

    # 執行結果
    $ ./demo


在 ``meson.build`` 加上額外相依：

.. code-block:: meson

    project('tutorial', 'c')
		mydeps = dependency('liblzma')
		executable('demo', 'main.c', dependencies: mydeps)

.. code-block:: sh

		$ ninja -C builddir
    The Meson build system
    Version: 0.44.0
    Source dir: /tmp/myproj
    Build dir: /tmp/myproj/builddir
    Build type: native build
    Project name: tutorial
    Native C compiler: clang (clang 5.0.1)
    Appending CFLAGS from environment: ' -Wall -Wextra -std=c11'
    Build machine cpu family: x86_64
    Build machine cpu: x86_64
    Found pkg-config: /usr/bin/pkg-config (0.29.2)
    Native dependency liblzma found: YES 5.2.3
    Build targets in project: 1
    Found ninja-1.8.2 at /usr/bin/ninja


安裝：

.. code-block:: sh

    ninja -C builddir install


客製化安裝目錄：

.. code-block:: sh

    # 作法一
    meson build . --prefix=/tmp
    ninja -C build
    ninja -C build install

    # 作法二
    meson build .
    ninja -C build
    env DESTDIR="/tmp" ninja -C build install



調整編譯參數
========================================

選擇語言版本
------------------------------

.. code-block:: meson

    project('myproj', 'c', 'cpp',
            default_options: ['c_std=c11', 'cpp_std=c++14'])


加上 math library
------------------------------

.. code-block:: meson

    project('myproj', 'c', 'cpp',
            default_options : ['c_std=c11', 'cpp_std=c++14'])
    mydeps = [dependency('liblzma')]
    # 用 find_library，有些平台不需要額外的參數，有些需要
    cc = meson.get_compiler('c')
    mydeps += cc.find_library('m', required : false)
    executable('demo', 'main.c', dependencies: mydeps)


專案參數
------------------------------

.. code-block:: sh

    meson mybuilddir -Dopt0=1 -Dsub1:opt1=2 -Dsub1:opt2=foo -Dsub2:opt1=false


cross compile
------------------------------

.. code-block:: sh

    meson build . --buildtype=release --cross-file=mytools.ini


* `Meson - Cross Compilation <http://mesonbuild.com/Cross-compilation.html>`_
* `cross compile 範例設定檔 <https://github.com/mesonbuild/meson/blob/master/cross/ubuntu-armhf.txt>`_


Meson + NDK
------------------------------



Subprojects
========================================



參考
========================================

* `gst-build <https://github.com/GStreamer/gst-build/>`_
