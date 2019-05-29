#!/bin/bash

set -e

if [ "$1" -lt 10 ]; then
  DAY="0$1"
else
  DAY=$1
fi

cd "day$DAY"

python3 "day$1.py" input.txt
