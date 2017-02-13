Standard Library
===============================================================================


``multiproccessing.pool``
----------------------------------------------------------------------

``map``, ``imap`` 或其他 variants 不適合用在每個 工作量不一致 的狀況上，
因為 ``map`` 會根據 ``chunck_size`` 這個參數 *預先* 切割好 iterable ，
即 iterable 會被 early evaluated ，而不會 lazy 的去拿工作。

stdlib (3.6) 目前沒辦法解上面的問題，要自己刻 producer & consumer 。

Ref: https://stackoverflow.com/questions/5318936/python-multiprocessing-pool-lazy-iteration
