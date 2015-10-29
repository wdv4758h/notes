========================================
matplotlib
========================================

Console Only (Output Image Files)
========================================

.. code-block:: python

    import matplotlib
    matplotlib.use('Agg')   # PNG


Example (輸出成 PNG 檔) :

.. code-block:: python

    import matplotlib
    matplotlib.use('Agg')   # PNG

    import matplotlib.pyplot as plt
    import matplotlib.image as mpimg

    img = mpimg.imread('input.png')
    plt.hist(img.ravel(), 256, [0,256])
    plt.savefig('test.png')


* `matplotlib - What is a backend? <http://matplotlib.org/faq/usage_faq.html#what-is-a-backend>`_
