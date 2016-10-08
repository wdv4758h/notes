#!/usr/bin/env python

'''
you can use ``py.test -x`` to stop after first failure,
or use ``py.test --maxfail=N`` to stop after N failures.
'''

import pytest


def f():
    raise SystemExit(1)


def test_f_fail():
    f()


def test_f_pass():
    with pytest.raises(SystemExit):
        f()
