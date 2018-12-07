#!/usr/bin/env python3

filename = 'input'

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

try:
    while construct.nodes:
        candidates = ""
        for node in construct.nodes.values():
            if not node.parents and node.key not in construct.steps:
                candidates += node.key
    
        step = sorted(candidates)[0]
        construct.steps += step
    
        for node in construct.nodes.values():
            if step in node.parents:
                node.parents.remove(step)
except IndexError:    
    print(construct.steps)
