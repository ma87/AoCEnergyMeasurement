#!/usr/bin/env python3

import os
import re

R = re.compile(r'#(\d+) @ (\d+),(\d+): (\d+)x(\d+)')

def get_line_values(line):
    return tuple(map(int, R.match(line.strip()).groups()))


N = 1000
fabric = [0] * N
for i in range(N):
    fabric[i] = [0] * N

with open('input') as f:
    for line in f:
        cid, left_offset, top_offset, width, height = get_line_values(line)
        
        for i in range(left_offset, left_offset + width):
            for j in range(top_offset, top_offset + height):
                fabric[i][j] += 1

with open('input') as f:
    for line in f:
        cid, left_offset, top_offset, width, height = get_line_values(line)
        
        overlap = 0
        for i in range(left_offset, left_offset + width):
            for j in range(top_offset, top_offset + height):
                if fabric[i][j] > 1:
                    overlap = 1
                    break
            if overlap:
                break
        if not overlap:
            print(cid)

