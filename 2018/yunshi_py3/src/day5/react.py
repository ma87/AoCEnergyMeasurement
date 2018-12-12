#!/usr/bin/env python3

import string

ORD_DIFF = abs(ord('a') - ord('A'))


def to_remove(a, b):
    return abs(ord(a) - ord(b)) == ORD_DIFF


def trigger_react(data):
    result = []
    for cursor in data:
        if result and to_remove(result[-1], cursor):
            result.pop()
        else:
            result.append(cursor)
    return result


def min_after_react(data):
    return min(
        len(trigger_react(s for s in data if s.lower() != l))
        for l in string.ascii_lowercase
    )


if __name__ == "__main__":
    with open('data', 'r') as infile:
        data = infile.read()
        print('Solution 1 :', len(trigger_react(data)))
        print('Solution 2 :', min_after_react(data))
