#!/usr/bin/env python3

'''
Station : https://www.checkio.org/station/scientific-expedition/
Problem : https://www.checkio.org/mission/fibonacci-golf/
'''

########################################
# version 1
########################################

def g(a=1,b=1,c=0,s=[0,1,1]):
    s=s.copy()
    def f(n):
        while len(s)<=n:
            s.append(a*s[-1]+b*s[-2]+c*s[-3])
        return s[n]
    return f

d={'fib':g(),'tri':g(c=1),'luc':g(s=[2,1,3]),'jac':g(1,2,0),'pel':g(2,s=[0,1,2]),'per':g(0,1,1,[3,0,2]),'pad':g(0,1,1)}

fibgolf=lambda f,n:d[f[:3]](n)

########################################
# version 2, compress version 1
########################################

def g(a=1,b=1,c=0,s=[0,1,1]):
    def f(n,s=s.copy()):
        while len(s)<=n:s.append(a*s[-1]+b*s[-2]+c*s[-3])
        return s[n]
    return f
fibgolf=lambda f,n:{'fib':g(),'tri':g(c=1),'luc':g(s=[2,1,3]),'jac':g(1,2,0),'pel':g(2,s=[0,1,2]),'per':g(0,1,1,[3,0,2]),'pad':g(0,1,1)}[f[:3]](n)

########################################
# version 3, iterator [WIP]
########################################

# too long for this problem ...
from itertools import repeat,chain,islice
def g(a=1,b=1,c=0,s=[0,1,1]):
    def f(n,s=s.copy()): return tuple(islice(chain(iter(s),map(lambda _,s=s:s.extend((s[1],s[2],a*s.pop()+b*s.pop()+c*s.pop()))or s[-1],repeat(0))),n+1))[-1]
    return f
fibgolf=lambda f,n:{'fib':g(),'tri':g(c=1),'luc':g(s=[2,1,3]),'jac':g(1,2,0),'pel':g(2,s=[0,1,2]),'per':g(0,1,1,[3,0,2]),'pad':g(0,1,1)}[f[:3]](n)
