#!/usr/bin/env python3

filename = 'input'

freq = 0
with open(filename) as f:
    for line in f:
        freq += int(line)

print(freq)
