#!/usr/bin/env python3

filename = 'input'
workers = [(0, '.')] * 5
cost_offset = 60

def parse_line(line):
    before = line[len('Step ')]
    after = line[len('Step X must be finished before step ')]
    return before, after

class Node(object):
    def __init__(self, key):
        self.key = key
        self.parents = set()
        self.children = set()
    def __repr__(self):
        return u'[{}], [{}]\n'.format(self.parents, self.children)

class Construct(object):
    steps = ""
    nodes = {}

    def link(self, before, after):
        if before not in self.nodes:
            self.nodes[before] = Node(before)
        self.nodes[before].children.add(after)

        if after not in self.nodes:
            self.nodes[after] = Node(after)
        self.nodes[after].parents.add(before)
    def __repr__(self):
        return u'{}\nnodes:[\n{}]'.format(self.steps, self.nodes)


construct = Construct()
with open(filename) as f:
    for line in f:
        before, after = parse_line(line)
        construct.link(before, after)

# first element's parents set should be empty
# last element's children set shoudl be empty

total_time = 0

def cost(step):
    return ord(step) - ord('A') + cost_offset + 1

def work(workers):
    global total_time
    time = max(1, min([x for x, y in workers]))
    total_time += time
    for i in range(len(workers)):
        t, x = workers[i]
        if t > 0:
            t = t - time
            workers[i] = (t, x)
            if t == 0:
                workers[i] = (0, '.')  # DELETEME
                for node in construct.nodes.values():
                    if x in node.parents:
                        node.parents.remove(x)

def get_free_worker_index(workers):
    for i in range(len(workers)):
        x, y = workers[i]
        if x == 0:
            return i

while construct.nodes:
    candidates = ""
    for node in construct.nodes.values():
        if not node.parents and node.key not in construct.steps:
            candidates += node.key

    for step in sorted(candidates):
        try:
            index = get_free_worker_index(workers)
            x, y = workers[index]
            workers[index] = (cost(step), step)
            construct.steps += step

        except:
            break
    work(workers)  # at least one worker is available

    if len(construct.steps) == len(construct.nodes):
        finish_time = max([x for x, y in workers])
        total_time += finish_time
        print(total_time)
        break
