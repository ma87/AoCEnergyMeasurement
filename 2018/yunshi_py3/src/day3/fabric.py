#!/usr/bin/env python3

from collections import Counter
import re
compiled_pattern = re.compile(r'^#(\d+) @ (\d+),(\d+): (\d+)x(\d+)\n$')


def find_overlap(claims, fabric_counter):

    for _id, x, y, width, height in claims:
        for i in range(x, x+width):
            for j in range(y, y+height):
                fabric_counter[(i, j)] += 1

    result_1 = len([p for p, count in fabric_counter.items() if count >= 2])
    return result_1


def find_only_claim(claims, fabric_counter):

    for claim_id, x, y, width, height in claims:
        maybe_only_claim = True

        for i in range(x, x + width):
            for j in range(y, y + height):
                if not fabric_counter[(i, j)] == 1:
                    maybe_only_claim = False
                    break
            if not maybe_only_claim:
                break

            if i == x+width-1 and j == y+height-1:
                return claim_id

    return None


if __name__ == "__main__":
    with open('data', 'r') as infile:
        fabrics = [line for line in infile]
        elements = [compiled_pattern.match(line).groups() for line in fabrics]
        claims = [
            (int(id), int(x), int(y), int(width), int(height))
            for id, x, y, width, height in elements
        ]
        fabric_counter = Counter()
        print(find_overlap(claims, fabric_counter))
        print(find_only_claim(claims, fabric_counter))

