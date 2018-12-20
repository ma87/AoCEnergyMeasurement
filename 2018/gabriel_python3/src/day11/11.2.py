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


def area_power(grid, x, y, size):
    # TODO: replace with incremental sum
    power = 0
    for i in range(size):
        for j in range(size):
            power += grid[x + i][y + j]
    return power


def puzzle(serial_number):
    grid = [0] * 300
    for i in range(300):
        grid[i] = [0] * 300

    for x in range(300):
        for y in range(300):
            grid[x][y] = power_cell(serial_number, x + 1, y + 1)

    max_power = 1 - sys.maxsize
    max_coordinates = (None, None)
    max_size = None
    for x in range(0, 300):
        for y in range(0, 300):
            for size in range(1, 300):  # score decreases after 25
                try:
                    tmp = area_power(grid, x, y, size)
                    if tmp > max_power:
                        max_power = tmp
                        max_coordinates = (x + 1, y + 1)
                        max_size = size
                except IndexError:
                    break
            # print('DBG', x, y, max_power, max_coordinates, max_size)

    return max_power, max_coordinates, max_size

# print(18, puzzle(18))  # (113, (90, 269), 16)
# print(42, puzzle(42))  # (119, (232, 251), 12)
print(7689, puzzle(7689))
