#!/usr/bin/env python
# -*- coding: utf-8 -*-

from itertools import repeat

fibo_iter = map(lambda _, a=[-1, 1]: a.append(a.pop(0)+a[0]) or a[1], repeat(0))
