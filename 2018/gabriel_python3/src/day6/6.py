#!/usr/bin/env python3
import sys

filename = 'input'

def manhattan(x, y):
    return abs(y[1] - x[1]) + abs(y[0] - x[0])


# map boundaries
N = sys.maxsize
S = 0
W = sys.maxsize
E = 0

index = 0
coordinates = {-1: [0, 0, 0]}
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
    grid[i] = [(0, sys.maxsize)] * (S - N + 1)

for x in range(0, E - W + 1):
    for y in range(0, S - N + 1):
        e = (N + x, W + y)
        for k, p in coordinates.items():
            d = manhattan(e, p)
            dmin = grid[x][y][1]
            if d < dmin:
                grid[x][y] = (k, d)
        for k, p in coordinates.items():
            d = manhattan(e, p)
            kmin, dmin = grid[x][y]
            if kmin != k and d == dmin:
                grid[x][y] = (-1, 0)

for x in range(0, E - W + 1):
    for y in range(0, S - N + 1):
        kmin, _ = grid[x][y]
        coordinates[kmin][2] += 1

max_area_sz = 0
for _, p in coordinates.items():
    x, y, area_sz = p
    if x == W or x == E or y == N or y == S:
        continue
    max_area_sz = max(max_area_sz, area_sz)


print(max_area_sz)
