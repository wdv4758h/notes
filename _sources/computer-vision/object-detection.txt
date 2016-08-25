========================================
Object Detection
========================================

Viola–Jones object detection framework
========================================

(直接把我電腦視覺期末 Project 寫的紀錄放進來 :P)

----

**Viola–Jones object detection framework** is a **real-time** object detection framework proposed in 2001 by Paul Viola and Michael Jones.

There are 4 primary steps :

* Haar Features Selection
* Creating Integral Image
* Adaboost Training algorithm
* Cascaded Classifiers

Haar Features Selection
------------------------------

**Haar features** consider adjacent rectangular regions at a specific location in a detection window,
sums up the pixel intensities in each region and calculates the difference between these sums.

The advantage of using Haar features is the **fast calculation speed**.

A Haar feature is a rectangular region in the integral image,
so you will need to know the position of the starting and ending point.

like this : ::

    +-----------------+         +-----------------+
    |                 |         |       +-------+ |
    |  +---+---+      |         |       |///////| |
    |  |...|///|      |         |       +-------+ |
    |  |...|///|      |         |       |.......| |
    |  |...|///|      |         |       +-------+ |
    |  |...|///|      |         |      B          |
    |  +---+---+      |         |                 |
    |           A     |         |                 |
    +-----------------+         +-----------------+



    +-----------------+         +-----------------+
    |                 |         |      +---+---+  |
    |                 |         |      |///|...|  |
    |                 |         |      |///|...|  |
    | C               |         |      +---+---+  |
    |  +---+---+---+  |         |      |...|///|  |
    |  |...|///|...|  |         |      |...|///|  |
    |  |...|///|...|  |         |      +---+---+  |
    |  +---+---+---+  |         |     D           |
    +-----------------+         +-----------------+

* for A we need to know **6** points' integral value
* for B we need to know **6** points' integral value
* for C we need to know **8** points' integral value
* for D we need to know **9** points' integral value

