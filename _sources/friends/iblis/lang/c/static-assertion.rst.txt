.. _static-assertion:

Static Assertion
===============================================================================

.. highlight:: c

- compile time evaluated assertion

- compile time assertion will be removed via preproccessor

In C11 standard, use keyword ``_Static_assert``.

In ``assert.h``::

    #define static_assert _Static_assert

Sample::

    #include <assert.h>
    int main()
    {
        static_assert(42, "magic");
        static_assert(0, "some error");
        return 0;
    }
