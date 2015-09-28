========================================
String Optimization
========================================

SSO (Small/Short String Optimization)
========================================

概念：當字串夠短時，直接在物件本身儲存字串，而不是另外再去要一個空間

實作上，一個 String 通常會存有 pointer、size、capacity 三個資料，
當 String 發現字串夠短時，
可以直接把原本用於 pointer、size、capacity 的記憶體空間拿來儲存 char array，
藉此省去動態要空間的消耗。

----

以下是 32-bit 系統上的狀況：


原本：

.. image:: /images/cpp/SSO-origin.png



我們需要一個不合法的 String 表示方式來代表我們正在使用 SSO。
因此我們利用 ``size > capacity`` 這個不正常的狀況。
如果 size 的 MSB (most significant bit) 是 1 而且 capacity 的 MSB 是 0 時，
我們就進入了這個狀況。
搭配 bitshifting，我們把 size 和 capacity 的 MSB 都聚集到一邊 (此時 capacity 會凸出去一個 bit 到 size)，
形成以下情況：

.. image:: /images/cpp/SSO-shift.png



接著我們把前面的 bits 都拿來儲存資料，
因此我們獲得了 11 bytes 的 char array、6 個 bits 儲存 array 長度、2 個 bits 表示 SSO mode：
(此時的 11 bytes 還需要負責儲存結尾的 ``\0``)

.. image:: /images/cpp/SSO-version1.png




現在我們把 array 長度的表示法換一下，
改成 11 - size，
當前面存滿 11 個 bytes 時，
這六個 bits 就會變成 0。
另外我們把一開始 size 的 MSB 改成儲存它的相反值 (取 NOT)，
因此我們會在結尾兩個 bits 是 0 時進入 SSO mode：

.. image:: /images/cpp/SSO-version2.png



此時我們實際可以儲存的資料就多了一個 byte，
因為前面存滿 11 bytes 時我們剩下的一個 byte 會自動變成 ``\0`` ：

.. image:: /images/cpp/SSO-version3.png



* `[GitHub] SSO-23 - Memory optimal Small String Optimization implementation for C++ <https://github.com/elliotgoodrich/SSO-23>`_


CoW
========================================

* http://www.thecodingforums.com/threads/short-string-optimization-vs-cow.868317/