By this method, we can get **characteristic difference values** (specific regions' value) by simple calculation.

We can use these kind of features to indicate what does the object looks like.

For example, we can calculate ``the sum of "." area`` minus ``the sum of "/" area``,
then we will get a single value.
Now we can compare the single value with the threshold.
If it pass the threshold, we vote it (we guess that's what we want).

Each subframe is 24x24 pixels, so possible features are 162336.

Here is a example for calculate features (example subframe is 4x4) :

::

    features type : 2x1, 1x2, 3x1, 1x3, 2x2

    2x1 shapes:
            size: 2x1 => count: 12
            size: 2x2 => count: 9
            size: 2x3 => count: 6
            size: 2x4 => count: 3
            size: 4x1 => count: 4
            size: 4x2 => count: 3
            size: 4x3 => count: 2
            size: 4x4 => count: 1
    1x2 shapes:
            size: 1x2 => count: 12             +-----------------------+
            size: 1x4 => count: 4              |     |     |     |     |
            size: 2x2 => count: 9              |     |     |     |     |
            size: 2x4 => count: 3              +-----+-----+-----+-----+
            size: 3x2 => count: 6              |     |     |     |     |
            size: 3x4 => count: 2              |     |     |     |     |
            size: 4x2 => count: 3              +-----+-----+-----+-----+
            size: 4x4 => count: 1              |     |     |     |     |
    3x1 shapes:                                |     |     |     |     |
            size: 3x1 => count: 8              +-----+-----+-----+-----+
            size: 3x2 => count: 6              |     |     |     |     |
            size: 3x3 => count: 4              |     |     |     |     |
            size: 3x4 => count: 2              +-----------------------+
    1x3 shapes:
            size: 1x3 => count: 8                  Total Count = 136
            size: 2x3 => count: 6
            size: 3x3 => count: 4
            size: 4x3 => count: 2
    2x2 shapes:
            size: 2x2 => count: 9
            size: 2x4 => count: 3
            size: 4x2 => count: 3
            size: 4x4 => count: 1


Creating Integral Image
------------------------------

In **integral image**,
each pixel is the sum of all pixels in the original image which are left and above.

like this : ::

    Original        Integral

    1, 2, 3         0,  0,  0,  0
    4, 5, 6         0,  1,  3,  6
    7, 8, 9         0,  5, 12, 21
                    0, 12, 27, 45

calculation : ::

    Original        Integral

    1, 2, 3         0,  0,  0,  0
    4, 5, 6         0,   ,   ,
    7, 8, 9         0,   ,   ,
                    0,   ,   ,



    Original        Integral

    ( 1 ), 2, 3         0, ( 0 ),  0,  0
        4, 5, 6     ( 0 ), [ 1 ],   ,
        7, 8, 9         0,      ,   ,
                        0,      ,   ,

            calculation : 0 + 0 + 1 = 1



    Original        Integral

    1, ( 2 ), 3     0,   0  , ( 0 ),  0
    4,     5, 6     0, ( 1 ), [ 3 ],
    7,     8, 9     0,      ,      ,
                    0,      ,      ,

            calculation : 0 + 1 + 2 = 3



    Original        Integral

    1, 2, ( 3 )     0, 0,     0, ( 0 )
    4, 5,     6     0, 1, ( 3 ), [ 6 ]
    7, 8,     9     0,  ,      ,
                    0,  ,      ,

            calculation : 0 + 3 + 3 = 6



    Original        Integral

        1, 2, 3         0,     0, 0, 0
    ( 4 ), 5, 6         0, ( 1 ), 3, 6
        7, 8, 9     ( 0 ), [ 5 ], ,
                        0,      , ,

            calculation : 1 + 0 + 4 = 5


    ...


    Original        Integral

    1, 2, 3         0,  0,  0,  0
    4, 5, 6         0,  1,  3,  6
    7, 8, 9         0,  5, 12, 21
                    0, 12, 27, 45


Adaboost Training algorithm
------------------------------

**AdaBoost** was introduced in 1995 by Freund and Schapire, it's a machine learning algorithm which can collaborate with many other types of learning algorithms to improve their performance.

The concept is to combine some **weak classifier** into a weighted sum to make a **strong classifier**.

AdaBoost use weighted majority vote (or sum) to produce the final prediction.


Assume we have N training images (positive and negative),
we lable them with 1 or -1 (1, if the image is what we want, otherwise -1).

We iterate through the features (16K) to find out best N Haar features,
then we start training with these N features.
We give a weighting variable to every features (N features) to tune the result.
Now we start voting. By changing the weighting variable, we can minimize the error of the voting result.

Finally, we get a better result. Now we can output the model to an xml for using next time.


Cascaded Classifiers
------------------------------

* 1st layer, A simple **2-feature classifier** can achieve **almost 100% detection rate** with **50% false positive rate**.
    - if it's what we want, it will pass (almost 100% detection rate)
    - if it's not what we want, it will have 50% probability to pass
    - this can fast filter the data
* 2nd layer, 10 features, less false positive rate P%
    - if it's what we want, it will pass (almost 100% detection rate)
    - if it's not what we want, it will have P% probability to pass
    - now the overall false positive rate is (50% * P%)
* 3rd layer, X features, less false positive rate Q%
    - if it's what we want, it will pass (almost 100% detection rate)
    - if it's not what we want, it will have Q% probability to pass
    - now the overall false positive rate is (50% * P% * Q%)


::

    +-----------+       +---------+       +---------+       +---------+           +---------+       +------+
    |           |       |         |       |         |       |         |           |         |       |      |
    | sub image | ----> | stage 1 | ----> | stage 2 | ----> | stage 3 | ... ----> | stage n | --->  | Pass |
    |           |       |         |       |         |       |         |           |         |       |      |
    +-----------+       +---------+       +---------+       +---------+           +---------+       +------+
                            |                  |                 |                     |
                            |                  |                 |                     |
                            v                  v                 v                     v
            +----------------------------------------------------------------------------------+
            |                                                                                  |
            |                                      Reject                                      |
            |                                                                                  |
            +----------------------------------------------------------------------------------+


Reference
------------------------------

* `Wikipedia - Viola–Jones object detection framework <https://en.wikipedia.org/wiki/Viola%E2%80%93Jones_object_detection_framework>`_
* `Wikipedia - Haar-like features <https://en.wikipedia.org/wiki/Haar-like_features>`_
* `Wikipedia - AdaBoost <https://en.wikipedia.org/wiki/AdaBoost>`_
* `scikit-learn - AdaBoost <http://scikit-learn.org/stable/modules/ensemble.html#adaboost>`_
* `Robust Real-time Object Detection <http://lear.inrialpes.fr/people/triggs/student/vj/viola-ijcv04.pdf>`_
* `StackOverflow - Viola-Jones' face detection claims 180k features <http://stackoverflow.com/questions/1707620/viola-jones-face-detection-claims-180k-features>`_
* `OpenCV Face Detection: Visualized <https://vimeo.com/12774628>`_


Fun
========================================

* `PyCON APC 2015 - Marsface Project: Detecting Pseudo-artificial Structures on Mars <https://www.youtube.com/watch?v=XsinyMyoZPU>`_
