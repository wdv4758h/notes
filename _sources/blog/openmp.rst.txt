:title: OpenMP 入門
:slug: openmp-intro
:date: 2015-05-07 21:39
:modified: 2015-05-07 21:39
:category: Misc
:tags: C
:author: wdv4758h
:summary:

Introduction
========================================

OpenMP 全名叫 Open Multi-Processing，
是由 OpenMP Architecture Review Board 這個非營利組織所訂定的跨平台 API 規範，
目標是要幫現有的程式快速的加上多核心支援，
語言支援有 C、C++、Fortran，
內容包含 compiler directives、library routines、environment variables。


Compiler Support
------------------------------

* GCC 從 4.2 開始支援 OpenMP
* Clang 在 3.6 時還沒有完整的支援

.. table::
    :class: table table-bordered

    +----------------+-----+------+-------+
    | OpenMP Version | GCC | icc  | Clang |
    +================+=====+======+=======+
    | 2.5            | 4.2 | 10.1 |       |
    +----------------+-----+------+-------+
    | 3.0            | 4.4 | 11.0 |       |
    +----------------+-----+------+-------+
    | 3.1            | 4.7 |      |       |
    +----------------+-----+------+-------+
    | 4.0            | 4.9 |      |       |
    +----------------+-----+------+-------+

* Current Compiler Version
    - GCC : 5.1, 2015-04-22
    - Clang : 3.6, 2015-02-27
    - Intel C++ Compiler : 15.0.2, 2015-01-22

.. code-block:: cpp

    $ gcc -fopenmp hello.c -o hello

* `OpenMP Compilers <http://openmp.org/wp/openmp-compilers/>`_
* `LLVM - OpenMP <http://openmp.llvm.org/>`_
    - `Clang - Status of supported OpenMP constructs <https://github.com/clang-omp/clang/wiki/Status-of-supported-OpenMP-constructs>`_

* GCC
    - ``-fopenmp``
    - `GCC - OpenMP <https://gcc.gnu.org/wiki/openmp>`_


Example
------------------------------

.. code-block:: cpp

    // sleep sort

    #include <cstdio>
    #include <vector>
    #include <unistd.h> // sleep

    void sleep_sort(std::vector<unsigned long long> &data) {

        const auto length = data.size();

        #pragma omp parallel num_threads(length)
        {
            #pragma omp for
            for(unsigned long i = 0; i < length; i++) {
                sleep(data[i]);
                printf("%llu\n", data[i]);
            }
        }
    }

    int main(int argc, char *argv[]) {

        std::vector<unsigned long long> data(argc-1);

        #pragma omp parallel for
        for(int i = 0; i < argc-1; i++) {
            sscanf(argv[i+1], "%llu", &data[i]);
        }

        sleep_sort(data);

        return 0;
    }


OpenMP 會利用 directive 來增加 multithread 支援，
起手勢為 ``#pragma omp``

在 GCC 中， ``-fopenmp`` 會在 link 時加上 ``libgomp`` 這個 runtime library，
libgomp 會由 CPU 核心數來決定要開的 thread 數

在 C/C++ 標準中，如果遇到不支援的 ``#pragma`` 就直接忽略，
所以這樣增加 OpenMP 的支援不會造成舊 compiler 編譯時出現問題。

經由 ``omp.h`` 可以存取一個 runtime library，
但是這通常不需要，
如果要的話可以從 ``#define _OPENMP`` 得知對於不支援的 compiler 會如何處理。


Syntax
------------------------------

parallel
++++++++++++++++++++

使用 parallel pragma 來開始一個 parallel block，
程式會 runtime 決定要開多少 thread，
平行化的範圍是 parallel pragma 後的 statement 或 block，
結束後 thread 就會收回。

.. code-block:: cpp

    #pragma omp parallel
    {
        // Code inside this region runs in parallel.
        printf("Hello!\n");
    }

實作上，GCC 會產生一個 magic function，把相關的 code 都放進去，
如此一來 block 裡個變數都是 function 的 local variable (在不同 thread 也是 local)。
ICC 則是使用類似 fork 的機制，而非使用 magic function。
兩種實作都會正常運作。

不同 context 間的變數的分享是自動處理的，
有時候是用 reference，有時候是用 register 變數 (離開 parallel block 或是執行 flush 時會清掉)

OpenMP 的平行化只要搭配 if clause 就可以使用 condition 來開關

.. code-block:: cpp

    #pragma omp parallel for if(parallelism_enabled)
    for(int c=0; c<n; ++c)
        handle(c);


Loop directive: for
++++++++++++++++++++

.. code-block:: cpp

    #pragma omp for
    for(int n = 10; n < 20; ++n) {
        printf("%d\n", n);
    }

這段 code 和以下 code 等價 :

.. code-block:: cpp

    int this_thread = omp_get_thread_num(), num_threads = omp_get_num_threads();
    int start = (this_thread    ) * (20 - 10) / num_threads + 10;
    int end   = (this_thread + 1) * (20 - 10) / num_threads + 10;
    for(int n = start; n < end; ++n)
        printf("%d\n", n);

其中， ``omp_get_thread_num`` 取得的是現在這個 thread 的編號，
``omp_get_num_threads`` 取得的是總共有多少 thread。
在只有單條 thread 的情況下，this_thread 就會是 0，
num_threads 就會是 1，
start 和 end 的話則是把 for 裡的範圍分配給各個 thread，
每個 thread 會拿到 loop 裡的不同 section，如此一來每個 section 會各自平行執行。

