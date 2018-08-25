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
支援多種程式語言。
(可以藉由實做 ``Compiler`` class 來擴充語言支援)

Meson 支援複雜的相依處理，
並盡可能地平行化編譯，
在一些較複雜的專案中已經可以看到比 Autotools 快的編譯時間。



專案語言設定
========================================

單一語言
------------------------------

目前支援的 project 選項：

* c
* cpp
* objc
* objcpp
* java
* cs
* d
* rust
* fortran
* swift


範例：

.. code-block:: meson

    project('tutorial', 'c')

.. code-block:: meson

    project('tutorial', 'c', default_options: ['c_std=c11'])


有人可能會問「為什麼沒有 Python」？
因為 Meson 的設計是要處理編譯相關的複雜設定問題，
以純 Python 的狀況來說直接使用現有的 setuptools 和 pip 就夠了，
加一層 Meson 並沒有意義。
如果是 CPython extension 的話看是用 C、C++、Rust 寫的，
可以選擇相關的專案設定，
所以也不是問題。


詳細的專案支援偵測： ``mesonbuild/interpreter.py`` 內的 detect_compilers 函式


相關呼叫流程：

* func_project
    - proj_name = args[0]
    - proj_langs = args[1:]
* add_languages(proj_langs, True)
* detect_compilers(lang, need_cross_compiler)
* detect_XXX_compiler()


多種語言
------------------------------

.. code-block:: meson

    project('myproj', 'c', 'cpp',
            default_options: ['c_std=c11', 'cpp_std=c++14'])



程式碼設定
========================================



Meson 子目錄
========================================



編譯參數調整
========================================

選擇編譯器
------------------------------

編譯器選擇直接靠常用的環境變數達成，
例如 C 語言就是 ``CC=gcc`` ``CC=clang`` 等等。

要注意的是環境變數設定的都是 native compiler，
如果要設定 cross compiler 就要用 cross file，
這跟某些 Build System 不太一樣，
但是這樣可以在編譯過程中去編出一些輔助程式，
並且在流程中使用。


語言版本
------------------------------

支援的語言版本會根據編譯器不同而有差異，
例如 Clang 和 GCC 就會不同，
但是大致上是這些：

* C: ``c_std``
    - c89
    - c99
    - c11
    - gnu89
    - gnu99
    - gnu11
* C++: ``cpp_std``
    - c++98
    - c++03
    - c++11
    - c++14
    - c++17
    - gnu++98
    - gnu++03
    - gnu++11
    - gnu++14
    - gnu++17


詳細可以看： ``mesonbuild/compilers/${LANG}.py`` 裡的 get_options


優化參數
------------------------------

平台偵測
------------------------------

覆蓋編譯器參數
------------------------------

.. code-block:: meson

    executable(..., override_options : ['c_std=c11'])



提供功能選擇
========================================

meson_options.txt



常用設定
========================================

C
------------------------------

C++
------------------------------

Python
------------------------------

Rust
------------------------------



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



相依套件處理 - Subprojects
========================================

Meson subprojects 的目的是要自動抓原始碼進來編，
使用時機可能是相依套件找不到或是想同時編多個專案，
因此要處理的部份就是把程式碼抓回來並且切到想要的版本。

subprojects 的設定會放在 ``subprojects`` 資料夾，
並且以 ``XXX.warp`` 命名。

目前 subprojects 支援：

* [wrap-git]
    - directory
    - revision
    - url
    - push-url
* [wrap-hg]
    - directory
    - revision
    - url
* [wrap-svn]
    - directory
    - revision
    - url
* [wrap-file]
    - source_filename
    - source_url
    - source_hash
    - patch_filename
    - patch_url
    - patch_hash
    - directory
    - lead_directory_missing


把 subproject 設定轉換成 Shell Script 來看，
``[wrap-git]`` 大致上是這樣：

