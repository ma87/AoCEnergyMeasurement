#!/usr/bin/env python3
import sys

filename = 'input'
max_distance = 10000

def manhattan(x, y):
    return abs(y[1] - x[1]) + abs(y[0] - x[0])


# map boundaries
N = sys.maxsize
S = 0
W = sys.maxsize
E = 0

index = 0
coordinates = dict()
with open(filename) as f:
    for line in f:
        # x: W <-> E axis
        # y: N <-> S axis
        x, y = tuple(map(int, line.split(',')))
        W = min(x, W)
        E = max(x, E)
        N = min(y, N)
        S = max(y, S)
        
        coordinates[index] = [x, y, 0]
        index += 1


grid = [0] * (E - W + 1)
for i in range(0, E - W + 1):
    grid[i] = [0] * (S - N + 1)

for x in range(0, E - W + 1):
    for y in range(0, S - N + 1):
        e = (N + x, W + y)
        for k, p in coordinates.items():
            d = manhattan(e, p)
            grid[x][y] += d

region_size = 0
for x in range(0, E - W + 1):
    for y in range(0, S - N + 1):
        region_size += (grid[x][y] < max_distance)

print(region_size)
