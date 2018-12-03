#!/usr/bin/env python3

import os
from collections import Counter

def hamming(s1, s2): 
    d = 0
    L = len(s1)
    for i in range(L):
        if s1[i] != s2[i]:
            d += 1
    return d


def file2set(filename):
    s = set()
    with open(filename) as fin:
        for line in fin:
            s.add(line)

    return s


S = file2set('input')
for x in S:
    for y in S:
        if hamming(x, y) == 1:
            for i in range(len(x)):
                if x[i] != y[i]:
                    print(x[:i], x[(i + 1):])
                    exit(0)
