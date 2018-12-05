#!/usr/bin/env python3

def match (x, y):
    return x.lower() == y.lower() and x != y

def final_reduce(part1, part2):
    if not part1:
        return part2
    elif not part2:
        return part1
    elif match(part1[-1], part2[0]):
        return final_reduce(part1[:-1], part2[1:])
    else:
        return part1 + part2

def reduce(seq):
    l = len(seq)
    if l < 2:
        return seq
    elif l == 2:
        if match(seq[0], seq[1]):
            return ''
        else:
            return seq
    else:
        part1 = seq[:l//2]
        part2 = seq[l//2:]
        rv1 = reduce(part1)
        rv2 = reduce(part2)
        if part1 == rv1 and part2 == rv2:
            return final_reduce(part1, part2)
        else:
            return reduce(rv1 + rv2)


# 10901 too low
filename = 'input'

with open(filename) as f:
    rv = reduce(f.read().strip())
    print(rv, len(rv))
