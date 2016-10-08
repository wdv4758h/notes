#!/usr/bin/env python

'''
Use specific argument names to pass in resources automatically.
Use ``py.test --fixtures`` to show what you can use.
'''


def test_f(tmpdir):
    '''
    tmpdir
    '''

    print("temporary directory", tmpdir)
    assert False
