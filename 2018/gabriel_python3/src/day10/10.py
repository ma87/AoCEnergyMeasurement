#!/usr/bin/python3


import re
import sys


filename = 'input'

R = re.compile(r'position=<\s*(-?\d+),\s*(-?\d+)> velocity=<\s*(-?\d+),\s*(-?\d+)>')

class Grid(object):
    def __init__(self):
        self.xmin = sys.maxsize
        self.ymin = sys.maxsize
        self.xmax = 1 - sys.maxsize
        self.ymax = 1 - sys.maxsize
        self.last_size = 0

    def reset(self):
        self.last_size = (self.xmax - self.xmin + 1) * (self.ymax - self.ymin + 1)
        self.xmin = sys.maxsize
        self.ymin = sys.maxsize
        self.xmax = 1 - sys.maxsize
        self.ymax = 1 - sys.maxsize

    def update(self, light):
        self.xmin = min(self.xmin, light.x)
        self.ymin = min(self.ymin, light.y)
        self.xmax = max(self.xmax, light.x)
        self.ymax = max(self.ymax, light.y)

    def dump(self, lights):
        x_range = self.xmax - self.xmin + 1
        y_range = self.ymax - self.ymin + 1
        size = (self.xmax - self.xmin + 1) * (self.ymax - self.ymin + 1)
        if size < self.last_size:
            # assert: lights will converge, then diverge
            return False

        M = [''] * (x_range)
        for i in range(x_range):
            M[i] = [' '] * (y_range)

        for light in lights:
            light.advance(-1)
            M[light.x - self.xmin][light.y - self.ymin] = '#'
            
        for y in range(y_range):
            for x in range(x_range):
                print(M[x][y], end='')
            print()

        print('')
        return True


class Light(object):
    def __init__(self, x, y, dx, dy):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy

    def advance(self, time=1):
        self.x += time * self.dx
        self.y += time * self.dy

    def __repr__(self):
        return '{}'.format(self.__dict__)


def parse_line(line):
    x, y, dx, dy = map(int, R.match(line.strip()).groups())
    return Light(x, y, dx, dy)

grid = Grid()
lights = list()
with open(filename) as f:
    for line in f:
        light = parse_line(line)
        lights.append(light)


time = 0
while True:
    grid.reset()
    for light in lights:
        light.advance()
        grid.update(light)
    if grid.dump(lights):
        print(time)
        break
    time += 1
