========================================
OpenCV
========================================


.. contents:: 目錄


編譯
========================================

基本流程：

.. code-block:: sh

    $ git clone https://github.com/opencv/opencv
    $ git clone https://github.com/opencv/opencv_contrib
    $ cd opencv/
    $ mkdir build/
    $ cd build/
    # 自行更改要開啟的設定
    $ cmake -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ \
            -D CPU_BASELINE=SSE3 \
            -D WITH_GSTREAMER=ON \
            -D WITH_FFMPEG=ON \
            -D WITH_OPENGL=ON \
            -D WITH_OPENCL=ON \
            -D WITH_CUDA=OFF \
            -D CMAKE_BUILD_TYPE=Release \
            ../

    # 編好後可以在 lib/python3/ 內找到給 Python 3 的 Shared Library


更多編譯調整：

.. code-block:: sh

    # for x86_64
    # CPU_BASELINE 為最小需求，一定要有才可以跑
    # CPU_DISPATCH 則是額外支援，根據執行平台選擇
    $ cmake -D CMAKE_CXX_COMPILER=$CXX -D CMAKE_CC_COMPILER=$CC \
            -D PYTHON_DEFAULT_EXECUTABLE=/usr/bin/python3 \
            -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ \
            -D CPU_BASELINE=AVX2 \
            -D WITH_GSTREAMER=OFF \
            -D WITH_FFMPEG=ON \
            -D WITH_OPENGL=OFF \
            -D WITH_OPENCL=ON \
            -D WITH_CUDA=OFF \
            -D WITH_TBB=OFF \
            -D WITH_V4L=ON \
            -D WITH_XINE=OFF \
            -D WITH_GTK=OFF \
            -D WITH_QT=OFF \
            -D WITH_OPENMP=ON \
            -D BUILD_WITH_DEBUG_INFO=OFF \
            -D BUILD_TESTS=OFF \
            -D BUILD_PERF_TESTS=OFF \
            -D BUILD_EXAMPLES=OFF \
            -D INSTALL_C_EXAMPLES=OFF \
            -D INSTALL_PYTHON_EXAMPLES=OFF \
            -D CMAKE_BUILD_TYPE=Release \
            -D CMAKE_INSTALL_PREFIX=/usr \
            -D CMAKE_SKIP_RPATH=ON \
            -D BUILD_opencv_python2=OFF \
            -D BUILD_opencv_python3=ON \
            -D BUILD_opencv_dnn=OFF \
            -D BUILD_opencv_dnn_modern=OFF \
            ../


針對 ARM 平台：

.. code-block:: sh

    # for ARM
    $ cmake -D CMAKE_CXX_COMPILER=$CXX -D CMAKE_CC_COMPILER=$CC \
            -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ \
            -D CPU_BASELINE=NEON \
            -D WITH_GSTREAMER=OFF \
            -D WITH_FFMPEG=ON \
            -D WITH_OPENGL=OFF \
            -D WITH_OPENCL=ON \
            -D WITH_CUDA=OFF \
            -D WITH_TBB=OFF \
            -D WITH_V4L=ON \
            -D WITH_XINE=OFF \
            -D WITH_GTK=OFF \
            -D WITH_QT=OFF \
            -D BUILD_WITH_DEBUG_INFO=OFF \
            -D BUILD_TESTS=OFF \
            -D BUILD_PERF_TESTS=OFF \
            -D BUILD_EXAMPLES=OFF \
            -D INSTALL_C_EXAMPLES=OFF \
            -D INSTALL_PYTHON_EXAMPLES=OFF \
            -D CMAKE_BUILD_TYPE=Release \
            -D CMAKE_INSTALL_PREFIX=/usr \
            -D CMAKE_SKIP_RPATH=ON \
            -D BUILD_opencv_dnn=OFF \
            -D BUILD_opencv_dnn_modern=OFF \
            ../


靜態編譯（OpenCV 本身靜態編譯，一些外部相依 libraries 可能還是動態連結，需要更多調整）：

.. code-block:: sh

    # x86_64 Static Build
    # 重點是 "-D BUILD_SHARED_LIBS=OFF"
    $ cmake -D CMAKE_CXX_COMPILER=$CXX -D CMAKE_CC_COMPILER=$CC \
            -D PYTHON_DEFAULT_EXECUTABLE=/usr/bin/python3 \
            -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ \
            -D BUILD_SHARED_LIBS=OFF \
            -D CPU_BASELINE=AVX2 \
            -D WITH_GSTREAMER=OFF \
            -D WITH_FFMPEG=ON \
            -D WITH_OPENGL=OFF \
            -D WITH_OPENCL=ON \
            -D WITH_CUDA=OFF \
            -D WITH_TBB=OFF \
            -D WITH_V4L=ON \
            -D WITH_XINE=OFF \
            -D WITH_GTK=OFF \
            -D WITH_QT=OFF \
            -D WITH_OPENMP=ON \
            -D BUILD_WITH_DEBUG_INFO=OFF \
            -D BUILD_TESTS=OFF \
            -D BUILD_PERF_TESTS=OFF \
            -D BUILD_EXAMPLES=OFF \
            -D INSTALL_C_EXAMPLES=OFF \
            -D INSTALL_PYTHON_EXAMPLES=OFF \
            -D CMAKE_BUILD_TYPE=Release \
            -D CMAKE_INSTALL_PREFIX=/usr \
            -D CMAKE_SKIP_RPATH=ON \
            -D BUILD_opencv_python2=OFF \
            -D BUILD_opencv_python3=ON \
            -D BUILD_opencv_dnn=OFF \
            -D BUILD_opencv_dnn_modern=OFF \
            ../


