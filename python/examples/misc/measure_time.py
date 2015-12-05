#!/usr/bin/env python
# -*- coding: utf-8 -*-

import timeit
import time
import cProfile
from functools import partial
from contextlib import contextmanager


def f1():
    return 42


def f2(x):
    return x+1


def wrapper(func, *args, **kwargs):
    def wrapped():
        return func(*args, **kwargs)
    return wrapped


def measure_time(func, *args, **kwargs):
    start = time.perf_counter()
    for i in range(1000000):
        func(*args, **kwargs)
    end = time.perf_counter()
    return end - start


@contextmanager
def measure_time_context():
    start = time.perf_counter()
    yield
    end = time.perf_counter()
    print(end - start)


class Timer(object):

    def __enter__(self):
        self.start = time.perf_counter()

    def __exit__(self, type, value, traceback):
        self.end = time.perf_counter()

    def duration_in_seconds(self):
        return self.end - self.start


def self_timer_context(func, *args, **kwargs):
    timer = Timer()

    with timer:
        for i in range(1000000):
            func(*args, **kwargs)

    return timer.duration_in_seconds()


if __name__ == '__main__':
    # timeit.timeit(stmt, setup, timer, number, globals)

    print(timeit.timeit(f1))
    print(timeit.timeit('f2(42)', 'from measure_time import f2'))
    print(timeit.timeit('f2(42)', globals=globals()))
    print(timeit.timeit(wrapper(f2, 42)))
    print(timeit.timeit(partial(f2, 42)))
    print(timeit.timeit(partial(f2, 42), number=2000000))
    print(measure_time(f2, 42))

    with measure_time_context():
        for i in range(1000000):
            f2(42)

    print(self_timer_context(f2, 42))

    cProfile.run('f2(42)')
    cProfile.run('[f2(42) for i in range(1000000)]')
    cProfile.run('[f2(42) for i in range(1000000)]', sort='tottime')
