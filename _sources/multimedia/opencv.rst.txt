========================================
OpenCV
========================================


.. contents:: 目錄


編譯
========================================

.. code-block:: sh

    $ git clone https://github.com/opencv/opencv
    $ git clone https://github.com/opencv/opencv_contrib
    $ cd opencv/
    $ mkdir build/
    $ cd build/
    # 自行更改要開啟的設定
    $ cmake -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ \
            -D ENABLE_SSE3=ON \
            -D WITH_GSTREAMER=ON \
            -D WITH_FFMPEG=ON \
            -D WITH_OPENGL=ON \
            -D WITH_OPENCL=ON \
            -D WITH_CUDA=OFF \
            -D CMAKE_BUILD_TYPE=Release \
            ../

    # 編好後可以在 lib/python3/ 內找到給 Python 3 的 Shared Library



Misc
========================================

OpenCV 的 ``VideoCapture`` 、 ``VideoWrite`` 可以直接放入 GStreamer Pipeline 來用



Machine Learning + OpenCV
========================================

* `Machine Learning for OpenCV <https://github.com/mbeyeler/opencv-machine-learning>`_



參考
========================================