.. code-block:: sh

    # ARM Static Build
    # 重點是 "-D BUILD_SHARED_LIBS=OFF"
    $ cmake -D CMAKE_CXX_COMPILER=$CXX -D CMAKE_CC_COMPILER=$CC \
            -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ \
            -D PYTHON_DEFAULT_EXECUTABLE=/usr/bin/python3 \
            -D PYTHON3_NUMPY_INCLUDE_DIRS=/usr/include/numpy/ \
            -D BUILD_SHARED_LIBS=OFF \
            -D CPU_BASELINE=NEON \
            -D WITH_GSTREAMER=OFF \
            -D WITH_FFMPEG=ON \
            -D WITH_OPENGL=OFF \
            -D WITH_OPENCL=ON \
            -D WITH_CUDA=OFF \
            -D WITH_TBB=OFF \
            -D WITH_V4L=ON \
            -D WITH_XINE=OFF \
            -D WITH_GTK=OFF \
            -D WITH_QT=OFF \
            -D BUILD_WITH_DEBUG_INFO=OFF \
            -D BUILD_TESTS=OFF \
            -D BUILD_PERF_TESTS=OFF \
            -D BUILD_EXAMPLES=OFF \
            -D INSTALL_C_EXAMPLES=OFF \
            -D INSTALL_PYTHON_EXAMPLES=OFF \
            -D CMAKE_BUILD_TYPE=Release \
            -D CMAKE_INSTALL_PREFIX=/usr \
            -D CMAKE_SKIP_RPATH=ON \
            -D BUILD_opencv_python2=OFF \
            -D BUILD_opencv_python3=ON \
            -D BUILD_opencv_dnn=OFF \
            -D BUILD_opencv_dnn_modern=OFF \
            ../


Python Wheel 打包：

.. code-block:: sh

    # 使用 opencv-python
    $ git clone https://github.com/skvark/opencv-python
    $ cd opencv-python
    $ rm -rf opencv
    $ ln -sf /path/to/your/opencv/code opencv
    $ python3 find_version.py   # will generate cv_version.py
    $ cat cv_version.py         # e.g. opencv_version = "3.3.1"
    $ cp /path/to/your/prebuilt/cv2.blabla.so cv2/
    $ python3 setup.py bdist_wheel
    $ ls dist/*.whl



Transparent API (TAPI)
========================================

Transparent API 是 OpenCV 3 加入的一層抽象化，
方便為現有演算法做出各平台的特製。


參考：

* `OpenCV - OpenCL <https://opencv.org/platforms/opencl.html>`_
* `OpenCV 3 - Transparent API <https://github.com/opencv/opencv/wiki/Opencv3#transparent-api>`_
* `Learn OpenCV - OpenCV Transparent API <https://www.learnopencv.com/opencv-transparent-api/>`_
* `T-API python support implemented by PolarNick239 · Pull Request #6078 <https://github.com/opencv/opencv/pull/6078>`_



Morphological Transformations
========================================

在進行圖像處理時，
適當套用一些 Morphological Transformations 可以改善後續處理的結果，
例如在做物件追蹤時，先比較圖像，抽出有變動的部份（Background Subtraction），
接著做一些 Morphological Transformations，
再找出輪廓（findContours），
最後丟給物件追蹤（Object Tracking），
中間的圖像處理就可以對後續追蹤有不少的影響。


常用範例：

* Erosion：變細
* Dilation：變粗
* Opening：去除外圍雜訊
* Closing：補足內在漏洞
* White Tophat
* Black Tophat
* Skeletonize
* Convex Hull


參考：

* `OpenCV - Morphological Transformations <https://docs.opencv.org/trunk/d9/d61/tutorial_py_morphological_ops.html>`_
* `OpenCV - Structural Analysis and Shape Descriptors <https://docs.opencv.org/trunk/d3/dc0/group__imgproc__shape.html>`_
* `Morphological Filtering <http://scikit-image.org/docs/dev/auto_examples/xx_applications/plot_morphology.html>`_



Misc
========================================

OpenCV 的 ``VideoCapture`` 、 ``VideoWrite`` 可以直接放入 GStreamer Pipeline 來用



Machine Learning + OpenCV
========================================

* `Machine Learning for OpenCV <https://github.com/mbeyeler/opencv-machine-learning>`_



參考
========================================

* `OpenCV - CPU optimizations build options <https://github.com/opencv/opencv/wiki/CPU-optimizations-build-options>`_
