=============================
Scalable Vector Graphics 筆記
=============================

建立一個 SVG 檔案
-----------------
::

  <svg version="1.1"
      baseProfile="full"
      width="400" height="500"
      xmlns="http://www.w3.org/2000/svg">
  </svg>

MDN 的 SVG Tutorial 建議不要加這些 ::

  <?xml version="1.0"?>
  <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
      "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">


基本形狀們
----------
這裡列出基本的形狀（在 SVG 檔案裡以 Tag 描述）以及它們特有的屬性

* ``text`` - 文字

  - ``x``, ``y`` 為定位點的座標
  - ``text-anchor`` 為定位點在文字的位置

    + ``"middle"`` 會使文字的（左右）中央對齊 ``x`` ，baseline 對齊 ``y``
    + ``"start"`` ``"end"``

  - ``font-size`` 為字體大小
  - ``font-weight="bold"`` 為粗體

* ``rect`` - 長方形

  - ``x``, ``y`` 為左上角的座標
  - ``width``, ``height`` 為長寬
  - ``rx``, ``ry`` 為 x 和 y 軸圓角的半徑

* ``circle`` - 圓圈

  - ``cx``, ``cy``, ``r`` 為圓心和半徑

* ``ellipse`` - 橢圓

  - ``cx``, ``cy`` 為圓心
  - ``rx``, ``ry`` 為 x 和 y 軸的半徑

* ``line`` - 直線

  - ``x1``, ``y1``, ``x2``, ``y2`` 為起始點和終點的座標

* ``polyline`` - 折線，也就是一堆相連的直線

  - ``points`` 為每個折點的座標

    + ``points="60 110 65 120 70 115"``

* ``polygon`` - 多邊形

  - ``points`` 為每個折點的座標

    + ``points="60 110, 65 120, 70 115"``
    + 分隔符號可以用空白或是逗點（不限於這兩個）
    + 最後一個點會自動以直線連上第一個點


線屬性
------
這裡列出線的屬性

* ``stroke`` - 線的顏色

  - ``stroke="black"``

* ``stroke-width`` - 線的寬度
* ``stroke-linecap`` - 線的收尾方式

  - ``"butt"`` 直接切平
  - ``"square"`` 包一個正方形，線的結尾在正方形的中央，效果類似切平再加長一點
  - ``"round"`` 包一個圓形

* ``stroke-linejoin`` - 兩條線折角的連接方式

  - ``"miter"`` 為尖角
  - ``"round"`` 為圓角
  - ``"bevel"`` 為兩個尖角，類似把 ``"miter"`` 的尖角切一個角下來

* ``stroke-dasharray`` - 虛線的寬度

  - ``stroke-dasharray="1,2,3"`` - 實線/虛線的寬度順序

    a.  實線 ``1``
    b.  虛線 ``2``
    c.  實線 ``3``
    d.  虛線 ``1``
    e.  實線 ``2``
    f.  ...

  - 若不是偶數的話會產生奇怪的效果


fill 屬性
---------
* ``fill`` - 把圖形圍繞的區域用顏色填滿

  - ``fill="transparent"`` 為透明
  - ``fill="url(#id1)"`` 使用 ``id1`` 填滿

* ``fill-opacity`` - 填滿的不透明度，在 [0, 1] 之間


``path``
--------
``path`` 是最一般化的形狀，上述所有的形狀都可以用它描述。

``path`` 的形狀只用 ``d`` 屬性，用一連串指令描述一連串的「動作」

*以下變數以* ``{x}`` *表示*

以下指令若改為小寫，則所有的座標都變為相對座標

* ``M {x} {y}``

  - 將游標移動到（Move to）絕對座標 ``{x}`` ``{y}`` 處

* ``L {x} {y}``

  - 從目前位置畫線至（Line to）絕對座標 ``{x}`` ``{y}`` 處
  - ``H {x}`` 水平畫線
  - ``V {y}`` 垂直畫線

* ``Z``

  - 畫直線回到 ``path`` 的起始點

* ``C {x1} {y1} {x2} {y2} {x} {y}`` - 三階（Cubic）貝茲曲線

  - ``{x1} {y1}`` 為第一個控制點的座標
  - ``{x2} {y2}`` 為第二個控制點的座標
  - ``{x} {y}`` 為曲線結束點的座標

* ``Q {x1} {y1} {x} {y}`` - 二階（Quadratic）貝茲曲線

  - ``{x1} {y1}`` 為控制點的座標
  - ``{x} {y}`` 為曲線結束點的座標

* ``A {rx} {ry} {x-axis-rotation} {large-arc-flag} {sweep-flag} {x} {y}`` - 圓弧

  - ``{rx} {ry}`` 為圓弧的半徑
  - ``{x-axis-rotation}`` 為旋轉的角度，以角度表示（而非徑度制）

    + 若設為 ``-45`` ，畫出來的弧形會往左旋轉 45 度

  - ``{large-arc-flag}`` 決定圓弧大小能不能超過 180 度， ``0`` 為不可以， ``1`` 為可以
  - ``{sweep-flag}`` 決定圓弧的順逆時針方向， ``0`` 為逆時針， ``1`` 為順時針
  - ``{x} {y}`` 為圓弧的結束點


與 CSS 結合
-----------
``<defs>`` Tag 中可以加入 ``<style>`` 標籤，並插入 CSS，但不是每個屬性都可以這樣設定

注意即使是用 CSS 定義外觀，在這個狀況下仍不適用 ``background-color`` 和 ``color`` ，需使用 SVG 的屬性 ``fill`` 和 ``stroke``

在 SVG 檔案中可以用 ::

  <?xml-stylesheet type="text/css" href="style.css"?>

抓取外部 CSS 檔案


漸層 - Gradients
----------------
漸層物件使用 ``<xxxGradient>`` 定義，需放在 ``<defs>`` Tag 中，並且一定要帶有 ``id`` 屬性 ::

  <defs>
    <linearGradient id="gradient1">
      ...
    </linearGradient>
  </defs>

漸層裡的每個轉換點使用 ``<stop>`` Tag 定義 ::

  <stop offset="0%" stop-color="red"/>
  <stop offset="50%" stop-color="black" stop-opacity="0"/>
  <stop offset="100%" stop-color="blue"/>

在 ``fill`` 或是 ``stroke`` 屬性中使用 ``url(#id)`` 套用

* ``<linearGradient>`` - 線性漸層

  - 具有 ``x1`` ``y1`` ``x2`` ``y2`` 四個屬性，分別描述漸層的方向
  - 四個值都在 [0, 1] 之間，代表它們所佔的長度比例

* ``<radioGradient>`` - 圓形漸層

  - ``cx`` ``cy`` 為漸層 **形狀** 的中心
  - ``r`` 為漸層半徑
  - ``fx`` ``fy``  為漸層 **顏色** 的中心
  - 這些值也都在 [0, 1] 之間，代表它們所佔的長度比例


圖樣 - Patterns
---------------
圖樣物件使用 ``<pattern>`` 定義，需放在 ``<def>`` 中，並且一定要帶有 ``id`` 屬性

``<pattern>`` 所包的內容可以在 ``fill`` 被重覆顯示

``<pattern>`` 具有 ``x`` ``y`` ``width`` ``height`` 四個屬性，描述一個圖樣的大小


文字 - Texts
------------
文字以 ``<text>`` 定義，在 `基本形狀們`_ 中已有列出部份屬性，以下列出更多相關的 Tags

* ``<tspan>`` - 包在 ``<text>`` 裡面，描述一部份的文字，例如把一串字之中的一些字上色
