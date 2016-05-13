========================================
Information For Your Report
========================================

* `Week Numbers <http://www.epochconverter.com/date-and-time/weeknumbers-by-year.php>`_
* `What's the Current Week Number? <http://www.epochconverter.com/weeknumbers>`_


Python :

.. code-block:: python

    import datetime
    datetime.date.today().isocalendar()[1]

.. code-block:: sh

    python -c "import datetime; print('Week', datetime.date.today().isocalendar()[1])"
