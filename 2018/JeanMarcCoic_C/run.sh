#!/bin/bash

set -e

DAY=$1

cd src/day-$DAY
./part1
./part2
