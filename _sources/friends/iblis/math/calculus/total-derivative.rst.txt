Total Derivative
===============================================================================
.. math::

    \text{Let } f(x, y) = xy

如果 :math:`x, y` 之間為 independent。
則

.. math::

    \frac{df}{dx} = y \\
    \frac{df}{dy} = x

如果 :math:`x, y` 之間有 dependent，假設關係為 :math:`y = x`
則

.. math::

    f(x, y) = xy = x^2 \\
    \frac{df}{dx} = 2x

其實上面的 :math:`\frac{df}{dx}` 可以用 chain rule 寫成

.. math::

    \frac{df}{dx} & =
        \frac{\partial f}{\partial x} +
        \frac{\partial f}{\partial y} \frac{dy}{dx} \\
        & =
        \frac{\partial f}{\partial x} +
        \frac{\partial f}{\partial y} \times 1 \\
        & =
        \frac{\partial f}{\partial x} +
        x times 1 \\
        & =
        y + x \\
        & =
        2x

簡單來說就是有 dependent，需要 chain rule，而直接寫出 chain rule 即是
general form，因為 independent 的 chain rule 項就直接是 0。

Ref
----------------------------------------------------------------------

- https://en.wikipedia.org/wiki/Total_derivative