Scheduling
++++++++++++++++++++

預設的 schedule 是 static，在進入 loop 時，各 loop 會各自決定要計算的部份。

.. code-block:: cpp

    #pragma omp for schedule(static)
    for(int c=0; c<n; ++c)
        handle(c);



在 dynamic 的 schedule 中，不會事先決定好每個 thread 要跑哪個部份，
每個 thread 會去詢問 OpenMP runtime library 來取得 iteration number 然後運算，
算完後再要下一個。常和 ``ordered`` 一起使用，或是不同的 iteration 會需要不同時間來執行時。

.. code-block:: cpp

    #pragma omp for schedule(dynamic)
    for(int c=0; c<n; ++c)
        handle(c);



另外可以指定一次分配多少個 iteration 來減少詢問 OpenMP runtime library 的次數 :

.. code-block:: cpp

    #pragma omp for schedule(dynamic, 3)
    for(int c=0; c<n; ++c)
        handle(c);



ordered
++++++++++++++++++++

指定 code 中的某部份需要照順序執行

.. code-block:: cpp

    #pragma omp for ordered schedule(dynamic)
    for(int n=0; n<100; ++n)
    {
        files[n].compress();

        #pragma omp ordered
        send(files[n]);
    }



Sections
++++++++++++++++++++

指定多個 block 可以平行執行

.. code-block:: cpp

    #pragma omp sections
    {
        { Work1(); }
        #pragma omp section
        { Work2();
          Work3(); }
        #pragma omp section
        { Work4(); }
    }

.. code-block:: cpp

    #pragma omp parallel // starts a new team
    {
        //Work0(); // this function would be run by all threads.

        #pragma omp sections // divides the team into sections
        {
          // everything herein is run only once.
          { Work1(); }
          #pragma omp section
          { Work2();
            Work3(); }
          #pragma omp section
          { Work4(); }
        }

        //Work5(); // this function would be run by all threads.
    }

tasks (OpenMP 3.0)
++++++++++++++++++++

.. code-block:: cpp

    struct node { node *left, *right; };
    extern void process(node* );
    void postorder_traverse(node* p)
    {
        if (p->left)
            #pragma omp task // p is firstprivate by default
            postorder_traverse(p->left);
        if (p->right)
            #pragma omp task // p is firstprivate by default
            postorder_traverse(p->right);
        #pragma omp taskwait
        process(p);
    }


有了起手勢 ``#pragma omp`` 後，可以接以下東西 :

.. table::
    :class: table table-bordered

    +--------------------+--------------------------------------------------------------------------------------+
    | parallel           | 建 thread                                                                            |
    +--------------------+--------------------------------------------------------------------------------------+
    | for                | 把 for 切給各個 thread                                                               |
    +--------------------+--------------------------------------------------------------------------------------+
    | num_threads(N)     | 指定要開 N 個 thread                                                                 |
    +--------------------+--------------------------------------------------------------------------------------+
    | ordered            | 指定 code 中的某部份需要照順序執行                                                   |
    +--------------------+--------------------------------------------------------------------------------------+
    | sections / section | 指定多個 block 可以平行執行                                                          |
    +--------------------+--------------------------------------------------------------------------------------+
    | atomic             | 只能用於簡單的運算 (例如加法)                                                        |
    +--------------------+--------------------------------------------------------------------------------------+
    | critical           |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | reduction          |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | flush              |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | private            |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | firstprivate       |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | shared             |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | lastprivate        |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | default            |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | barrier            | 一條分界線，後面的 code 會等所有 thread 把前面都執行完後才開始                       |
    +--------------------+--------------------------------------------------------------------------------------+
    | nowait             | 這個 statement 或 block 可以不用等，先執行完的 thread 可以繼續 (例如搭配 for 來使用) |
    +--------------------+--------------------------------------------------------------------------------------+
    | single             |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | master             |                                                                                      |
    +--------------------+--------------------------------------------------------------------------------------+
    | collapse(N)        | (搭配 for 使用) 處理 N 層的 Nested Loops                                             |
    +--------------------+--------------------------------------------------------------------------------------+


OpenMP 2.5 中，for 裡的 iteration variable 必需是 signed integer。
OpenMP 3.0 中，還可以是 unsigned integer、pointer、constant-time random access iterator，
iterator 的 case 會使用 ``std::distance()`` 來判斷 loop 的次數。


Problem
------------------------------

Nested Loops
++++++++++++++++++++

.. code-block:: cpp

    #pragma omp parallel for
    for(int y=0; y<25; ++y)
    {
        #pragma omp parallel for
        for(int x=0; x<80; ++x)
        {
          tick(x,y);
        }
    }

裡面那層的 OpenMP code 實際上不會平行化。

OpenMP 3.0 中加入了 collapse 可以解決這個狀況 :

.. code-block:: cpp

    #pragma omp parallel for collapse(2)
    for(int y=0; y<25; ++y)
    {
        for(int x=0; x<80; ++x)
        {
          tick(x,y);
        }
    }

效能方面，因為 libgomp 夠聰明，所以這種多層的平行化不會一直建立和回收 thread，
建立次數 (``clone`` system call) 會和 concurrent threads 的最大數量一樣，
parallel 不單純是 pthread_create 和 pthread_join 的結合。

Reference
========================================

* `Guide into OpenMP: Easy multithreading programming for C++ <http://bisqwit.iki.fi/story/howto/openmp/>`_
* `Wikipedia - OpenMP <http://en.wikipedia.org/wiki/OpenMP>`_
