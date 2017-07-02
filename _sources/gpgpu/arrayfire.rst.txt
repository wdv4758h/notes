========================================
ArrayFire
========================================

Installation
========================================

.. code-block:: sh

    $ sudo pacman -S arrayfire


Python Binding :

.. code-block:: sh

    $ pip install arrayfire


Prepare
========================================

要執行需要 OpenCL 的程式：

.. code-block:: sh

    # Intel

    $ sudo yaourt -S intel-opencl-runtime   # official
    $ sudo yaourt -S beignet                # for integrated graphics hardware

    # NVIDIA

    $ sudo pacman -S opencl-nvidia      # official

    # AMD

    $ sudo yaourt -S opencl-catalyst    # official
    $ sudo pacman -S opencl-mesa        # mesa driver



OpenCL 開發：

.. code-block:: sh

    $ sudo pacman -S ocl-icd opencl-headers



Check :

.. code-block:: sh

    # Intel

    $ cat /etc/OpenCL/vendors/intel.icd
    /opt/intel/opencl-sdk/lib64/libintelocl.so

    $ cat /etc/OpenCL/vendors/intel-beignet.icd
    /usr/lib/beignet/libcl.so

    # NVIDIA

    $ cat /etc/OpenCL/vendors/nvidia.icd
    /usr/lib/libnvidia-opencl.so

    # AMD




Usage
========================================

.. code-block:: sh

    $ cat hello.py
    #!/usr/bin/python

    import arrayfire as af

    # Display backend information

    print("="*20)

    af.info()

    print("="*20)

    af.backend.set_unsafe("cpu")
    af.info()

    print("="*20)

    af.backend.set_unsafe("opencl")
    af.info()

    print("="*20)

    af.backend.set_unsafe("cuda")
    af.info()

    print("="*20)

    # Generate a uniform random array with a size of 5 elements
    a = af.randu(5, 1)

    # Print a and its minimum value
    print(a)

    # Print min and max values of a
    print("Minimum, Maximum: ", af.min(a), af.max(a))

    $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/cuda/lib64:/opt/cuda/nvvm/lib64
    $ python hello.py   # https://github.com/arrayfire/arrayfire-python/wiki#setting-the-environment-variables
    ====================
    ArrayFire v3.2.0 (CUDA, 64-bit Linux, build )
    Platform: CUDA Toolkit 7.5, Driver: 358.16
    [0] GeForce GT 630M, 2048 MB, CUDA Compute 2.1
    ====================
    ArrayFire v3.2.0 (CPU, 64-bit Linux, build )
    [0] Intel:        Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz Max threads(4)
    ====================
    Failed to release test userptr object! (9) i915 kernel driver may not be sane!
    Failed to release test userptr object! (9) i915 kernel driver may not be sane!
    Failed to release test userptr object! (9) i915 kernel driver may not be sane!
    Failed to release test userptr object! (9) i915 kernel driver may not be sane!
    Device[0] has no support for OpenGL Interoperation
    Device[2] has no support for OpenGL Interoperation
    ArrayFire v3.2.0 (OpenCL, 64-bit Linux, build )
    [0] BEIGNET : Intel(R) HD Graphics IvyBridge M GT2
    -1- NVIDIA  : GeForce GT 630M
    -2- INTEL   : Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz
    ====================
    ArrayFire v3.2.0 (CUDA, 64-bit Linux, build )
    Platform: CUDA Toolkit 7.5, Driver: 358.16
    [0] GeForce GT 630M, 2048 MB, CUDA Compute 2.1
    ====================
    arrayfire.Array()
    Type: float
    [5 1 1 1]
        0.7402
        0.9210
        0.0390
        0.9690
        0.9251


    Minimum, Maximum:  0.039020489901304245 0.9689629077911377


Reference
========================================

* `Arch Wiki - GPGPU <https://wiki.archlinux.org/index.php/GPGPU>`_
