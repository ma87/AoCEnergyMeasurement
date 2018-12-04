#!/bin/bash

DAY=$1

# Nothing to do for python
gcc -o src/day-$DAY/part1 src/day-$DAY/part1.c
gcc -o src/day-$DAY/part2 src/day-$DAY/part2.c
