#!/usr/bin/env python3
if __name__ == "__main__":
    with open('data', 'r') as infile:
        print(sum([int(line) for line in infile]))
