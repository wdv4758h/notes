#!/usr/bin/env python

'''
you can use this command to run specific Python code:

..code-block:: python

    py.test example1.py

'''


def f(x):
    return x + 1


def test_f():
    assert f(0) == 1
