========================================
OpenCL (Open Computing Language)
========================================


.. contents:: 目錄


Installation
========================================

.. code-block:: sh

    $ sudo pacman -S opencl-nvidia  # NVIDIA
    $ sudo pacman -S beignet        # Intel


* AMD CPU/GPU/APU
* Intel CPU/GPU
* NVIDIA GPU
* ARM



概念學習
========================================

異質運算 (Heterogeneous Parallel Computing)
-------------------------------------------

OpenCL 概念
------------------------------

基本介紹
++++++++++++++++++++

現今的運算平台通常都具有多種運算元件，
可能是多個 CPU、GPU、DSP、加速器等等，
OpenCL 的目標是提供一個統一且方便的方式來撰寫程式以善用這些資源。

OpenCL 支援各式各樣的平台（相較之下 CUDA 只支援 NVIDIA 自家的平台），
為了要區分每個裝置所需要使用的 library，
OpenCL 的 runtime 會使用 ICD。
如果程式碼是針對 generic runtime 編譯的，
那 ICD 會 load 正確的平台 runtime。
runtime 的資料會被放在 ``/etc/OpenCL/vendors/`` 裡，
例如 ``/etc/OpenCL/vendors/intel-beignet.icd`` 。


常見 Runtime 安裝：

* Intel:  ``sudo pacman -S beignet``
* AMD:    ``sudo pacman -S opencl-mesa``
* NVIDIA: ``sudo pacman -S opencl-nvidia``


* `Arch Wiki - GPGPU <https://wiki.archlinux.org/index.php/GPGPU>`_


通常平台供應商都會提供 ICD loader （libOpenCL.so），
而這些 loader 也不具有平台依賴性，
loader 實做理論上也可以用在其他平台，
但是這些 loader 通常不是最新的，
因此可以使用 ``ocl-icd`` 來負責這塊。

檢查目前機器上已經可以使用的 OpenCL 實做（相關套件已經裝了）：

.. code-block:: sh

    $ ls /etc/OpenCL/vendors

要知道更多詳細的資訊可以安裝 ``clinfo`` ：

.. code-block:: sh

    $ sudo pacman -S clinfo
    $ clinfo


OpenCL 平台模型：

* Host：控制整隻程式執行的平台
* OpenCL Device：Host 可以利用的裝置，一個 Host 可以有多個 OpenCL Device
* Compute Unit：一個 OpenCL Device 可以有多個 Compute Unit
* Processing Element：一個 Compute Unit 可以有多個 Processing Element
* 記憶體分為 Host Memory 和 Device Memory


範例：
一台機器上同時插了兩個 CPU 和兩個 GPU，
則所有 CPU 會被視為一個 OpenCL Device，
每個 CPU core 是一個 Compute Unit，
每個 Compute Unit 則是一個 Processing Element，
如果有 SIMD 的話則看 SIMD 寬度，
一個 Compute Unit 擁有 n 個 Processing Element。
另外每個 GPU 都各自視為 OpenCL Device，
可以利用 OpenCL 來 concurrent 地控制 CPU 和 GPU。


Platform Info
++++++++++++++++++++

C:

C++:

Python:

