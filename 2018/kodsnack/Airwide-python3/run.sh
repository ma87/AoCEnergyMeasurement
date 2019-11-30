#!/bin/bash

set -e

cd "day$1"

if [ -f "day$1part2.py" ] ; then
  python3 "day$1part2.py" input.txt
else
  python3 "day$1.py" input.txt
fi
