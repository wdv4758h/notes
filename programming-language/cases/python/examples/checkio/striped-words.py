#!/usr/bin/env python3

'''
Station : http://www.checkio.org/station/oreilly/
Problem : http://www.checkio.org/mission/striped-words/
'''

########################################
# version 1, re.fullmatch (Python 3.4+)
########################################

import re

p1 = "AEIOUY"
p2 = "BCDFGHJKLMNPQRSTVWXZ"

checkio = lambda s: len(tuple(filter(lambda x: re.fullmatch('[{}]?([{}][{}])+|[{}]?([{}][{}])+'.format(p1, p2, p1, p2, p1, p2), x), s.upper().replace(',', ' ').replace('?', ' ').replace('.', ' ').split())))


########################################
# version 2, re.match
########################################

import re

p1 = "AEIOUY"
p2 = "BCDFGHJKLMNPQRSTVWXZ"

checkio = lambda s: len(tuple(filter(lambda x: re.match('^([{}]?([{}][{}])+|[{}]?([{}][{}])+)$'.format(p1, p2, p1, p2, p1, p2), x), s.upper().replace(',', ' ').replace('?', ' ').replace('.', ' ').split())))


########################################
# version 3, str.translate
########################################

import re

p1 = "AEIOUY"
p2 = "BCDFGHJKLMNPQRSTVWXZ"

checkio = lambda s: len(tuple(filter(lambda x: re.match('^[{p1}]?([{p2}][{p1}])*[{p2}]?$'.format(p1=p1, p2=p2), x) and len(x) > 1, s.upper().translate({ord(i): ' ' for i in ',?.'}).split())))
