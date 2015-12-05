#!/usr/bin/env python
# -*- coding: utf-8 -*-

from contextlib import redirect_stdout  # since 3.4
from contextlib import contextmanager
from io import StringIO
import sys


def f1():
    s = StringIO()
    with redirect_stdout(s):
        print(42)

    print('='*20)
    print(s.getvalue(), end='')
    print('='*20)


def f2():
    s = StringIO()

    stdout = sys.stdout
    sys.stdout = s

    print(42)

    sys.stdout = stdout

    print('='*20)
    print(s.getvalue(), end='')
    print('='*20)


def f3():

    @contextmanager
    def redirect(stream):
        stdout = sys.stdout
        sys.stdout = stream
        try:
            yield
        finally:
            sys.stdout = stdout

    s = StringIO()
    with redirect(s):
        print(42)

    print('='*20)
    print(s.getvalue(), end='')
    print('='*20)


if __name__ == '__main__':
    f1()
    f2()
    f3()
