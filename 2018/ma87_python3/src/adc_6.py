import sys
import os
import re
import operator

if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]

def get_max_coords(coords):
    max_x = max([c.x for c in coords])
    max_y = max([c.y for c in coords])
    return (max_x + 1, max_y + 1)

class Coords():
    def __init__(self,x,y):
        self.x = x
        self.y = y

directions = [Coords(1,0),  # RIGHT
              Coords(-1,0), # LEFT
              Coords(0,1),  # DOWN
              Coords(0,-1), # UP
             ]

areas = []

def out_of_grid(new_c, grid):
    if new_c.x < 0 or new_c.y < 0:
        return True
    if new_c.x >= len(grid[0]) or new_c.y >= len(grid):
        return True
    return False

def check_grid(area, coord, distance, grid):
    state_grid = grid[coord.y][coord.x]
    if state_grid[0] == '0':
        grid[coord.y][coord.x] = (str(area.id), distance)
        return True
    elif state_grid[0] == '.':
        if state_grid[1] > distance:
            grid[coord.y][coord.x] = (str(area.id), distance)
            return True
        return False
    else:
        if state_grid[1] > distance:
            grid[coord.y][coord.x] = (str(area.id), distance)
            for a in areas:
                if a.id == state_grid[0]:
                    a.size -= 1
            return True
        elif state_grid[1] == distance and state_grid[0] != str(area.id):
            grid[coord.y][coord.x] = ('.', distance)
            for a in areas:
                if str(a.id) == state_grid[0]:
                    a.size -= 1
            return False
        else:
            return False

def print_grid(grid):
    for rows in grid:
        for col in rows:
            print(col[0], end='')
        print('')


class Area():
    def __init__(self, id, start_coord):
        self.id = id
        self.size = 1
        self.isinfinite = False
        self.edges = [(start_coord, 0)]
        self.isexpanding = True

    def expand(self, grid):
        new_edges = []
        for e in self.edges:
            for d in directions:
                new_c = Coords(e[0].x + d.x, e[0].y + d.y)
                new_distance = e[1] + 1
                if out_of_grid(new_c, grid):
                    self.isinfinite = True
                elif check_grid(self, new_c, new_distance, grid):
                    new_edges.append((new_c, new_distance))
                    self.size += 1
        if len(new_edges) > 0:
            self.edges = new_edges[:]
        else:
            self.edges.clear()
            self.isexpanding = False

def get_distance(a, b):
    return abs(a.x - b.x) + abs(a.y - b.y)

def get_total_distance(coords, c):
    total_distance = 0
    for l in coords:
        total_distance += get_distance(c, l)
    return total_distance

def get_solution_2(coords, grid):
    size = 0
    
    for y, rows in enumerate(grid):
        for x, col in enumerate(rows):
            if sum([get_distance(Coords(x,y), c) for c in coords]) < 10000:
                size += 1
    return size

with open(filename, 'r') as f:
    contents = f.readlines()
    location_reg_exp = re.compile(r'(\d+), (\d+)')
    coords = [] # [Coords(int(x),int(y)) for location in contents for x , y in tuple(location_reg_exp.match(location).groups())]
    for i, location in enumerate(contents, start=1):
        x , y = tuple(location_reg_exp.match(location).groups())
        c = Coords(int(x),int(y))
        coords.append(c)
        areas.append(Area(i, c))

    max_x , max_y = get_max_coords(coords)

    grid = [[('0', 0)] * max_x for i in range(max_y)]
    for a in areas:
        grid[a.edges[0][0].y][a.edges[0][0].x] = (str(a.id), 0)

    grid_2 = grid[:]
    is_expanding = True
    counter = 3
    while is_expanding:
        is_expanding = False
        for a in areas:
            a.expand(grid)
            is_expanding |= a.isexpanding

#print_grid(grid)
print("solution 1 = " + str(max([a.size for a in areas if not a.isinfinite])))
print("solution 2 = " + str(get_solution_2(coords, grid_2)))
