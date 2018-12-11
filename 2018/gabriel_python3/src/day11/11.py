#!/usr/bin/env python3

import sys

def get_hundredth_digit(number):
    try:
        return int(str(number)[-3])
    except IndexError:
        return 0

def power_cell(serial, x, y):
    rack_id = x + 10
    power_level = rack_id * y
    power = power_level + serial
    hundred = get_hundredth_digit(power * rack_id)
    return hundred - 5


def area_power(grid, x, y):
    try:
        power = 0
        for i in range(-1, 2):
            for j in range(-1, 2):
                power += grid[x + i][y + j]
        return power
    except IndexError:
        return 1 - sys.maxsize

def puzzle(serial_number):
    grid = [0] * 300
    for i in range(300):
        grid[i] = [0] * 300
    
    for x in range(300):
        for y in range(300):
            grid[x][y] = power_cell(serial_number, x + 1, y + 1)
            
    max_power = 1 - sys.maxsize
    max_coordinates = (None, None)
    for x in range(1, 300):
        for y in range(1, 300):
            tmp = area_power(grid, x, y)
            if tmp > max_power:
                max_power = tmp
                max_coordinates = (x, y)
    
    return max_power, max_coordinates

#print(18, puzzle(18))  # (29, (33, 45))
#print(42, puzzle(42))  # (30, (21, 61))
print(7689, puzzle(7689))