.. code-block:: python

    #!/usr/bin/env python

    """
    Show the OpenCL information on the machine.
    """


    import pyopencl as cl


    def get_platform_info():
        """
        Get OpenCL platform info.
        """

        platforms = cl.get_platforms()
        result = []
        result.append(f'Number of platform: {len(platforms)}')
        prefix = '│  '
        prefix_head = '├──'
        for index, platform in enumerate(platforms):
            if index == len(platforms) - 1:
                prefix = '   '
                prefix_head = '└──'
            devices = platform.get_devices()
            result.extend((
                f'{prefix_head}Platform: {platform.name}',
                f'{prefix}Vendor: {platform.vendor}',
                f'{prefix}Version: {platform.version}',
                f'{prefix}Number of devices: {len(devices)}',
            ))
            subprefix = prefix + '│  '
            subprefix_head = prefix + '├──'
            for index, device in enumerate(devices):
                if index == len(devices) - 1:
                    subprefix = prefix + '   '
                    subprefix_head = prefix + '└──'
                result.extend((
                    f'{subprefix_head}Name: {device.name}',
                    f'{subprefix}Version: {device.opencl_c_version}',
                    f'{subprefix}Max Compute Units: {device.max_compute_units}',
                    f'{subprefix}Local Memory Size: {device.local_mem_size/1024} KB',
                    f'{subprefix}Global Memory Size: {device.global_mem_size/(1024*1024)} MB',
                    f'{subprefix}Max Alloc Size: {device.max_mem_alloc_size/(1024*1024)} MB',
                    f'{subprefix}Max Work-group Total Size: {device.max_work_group_size}',
                    f'{subprefix}Max Work-group Dims: {device.max_work_item_sizes}',
                ))
        return '\n'.join(result)


    if __name__ == '__main__':
        print(get_platform_info())


.. code-block:: sh

    $ python cl-platform-info.py
    Number of platform: 1
    └──Platform: Intel Gen OCL Driver
       Vendor: Intel
       Version: OpenCL 2.0 beignet 1.3
       Number of devices: 1
       └──Name: Intel(R) HD Graphics Skylake ULT GT2
          Version: OpenCL C 2.0 beignet 1.3
          Max Compute Units: 24
          Local Memory Size: 64.0 KB
          Global Memory Size: 3959.0 MB
          Max Alloc Size: 2969.0 MB
          Max Work-group Total Size: 512
          Max Work-group Dims: [512, 512, 512]


改寫
++++++++++++++++++++

假設原本有這樣的 C 程式：

.. code-block:: c

    void mul(const int length,
             const float *a,
             const float *b,
             float *c) {
        int i;
        for (i = 0; i < length; i++) {
            c[i] = a[i] * b[i];
        }
    }


用 OpenCL 重寫：

.. code-block:: opencl

    // this is called "kernel"
    // every instance of kernel is called "work-item"
    // the "work-items" will be executed in parallel
    __kernel void mul(__global const float *a,
                      __global const float *b,
                      __global float *c) {
        int id = get_global_id(0);
        c[id] = a[id] * b[id];
    }


* Global Dimension
* Local Dimension
* work-items
* work-groups


OpenCL 程式的編譯分成兩種：

* Online Compilation: OpenCL kernel 在執行期間才會編譯，只須在執行前先編譯好其他部份的程式即可
* Offline Compilation: OpenCL kernel 在執行前就編譯好，執行期間直接使用編譯好的 kernel


Online Compilation:

.. code-block:: sh

    $ clang -lOpenCL main-online.c


Offline Compilation:

.. code-block:: sh

    # 會生出 SPIR (Standard Portable Intermediate Representation)
    $ clang -include clc/clc.h -std=cl2.0 -S -emit-llvm -target nvptx64-nvidia-nvcl kernel.cl
    $ llvm-link /usr/lib/clc/nvptx64--nvidiacl.bc kernel.ll -o kernel.linked.bc
    $ clang -target nvptx64-nvidia-nvcl kernel.linked.bc -S -o kernel.nvptx.s
    $ clang -lOpenCL main-offline.c

稍微把 Offline Compilation 的變動地方抽出來：

.. code-block:: sh

    $ export TARGET="nvptx64-nvidia-nvcl"
    $ export TARGET_BIT_CODE="/usr/lib/clc/nvptx64--nvidiacl.bc"
    # 會生出 SPIR (Standard Portable Intermediate Representation)
    $ clang -include clc/clc.h -std=cl2.0 -S -emit-llvm -target $TARGET kernel.cl
    $ llvm-link $TARGET_BIT_CODE kernel.ll -o kernel.linked.bc
    $ clang -target $TARGET kernel.linked.bc -S -o kernel.s
    $ clang -lOpenCL main-offline.c


同步
------------------------------



OpenCL 演進
========================================

OpenCL 1.0
------------------------------

OpenCL 1.1
------------------------------

