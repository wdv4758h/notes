#!/usr/bin/env python3

'''
Station : http://www.checkio.org/station/mine/
Problem : http://www.checkio.org/mission/flatten-list/
'''

########################################
# version 1, yield
########################################

flat_list = lambda l: list(filter(lambda x: x is not None, ((yield from flat_list(i)) if isinstance(i, list) else i for i in l)))


########################################
# version 2, iterator, chain & map
########################################

from itertools import chain
flat_iter = lambda data: chain(*map(lambda x: flat_iter(x) if hasattr(x, '__iter__') else iter((x,)), data))
flat_list = lambda l: list(flat_iter(l))
