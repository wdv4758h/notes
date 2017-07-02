K-Means
===============================================================================

*n* point seperated into *k* groups.


Init
----------------------------------------------------------------------

- 任意分 k groups 或
- 任意用 k 個 data point 作為 initial center (seed points)


Meta Algo
----------------------------------------------------------------------

For each iteration:

#. recalculate groups center
#. change delegation. For each point, delegate it to the nearest center

Stop rule:

- continuously same delegation twice
- Or, hit the max iteration user assigned


e.g. Assume we have following data set:

.. math::
    \{1, 2, 3, 4, 11, 12\}


Iteration
----------------------------------------------------------------------

The both action in an iteration can reduce TSSE (total sum of square error).

#. 給定任意集合，則用幾何中心作為代表，TSSE 最小。用偏微方證明。
#. change delegation 是因為 :math:`|X - C_{new}| < |X - C_{orig}|`


Convergency
----------------------------------------------------------------------

K-mean *MUST* converge.

Any iteration in this algo will not be repeated.
The TSSE is always less then previous.

.. math::

    \text{TSSE}_{new} < \text{TSSE}_{old}

Otherwise, this algo will stop.

.. math::
    \because \text{TSSE}_{new} = \text{TSSE}_{old}


Pros and Cons
----------------------------------------------------------------------

Pros:

- min the TSSE
- workload relative light
- simple algo, easy to implement

Cons:

- min the TSSE may let us fall into local min, not the global min
- the init points affect the result
- cannot avoid noise (outliner)

e.g. loacl min: {98, 99, 100, 101, 102, 154, 200}

Iter 1: k=2, {98, 99, 100, 101, 102, 154}, {200}
Iter 2: same as 1, stop.

.. math::
    \text{TSSE} = 11^2 + 10^2 + 9^2 + 8^2 + 7^2 + 45^2 + 0^2 = 2440 > 1068

The number 1068 came from {98, 99, ..., 102}, {154, 200}.
So the result from k-means isn't the global min.


Cluster Center Initialization Algorithm
----------------------------------------------------------------------

To solve the init points effect.

- apply k-means to _each_ dimension.
- we use standard distribution to find center for _each_ dimension.
- construct clustering string from each dimension.


ISO Data
----------------------------------------------------------------------

when k-means algo stopped,

#. we can drop the groups which contain mush less elements.
   (drop outliners)
#. 
    #. the # of groups too less (e.g. < 0.5*threshold),
       then split the large groups.
    #. the # of groups too many (e.g > 2*threshold),
       then merge the similar groups.
    #. else: 某段時間 split; merge
#. restart step 1.
