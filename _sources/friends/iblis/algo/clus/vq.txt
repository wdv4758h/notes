Vector Quantization
===============================================================================

If we want to transfer 10000 vector data

.. math::

    \{\vec{x_1}, \vec{x_2}, \dots, \vec{x_{10000}}\}

.. math::

    \forall \vec{x} \text{ is high-dimension (e.g. 16-dim).}


Problem
----------------------------------------------------------------------

How to speed up the data transfer?
If we can accept error;
we can accept losely transfer.


Solution
----------------------------------------------------------------------

We can use VQ for data compression.

First, we can cluster vectors into 8 clusters.
Then we get 8 centroid.

Thus, we only need to transfer
:math:`\{ \vec{centroid_0}, \dots, \vec{centroid_7} \}`
and 10,000 numbers which represent the cluster belongs to.

And, :math:`\forall` 10,000 numbers, it only 3 bits to transfer (000 - 111).


Results
----------------------------------------------------------------------
This method will get high transfer speed, but the error is quite larger.

.. note::
    This 8 cluster centroids are so-called *codebook*.
    Each centroid is a *codeword* (*codevector*).


Codebook Generation
----------------------------------------------------------------------

The commonly used Linde-Buzo-Gray (LBG) algorithm to create codebook.

*In fact, it is k-means*.


Conclusion
----------------------------------------------------------------------

- If centroid come from known public data, then your vector data called
  *Outside Data*.(Data may irrelavent to centroid)

- If codebook is generated from data, we call them *Inside Data*.
  Then, the error will be lower, but the transfer cost raises.


e.g.: Assume we use our own codebook

- Data --> *clustering* --> 8 clusters

- Data --> *classification* --> more near to which cluster


Side-Matched VQ (SMVQ)
----------------------------------------------------------------------

Goal
    To provide better visual image quality than original VQ.

- Porposed by Kim in 1992


Seed Block
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

最左邊以及最上邊的 :math:`\frac{512}{4} = 128` 個 :math:`4 \times 4` 的
blocks ，共 128 + 128 - 1 = 255 個 blocks 為 seed blocks

seed block 用傳統的 VQ ，且立刻解壓縮（用 codeword 蓋掉 seed blocks）


Example
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

假設照片 (512 x 512) 切成 2-by-2 之區塊
codebook 有 256 個 codewords (8bit for index)

codewords:
    0.
           0 0
           0 0
    #.
           1 1
           1 1

           .. math::

               \dots

    255.
           255 255
           255 255

Compression algorithm:

step 1.
    可平行；
    最上以及最左邊為 seed blocks, 用傳統的 VQ 做壓縮，得到 index file
    ，且立刻解壓縮 (in-place)

step 2.
    部分可平行；剩餘的 250 x 250 blocks 一定要由左至右由上而下依序做。

    上方以及左方至親友團推薦

::

    -
          4 4
          4 4
        + - -
    3 3 | x y
    3 3 | z w


.. math::

    \text{find}

.. math::

    | x - 4 | + | y - 4 | + | x - 3| + | z -3 |
    \text{(親友誤差)}

    \text{最小之候選 codewords}

    得 3 3 與 4 4
       3 3    4 4

再用 original photo 挑出相對好的候選 codeword，且立刻解壓縮


Disscusion
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- "classical blocks" more => the quality of image raise
