.. _taylor-expansion:

Taylor Expansion
===============================================================================

首先 recall `first fundamental theroem of calculus`:

.. math::

    f(b) - f(a) = \int_a^b f'(t) \,dt

其中一個等效形式：

.. math::

    f(b) - f(a) & =      \int_0^{b-a} f'(t + a) \,dt \\
    f(b)        & = f(a) \int_0^{b-a} f'(t + a) \,dt

然後現在做點代換，
Let :math:`a = x, b = x + h`

而且 nested apply 上面的等效形式。

.. math::

    f(x + h)
        & = f(x) + \int_0^h f'(t + x) \,dt \\
        & = f(x) + \int_0^h f'(x + t) \,dt \\
        & = f(x) + \int_0^h \Big( f'(x) + \int_0^t f''(x + s) ds \Big) \,dt \\
        & = f(x) + \int_0^h f'(x) \,dt + \int_0^h \int_0^t f''(x + s) \,ds \,dt \\
        & = f(x) + f'(x)h + \int_0^h \int_0^t f''(x + s) \,ds \,dt \\
        & = f(x) + f'(x)h + \int_0^h \int_0^t \Big( f''(x) + \int_0^s f'''(x + u) \,du \Big) \,ds \,dt \\
        & = f(x) + f'(x)h + \int_0^h \int_0^t f''(x) \,ds \,dt + \int_0^h \int_0^t \int_0^s f'''(x + u) \,du \,ds \,dt \\
        & = f(x) + f'(x)h + \int_0^h f''(x)t \,dt + \int_0^h \int_0^t \int_0^s f'''(x + u) \,du \,ds \,dt \\
        & = f(x) + f'(x)h + \frac{f''(x)}{2}h^2 + \int_0^h \int_0^t \int_0^s f'''(x + u) \,du \,ds \,dt \\
        & \vdots \\
        & = f(x) + \frac{f'(x)}{1!}h + \frac{f''(x)}{2!}h^2 + \frac{f'''(x)}{3!}h^3 + \dots \\
        & = \sum_{n=0}^{\infty} \frac{f^{(n)}(x)}{n!}h^n

等效形式長這樣

.. math::

    f(x) = \sum_{n=0}^{\infty} \frac{f^{(n)}(a)}{n!}(x - a)^n

就是對 :math:`a` 這點做展開，可以作爲 :math:`a` 點附近的 approximation。

Linear Taylor approximation

    .. math::

        f(x) \approx f(a) + f'(a)(x - a)

Quadratic Taylor approximation

    .. math::

        f(x) \approx f(a) + f'(a)(x - a) + \frac{1}{2}f''(a)(x - a)^2


Multiple Dimension
----------------------------------------------------------------------

我們的 input 變成這樣 :math:`\vec{x} = [x_1 x_2]^\mathsf{T}`
所以

.. math::

    \nabla f(\vec{x}) & =
    \begin{bmatrix}
        \nabla_{x_1}f(\vec{x}) \\
        \nabla_{x_2}f(\vec{x})
    \end{bmatrix} \\
    \nabla^2 f(\vec{x}) & =
    \begin{bmatrix}
        \nabla_{x_1 x_1} f(\vec{x}) & \nabla_{x_1 x_2} f(\vec{x}) \\
        \nabla_{x_2 x_1} f(\vec{x}) & \nabla_{x_2 x_2} f(\vec{x})
    \end{bmatrix} \\
    & = H(\vec{x})

Where :math:`H(\vec{x})` denote `Hessian matrix`.

Taylor Expansion:

.. math::

    f(\vec{x}) = f(\vec{a}) +
        \nabla f(\vec{x})^\mathsf{T} (\vec{x} - \vec{a}) +
        \frac{1}{2} (\vec{x} - \vec{a})^\mathsf{T} \, \nabla^2 f(\vec{x})
        \, (\vec{x} - \vec{a}) + \dots


Try
----------------------------------------------------------------------


.. literalinclude:: ./code/taylor.jl
   :language: julia

.. image:: ./img/taylor.gif
