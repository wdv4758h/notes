========================================
Dlib
========================================


.. contents:: 目錄


介紹
========================================

`Dlib <https://github.com/davisking/dlib>`_ 是用 C++ 撰寫的 library （目前是 C++11），
從 2002 年就開始開發，
目前支援使用 CPU 或 CUDA 來運算，
Dlib 內包含很多東西，
Machine Learning 是其中一部份，
但是仍有圖像處理或壓縮演算法等實做。

.. image:: http://dlib.net/ml_guide.svg



編譯
========================================

自行安裝 BLAS 和 LAPACK 供 Dlib 使用。

.. code-block:: sh

    $ https://github.com/davisking/dlib
    $ cd dlib/

    # 編譯 library
    $ mkdir build
    $ cd build/
    $ cmake ../ -DCMAKE_BUILD_TYPE=Release -DUSE_AVX_INSTRUCTIONS=1 -DDLIB_USE_CUDA=0

    # 編譯 Python 套件，參數自行調整
    # 需要安裝 Boost
    $ python3 setup.py bdist_wheel --compiler-flags "-Ofast -march=native" --yes DLIB_NO_GUI_SUPPORT --no DLIB_USE_CUDA --yes USE_AVX_INSTRUCTIONS
    $ ls dist/*.whl



Object Tracker
========================================

Dlib 內建就有叫做 `Correlation Tracker <https://github.com/davisking/dlib/blob/master/python_examples/correlation_tracker.py>`_ 的範例，
以下是基於該範例的修改：


.. code-block:: python

  #!/usr/bin/env python3

  import time

  import dlib
  import imageio


  # Create the correlation tracker - the object needs to be initialized
  # before it can be used
  tracker = dlib.correlation_tracker()

  win = dlib.image_window()

  vid = imageio.get_reader('~/video.mp4', 'ffmpeg')
  frame_iter = vid.iter_data()
  img = next(frame_iter)
  # need to initialize the tracker ...
  tracker.start_track(img, dlib.rectangle(234, 57, 352, 143))     # x0 y0 x1 y1

  for img in frame_iter:
     start_time = time.time()
     tracker.update(img)
     win.clear_overlay()
     win.set_image(img)
     win.add_overlay(tracker.get_position())
     print('frame motion tracked in {} seconds'.format(time.time() - start_time))



待研究
========================================

* OpenCL 支援



參考
========================================

* `Wikipedia - Dlib <https://en.wikipedia.org/wiki/Dlib>`_
* `Dlib Blog <http://blog.dlib.net/>`_
    - `A Clean C++11 Deep Learning API <http://blog.dlib.net/2016/06/a-clean-c11-deep-learning-api.html>`_
    - `Easily Create High Quality Object Detectors with Deep Learning <http://blog.dlib.net/2016/10/easily-create-high-quality-object.html>`_
* `Dlib Android <https://github.com/tzutalin/dlib-android>`_
