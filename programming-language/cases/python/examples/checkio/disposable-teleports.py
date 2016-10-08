#!/usr/bin/env python3

'''
Station : https://www.checkio.org/station/oreilly/
Problem : https://www.checkio.org/mission/disposable-teleports/
'''

########################################
# version 1
########################################

def find_path(current, edges, flags, log=[]):

    flags[current] = True

    if all(flags.values()):
        if log[0] in edges[current]:
            yield log + [current] + [log[0]]
        else:
            return

    for i in edges[current]:
        new_edges = edges.copy()
        new_edges[current] = new_edges[current].copy()
        new_edges[current].remove(i)
        new_edges[i] = new_edges[i].copy()
        new_edges[i].remove(current)
        yield from find_path(i, new_edges, flags.copy(), log + [current])


def checkio(data):
    edges = {}

    for s in data.split(','):
        a, b = (s[0], s[1])
        edges[a] = edges.get(a, []) + [b]
        edges[b] = edges.get(b, []) + [a]

    flags = {i: False for i in edges.keys()}

    return next(map(lambda x: ''.join(x), filter(bool, find_path('1', edges, flags))))
