========================================
CMake
========================================

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
