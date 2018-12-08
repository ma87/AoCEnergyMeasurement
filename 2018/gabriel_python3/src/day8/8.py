#!/usr/bin/env python3

filename = 'input'

class Node(object):
    def __init__(self, num_children, num_metadata):
        self.num_children = num_children
        self.num_metadata = num_metadata
        self.children = list()
        self.metadata = list()

    def add_children(self, child):
        self.children.append(child)

    def add_metadata(self, value):
        self.metadata.append(value)

    def metadata_sum(self):
        return sum(self.metadata)


def parse_license(root, it):
    global chksum
    num_children = int(next(it))
    num_metadata = int(next(it))
    node = Node(num_children, num_metadata)
    root.add_children(node)
    for i in range(num_children):
        parse_license(node, it)
    for i in range(num_metadata):
        metadata = int(next(it))
        root.add_metadata(metadata)
        chksum += metadata
        

chksum = 0
root = Node(1, 0)
with open(filename) as f:
    for line in f:
        it = iter(line.split(' '))
        parse_license(root, it)

print(chksum)
