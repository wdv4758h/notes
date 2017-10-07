========================================
OpenCL (Open Computing Language)
========================================


.. contents:: 目錄


Installation
========================================

.. code-block:: sh

    $ sudo pacman -S opencl-nvidia  # NVIDIA
    $ sudo yaourt -S beignet        # Intel


概念學習
========================================

異質運算 (Heterogeneous Parallel Computing)
-------------------------------------------

OpenCL 概念
------------------------------

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
++++++++++++++++++++++++++++++

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



OpenCL 2.0
========================================

* `OpenCL™ 2.0: Device Enqueue and Workgroup Built-in Functions <http://developer.amd.com/community/blog/2014/11/17/opencl-2-0-device-enqueue/>`_



Reference
========================================

* `Khronos - OpenCL Resources <https://www.khronos.org/opencl/resources/opencl-applications-using-opencl>`_
* `Khronos OpenCL Registry - OpenCL specification and headers <http://www.khronos.org/registry/cl/>`_
* `Hands On OpenCL - An open source two-day lecture course for teaching and learning OpenCL <https://handsonopencl.github.io/>`_
* `Porting CUDA to OpenCL <https://www.sharcnet.ca/help/index.php/Porting_CUDA_to_OpenCL>`_
* [GitHub] `Chlorine <https://github.com/Polytonic/Chlorine>`_
* `OpenCL™ Zone – Accelerate Your Applications <http://developer.amd.com/tools-and-sdks/opencl-zone/>`_
* `pocl - Portable Computing Language <http://portablecl.org/>`_
    - Clang as frontend and LLVM for kernel compiler implementation

----

* `Getting started with OpenCL, Part #1 <https://anteru.net/2012/11/03/2009/>`_
* `Adventures in OpenCL: Part 1, Getting Started <http://enja.org/2010/07/13/adventures-in-opencl-part-1-getting-started/>`_
