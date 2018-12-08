#!/usr/bin/env python3

filename = 'input'

class Node(object):
    def __init__(self, num_children, num_metadata):
        self.num_children = num_children
        self.num_metadata = num_metadata
        self.children = list()
        self.metadata = list()
        self.value = 0

    def add_children(self, child):
        self.children.append(child)

    def add_metadata(self, value):
        self.metadata.append(value)


def parse_license(root, it):
    num_children = int(next(it))
    num_metadata = int(next(it))
    node = Node(num_children, num_metadata)
    if root:
        root.add_children(node)

    for i in range(num_children):
        parse_license(node, it)
    for i in range(num_metadata):
        metadata = int(next(it))
        node.add_metadata(metadata)

    if not num_children:
        node.value = sum(node.metadata)
    else:
        for m in node.metadata:
            index = m - 1
            try:
                node.value += node.children[index].value
            except IndexError:
                pass

    return node

root = None
with open(filename) as f:
    for line in f:
        it = iter(line.split(' '))
        root = parse_license(root, it)

print(root.value)