OpenCL 1.2
------------------------------

OpenCL 2.0
------------------------------

* `OpenCL™ 2.0: Device Enqueue and Workgroup Built-in Functions <http://developer.amd.com/community/blog/2014/11/17/opencl-2-0-device-enqueue/>`_


OpenCL 2.1
------------------------------

OpenCL 2.2
------------------------------





Open Source 實做
========================================

OpenCL 定義的是 C/C++ API 用於撰寫程式，
要怎麼實做是另外一回事。
目前的 Open Source 實做幾乎都是用 Clang 作為編譯器，
把原本的程式碼轉成 IR，
接著各個實做再拿去做處理，
最後轉換成目標平台可以至執行的格式。

Clover 的實做會把 Clang 產生的 IR 轉換成 TSGI，
接著經由 Gallium 編譯成 GPU 的 machine code。

pocl (Portable OpenCL) 則是直接把 Clang 產生的 IR 交給 LLVM 處理，
轉換成 LLVM 支援的平台。

libclc 則提供 OpenCL 需要的一些 Standard Library 函式，
這是 Clover 和 pocl 都沒有完全支援的。


libclc
------------------------------

:Site: https://libclc.llvm.org/
:Repo: https://github.com/llvm-mirror/libclc


libclc 是 LLVM 中對 OpenCL 語言的實做，
以 Clang 作為前端做處理，
目前支援 AMDGCN 和 NVPTX。


pocl
------------------------------


Clover
------------------------------



CUDA to OpenCL
========================================



參考
========================================

General
------------------------------

* `Wikipedia - OpenCL <https://en.wikipedia.org/wiki/OpenCL>`_
* `Khronos - OpenCL Resources <https://www.khronos.org/opencl/resources/opencl-applications-using-opencl>`_
* `Khronos OpenCL Registry - OpenCL specification and headers <http://www.khronos.org/registry/cl/>`_
* `Khronos - SPIR (Standard Portable Intermediate Representation) <https://www.khronos.org/spir/>`_
* `Hands On OpenCL - An open source two-day lecture course for teaching and learning OpenCL <https://handsonopencl.github.io/>`_
* `Hands On OpenCL - C, C++ and Python Code for Exercises and Solutions <https://github.com/HandsOnOpenCL/Exercises-Solutions>`_
* `Porting CUDA to OpenCL <https://www.sharcnet.ca/help/index.php/Porting_CUDA_to_OpenCL>`_
* [GitHub] `Chlorine <https://github.com/Polytonic/Chlorine>`_
* `OpenCL™ Zone – Accelerate Your Applications <http://developer.amd.com/tools-and-sdks/opencl-zone/>`_
* `pocl - Portable Computing Language <http://portablecl.org/>`_
    - Clang as frontend and LLVM for kernel compiler implementation
    - [GitHub] `pocl - Portable Computing Language <https://github.com/pocl/pocl>`_
* `Gentoo Wiki - OpenCL <https://wiki.gentoo.org/wiki/OpenCL>`_
* `Arch Wiki - GPGPU <https://wiki.archlinux.org/index.php/GPGPU>`_
* `ROCm - Platform for GPU-Enabled HPC and Ultrascale Computing <https://rocm.github.io/>`_


Intel
------------------------------

* `Intel SDK for OpenCL™ Applications <https://software.intel.com/en-us/intel-opencl>`_
* `Intel FPGA SDK for OpenCL <https://www.altera.com/products/design-software/embedded-software-developers/opencl/overview.html>`_


LLVM
------------------------------

* `LLVM - include/llvm/ADT/Triple.h <https://github.com/llvm-mirror/llvm/blob/master/include/llvm/ADT/Triple.h>`_


Tutorial
------------------------------

* `Hands On OpenCL <https://handsonopencl.github.io/>`_
* `Getting started with OpenCL, Part #1 <https://anteru.net/2012/11/03/2009/>`_
* `Adventures in OpenCL: Part 1, Getting Started <http://enja.org/2010/07/13/adventures-in-opencl-part-1-getting-started/>`_
