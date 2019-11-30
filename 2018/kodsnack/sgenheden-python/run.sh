#!/bin/bash

set -e
echo "$1"
cd "day$1"
python3 part2.py < input.txt
