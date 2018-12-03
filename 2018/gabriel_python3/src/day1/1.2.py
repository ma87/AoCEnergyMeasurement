#!/usr/bin/env python3

filename = 'input'

freq = 0
freqs = set()
with open(filename) as f:
    for line in f:
        freq += int(line)
        if freq in freqs:
            print(freq)
            exit(0)
        freqs.add(freq)

while True:
    with open(filename) as f:
        for line in f:
            freq += int(line)
            if freq in freqs:
                print(freq)
                exit(0)
