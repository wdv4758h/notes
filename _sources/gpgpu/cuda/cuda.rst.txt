========================================
CUDA
========================================


流程
========================================

執行流程 ::

    　                   傳送資料到顯示卡記憶體中
    主機記憶體 ------------------------------------------>> 顯示卡記憶體


                    傳送程式碼(kernel)到顯示卡
    主機記憶體 ------------------------------------------>> 顯示卡記憶體


    主機做其它的事 or 閒置                                  執行顯示卡中的程式(kernel)


                            傳回執行結果
    主機記憶體 <<------------------------------------------ 顯示卡記憶體



編譯流程 ::

    　            nvcc
    .cu 檔案  ----------> 可執行檔 or 目的檔


總數目 ::

    　     總執行緒數目 = 網格大小(gridDim) x 區塊大小(blockDim)

    例如下圖為 (網格大小=3, 區塊大小=4) 所形成的核心，它具有 12 個獨立的執行緒

            +-----------+-----------+--------------------+
            |           |           | thread 0   (id  0) |
            |           |           +--------------------+
            |           |           | thread 1   (id  1) |
            |           |  block 0  +--------------------+
            |           |           | thread 2   (id  2) |
            |           |           +--------------------+
            |           |           | thread 3   (id  3) |
            |           +-----------+--------------------+
            |           |           | thread 0   (id  4) |
            |           |           +--------------------+
            |           |           | thread 1   (id  5) |
            |  grid     |  block 1  +--------------------+
            | (kernel)  |           | thread 2   (id  6) |
            |           |           +--------------------+
            |           |           | thread 3   (id  7) |
            |           +-----------+--------------------+
            |           |           | thread 0   (id  8) |
            |           |           +--------------------+
            |           |           | thread 1   (id  9) |
            |           |  block 2  +--------------------+
            |           |           | thread 2   (id 10) |
            |           |           +--------------------+
            |           |           | thread 3   (id 11) |
            +-----------+-----------+--------------------+


使用 ::

    kernel_name <<<gridDim, blockDim>>> (arg1, arg2, ...);

    核心函式名     網格大小 區塊大小    函式要傳的引數 (和 C 相同)


``<<<3, 4>>>`` :

+------------------------+------------------------------------------+----------------------------+
| 網格大小               | gridDim.x   = 3                          | (每個網格包含 3 個區塊)    |
+------------------------+------------------------------------------+----------------------------+
| 區塊大小               | blockDim.x  = 4                          | (每個區塊包含 4 個執行緒)  |
+------------------------+------------------------------------------+----------------------------+
| 區塊索引               | blockIdx.x  = 0,1,2                      | (每個 thread 看到的不一樣) |
+------------------------+------------------------------------------+----------------------------+
| 執行緒索引             | threadIdx.x = 0,1,2,3                    | (每個 thread 看到的不一樣) |
+------------------------+------------------------------------------+----------------------------+
| 區塊基底               | blockIdx.x*blockDim.x = 0,4,8            |                            |
+------------------------+------------------------------------------+----------------------------+
| 區塊基底加上執行緒索引 | id = blockIdx.x*blockDim.x + threadIdx.x |                            |
|                        |    = 0,1,2,3,  4,5,6,7,  8,9,10,11       |                            |
+------------------------+------------------------------------------+----------------------------+




名詞
========================================

* host   : PC or Server
* device : GPGPU
* kernel : 在顯示卡上執行的程式碼
* SMs (Streaming Multiprocessors)


SIMT (Single Instruction Multi-Threads)
========================================

Optimization
========================================

* ``__restrict__``

Reference
========================================

* `Modern GPU <http://nvlabs.github.io/moderngpu/>`_

* `Wikipedia - CUDA <https://en.wikipedia.org/wiki/CUDA>`_
* `Wikipedia - Single instruction, multiple threads <https://en.wikipedia.org/wiki/Single_instruction,_multiple_threads>`_
* ptt.cc
    - `CUDA 程式設計(1) -- 簡介 <https://www.ptt.cc/bbs/VideoCard/M.1222302747.A.CC4.html>`_
    - `CUDA 程式設計(2) -- SIMT概觀 <https://www.ptt.cc/bbs/VideoCard/M.1222881899.A.C62.html>`_
    - `CUDA 程式設計(3) -- CUDA 安裝 <https://www.ptt.cc/bbs/VideoCard/M.1223477316.A.1F8.html>`_
    - `CUDA 程式設計(4) -- 硬體規格簡介 & 採購參考 <https://www.ptt.cc/bbs/VideoCard/M.1223477872.A.1C2.html>`_
    - `CUDA 程式設計(5) -- 第一支程式 (向量加法) <https://www.ptt.cc/bbs/VideoCard/M.1224074823.A.786.html>`_
    - `CUDA 程式設計(6) -- 記憶體 <https://www.ptt.cc/bbs/VideoCard/M.1224674233.A.4CC.html>`_
    - `CUDA 程式設計(7) -- 來玩泡泡吧 <https://www.ptt.cc/bbs/VideoCard/M.1225285229.A.F15.html>`_
    - `CUDA 程式設計(8) -- OpenMP vs. SIMT <https://www.ptt.cc/bbs/VideoCard/M.1225888236.A.79A.html>`_
    - `CUDA 程式設計(9) -- 泡泡龍 part 2 <https://www.ptt.cc/bbs/VideoCard/M.1225912100.A.5B0.html>`_
    - `CUDA 程式設計(10) -- 速成篇(上) <https://www.ptt.cc/bbs/VideoCard/M.1226501606.A.7E2.html>`_
    - `CUDA 程式設計(11) -- 速成篇(中) <https://www.ptt.cc/bbs/VideoCard/M.1227118854.A.0F1.html>`_
    - `CUDA 程式設計(12) -- 速成篇(下) <https://www.ptt.cc/bbs/VideoCard/M.1227708086.A.351.html>`_
    - `CUDA 程式設計(13) -- 材質快取 (一) <https://www.ptt.cc/bbs/VideoCard/M.1228930736.A.779.html>`_
    - `CUDA 程式設計(14) -- 新年來開始 warp 吧 <https://www.ptt.cc/bbs/VideoCard/M.1231036765.A.649.html>`_
    - `CUDA 程式設計(15) -- 翻譯 RWT P4 [CUDA API] <https://www.ptt.cc/bbs/VideoCard/M.1233304220.A.98D.html>`_
* [2011] `SIMD < SIMT < SMT: parallelism in NVIDIA GPUs <http://yosefk.com/blog/simd-simt-smt-parallelism-in-nvidia-gpus.html>`_
    - flexibility: SIMD < SIMT < SMT
    - performance: SIMD > SIMT > SMT
* `CUDA 7 Runtime Compilation <http://www.soa-world.de/echelon/2015/01/cuda-7-runtime-compilation.html>`_
