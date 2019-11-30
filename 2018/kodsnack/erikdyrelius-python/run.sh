#!/bin/bash

set -e

if [ "$1" -lt 10 ]; then
  DAY="0$1"
else
  DAY=$1
fi

python3 "day$DAY.py" "day$DAY".txt