.. code-block:: sh

    set -e

    if [ -d <directory> ]; then
        cd <directory>
        git rev-parse   # stop if this has error, means the dir is not empty and it's not a git repo
        if [ <revision> = "HEAD" ]; then
            git pull
        else
            git checkout <revision> || \
              (git fetch && git checkout <revision>)
        fi
    else
        git clone <url> <directory>
        if [ <revision> = "HEAD" ]; then
            git checkout <revision>
        fi
        if [ ! -z <push-url> ]; then
            git remote set-url --push origin <push-url>
        fi
    fi


範例 Wrap 檔：

.. code-block:: ini

    [wrap-file]
    directory=proj1


.. code-block:: ini

    [wrap-git]
    directory=glib
    url=https://gitlab.gnome.org/GNOME/glib.git
    push-url=git@gitlab.gnome.org:GNOME/glib.git
    revision=master


範例 meson.build ：

.. code-block:: meson

    dep = dependency('foo', fallback : [subproject_name, variable_name])


詳細的支援： ``mesonbuild/wrap/wrap.py`` 內的 PackageDefinition.__init__

* func_subproject (interpreter.py)
* do_subproject (interpreter.py)
* resolve (wrap/wrap.py)
* get_git/get_hg/get_svn/(download+extract_package)
* get_git/get_hg/get_svn
    - 取得 directory
    - 取得 revision
    - 呼叫 git/hg/svn 指令去取得程式碼
* download+extract_package
    - get_data
        + 去 https://wrapdb.mesonbuild.com 抓
        + 或是直接下載
    - 取得 patch_filename/patch_url/patch_hash
    - 透過 shutil.unpack_archive 去自動偵測格式並解開


Cross Compile
========================================

基本狀況
------------------------------

.. code-block:: sh

    meson build . --buildtype=release --cross-file=mytools.ini


* `Meson - Cross Compilation <http://mesonbuild.com/Cross-compilation.html>`_
* `cross compile 範例設定檔 <https://github.com/mesonbuild/meson/blob/master/cross/ubuntu-armhf.txt>`_


Android NDK
------------------------------



Modules
========================================

http://mesonbuild.com/Modules.html



Build System 比較
========================================

Meson v.s. Autotools
------------------------------

https://github.com/mesonbuild/meson/blob/master/docs/markdown/Porting-from-autotools.md


Meson v.s. CMake
------------------------------


Meson v.s. Bazel
------------------------------



Build System 轉換
========================================

Autotools ➡ Meson
------------------------------


CMake ➡ Meson
------------------------------

* tools/cmake2meson.py



使用 Meson 的專案
========================================

* `GLib <https://github.com/GNOME/glib>`_
* `GStreamer <https://github.com/GStreamer/gst-build>`_
* elementary OS
* `systemd <https://github.com/systemd/systemd>`_
* `NetworkManager <https://github.com/NetworkManager/NetworkManager>`_
* `X.org <https://github.com/freedesktop/xorg-xserver>`_



Talks
========================================

* `The Meson Build System - 4+ years of work to become an overnight success <https://www.youtube.com/watch?v=gHdTzdXkhRY>`_
    - Meson 作者講述自己開發 Meson 的過程
    - 介紹 Meson 的特色，跨平台、支援多種語言、支援 cross compile、設定簡單
    - 前幾年沒有其他人在用，投稿也被拒絕
    - 為了推廣跑去很多研討會，旅程也花了不少錢
    - 在一場研討會中跟 GStreamer 開發者聊到編譯專案的問提，GStreamer 願意嘗試採用 Meson
    - 在採用 Meson 後，編譯時間跟 Autotools 相比有大幅提昇
    - 後續越來越多專案採用，例如 GLib、systemd、X.org
    - 回顧開發過程講述自己做開源專案會碰到的困境
    - Meson 會偵測 share library 的 symbol table 有沒有改變，如果 ABI 沒有變的話就不會重新 link 執行檔，藉此可以省下不少改程式碼後重編的時間



參考
========================================

* `gst-build <https://github.com/GStreamer/gst-build/>`_
