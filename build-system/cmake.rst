========================================
CMake
========================================


.. contents:: 目錄


Example 1
========================================

1. ./hello.c

.. code-block:: sh

    #include <stdio.h>

    int main () {
      printf("Hello World!\n");
      return 0;
    }


2. ./CMakeLists.txt

.. code-block:: cmake

    PROJECT (HELLO)
    SET (HELLO_SRCS hello.c)
    ADD_EXECUTABLE (hello ${HELLO_SRCS})

3. 編譯並執行

.. code-block:: sh

    $ cmake .
    -- The C compiler identification is GNU 5.1.0
    -- The CXX compiler identification is GNU 5.1.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /tmp/cmake
    $ make
    Scanning dependencies of target hello
    [100%] Building C object CMakeFiles/hello.dir/hello.c.o
    Linking C executable hello
    [100%] Built target hello
    $ ./hello
    Hello World!


Example 2
========================================

1. ./lib/hello.c

.. code-block:: c

    #include <stdio.h>

    void hello (){
        printf("Hello World!\n");
    }


2. ./lib/hello.h

.. code-block:: c

    void hello ();


3. ./src/main.c

.. code-block:: c

    #include <hello.h>

    int main () {
        hello();
        return 0;
    }


4. ./lib/CMakeLists.txt

.. code-block:: cmake

    ADD_LIBRARY (hello hello.c)


5. ./src/CMakeLists.txt

.. code-block:: cmake

    INCLUDE_DIRECTORIES (${HELLO_SOURCE_DIR}/lib)
    LINK_DIRECTORIES (${HELLO_BINARY_DIR}/lib)
    ADD_EXECUTABLE (main main.c)
    TARGET_LINK_LIBRARIES (main hello)

6. ./CMakeLists.txt

.. code-block:: cmake

    PROJECT (HELLO)
    ADD_SUBDIRECTORY (lib)
    ADD_SUBDIRECTORY (src)

7. 編譯並執行

.. code-block:: sh

    $ cmake .
    -- The C compiler identification is GNU 5.1.0
    -- The CXX compiler identification is GNU 5.1.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/dv/cmake_zone
    $ make
    Scanning dependencies of target hello
    [ 50%] Building C object lib/CMakeFiles/hello.dir/hello.o
    Linking C static library libhello.a
    [ 50%] Built target hello
    Scanning dependencies of target main
    [100%] Building C object src/CMakeFiles/main.dir/main.o
    Linking C executable main
    [100%] Built target main
    $ src/main
    Hello World!


More Options
========================================

指定安裝路徑
------------------------------

把原本的

.. code-block:: sh

    $ cmake .

換成

.. code-block:: sh

    $ cmake -DCMAKE_INSTALL_PREFIX:PATH=/your/install/path .


指定產生檔案的資料夾 (不要混在 source code 裡)
----------------------------------------------

直接在想要放的 folder 下 cmake (接 source code 資料夾)

例如：

.. code-block:: sh

    $ mkdir build
    $ cd build
    $ cmake ../


換 Linker
========================================

預設狀況下，
Linker 會去找 Compiler 來用，
例如 C++ 的會設成這樣 :

.. code-block:: cmake

    if(NOT CMAKE_CXX_LINK_EXECUTABLE)
      set(CMAKE_CXX_LINK_EXECUTABLE
          "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
    endif()

也就是說會去找 C++ Compiler 來用，
如果自己要換 Linker 的話就要把這個值蓋掉，
例如在下 ``cmake`` 指令時加上參數 :

.. code-block:: sh

    $ cmake \
    -DCMAKE_LINKER=`which my_linker` \
    -DCMAKE_CXX_LINK_EXECUTABLE='<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>'


* `[CMake] how to really change CMake linker <http://www.cmake.org/pipermail/cmake/2014-August/058271.html>`_
* `CMake - CMAKE_CXX_LINK_EXECUTABLE <https://github.com/Kitware/CMake/blob/master/Modules/CMakeCXXInformation.cmake>`_


偵測 Compiler Options
========================================

.. code-block:: cmake

    include(CheckCCompilerFlag)

    check_c_compiler_flag(-fno-sanitize-recover=all SANITIZE_RECOVER_ALL)

    if(SANITIZE_RECOVER_ALL)
        set(SANITIZE_RECOVER -fno-sanitize-recover=all)     # Clang 3.6+
    else()
        set(SANITIZE_RECOVER -fno-sanitize-recover)         # Clang 3.5-
    endif()

    message("Result : " ${SANITIZE_RECOVER})


.. code-block:: sh

    $ ls CMakeLists.txt
    $ mkdir build
    $ cd build
    $ CC=clang cmake ../
    -- The C compiler identification is Clang 3.7.0
    -- The CXX compiler identification is GNU 5.2.0
    -- Check for working C compiler: /usr/bin/clang
    -- Check for working C compiler: /usr/bin/clang -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Performing Test SANITIZE_RECOVER_ALL
    -- Performing Test SANITIZE_RECOVER_ALL - Success
    Result : -fno-sanitize-recover=all
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /tmp/build



參考
========================================

* `Awesome CMake <https://github.com/onqtam/awesome-cmake>`_
* `Cross compiling toolchains in Docker images <https://github.com/dockcross/dockcross/>`_
* `CMake scripts for Staticlibs projects <https://github.com/staticlibs/cmake/>`_
* `Collection of CMake toolchain files and scripts for cross-platform build <https://github.com/ruslo/polly>`_
* `Android CMake <https://github.com/taka-no-me/android-cmake>`_
* `CMake Examples <https://github.com/ttroy50/cmake-examples>`_
* `Learning CMake <https://github.com/Akagi201/learning-cmake>`_
* `LLVM - CMake Primer <https://llvm.org/docs/CMakePrimer.html>`_
