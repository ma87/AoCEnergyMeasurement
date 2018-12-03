#!/usr/bin/env python3

import os
from collections import Counter

def chksum(filename):
    twices = 0
    trices = 0
    with open(filename) as fin:
        for line in fin:
            tw = 0
            tr = 0
            for l, n in Counter(line).most_common():
                if n == 3:
                    tr = 1
                elif n == 2:
                    tw = 1
                    break
            twices += tw
            trices += tr

    return twices * trices

print(chksum('input'))
