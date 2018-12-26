import sys
import os
import re
import operator


if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]
class Star:
    def __init__(self, id, x, y, z, t):
        self.id = id
        self.x = x
        self.y = y
        self.z = z
        self.t = t
def manhattan_dist(a,b):
    return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z) + abs(a.t - b.t)
def star_in_constellation(s, c, stars):
    for s_id in c:
        if manhattan_dist(s, stars[s_id]) <= 3:
            return True
    return False

with open(filename, 'r') as f:
    stars = {}
    id = 1
    constellations = {}
    for l in f.readlines():
        star = [int(i) for i in l.split(',')]
        if star:
            s = Star(id, star[0],star[1],star[2],star[3])
            stars[id] = s
            s_constellations = []
            for c_id, c in constellations.items():
                if star_in_constellation(s,c,stars):
                    s_constellations.append(c_id)
                    constellations[c_id].append(s.id)
            if len(s_constellations) > 1:
                constellations[s_constellations[0]][:] = [s_id for c in s_constellations for s_id in constellations[c]]
                for c in s_constellations[1:]:
                    del constellations[c]
            elif len(s_constellations) == 1:
                constellations[s_constellations[0]].append(id)
            else:
                constellations[id] = [id]
            id = id + 1

print("solution 1 = " +str(len(constellations)))
