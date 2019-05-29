#!/bin/bash

set -e


if [ "$1" -lt 10 ]; then
  DAY="0$1"
else
  DAY=$1
fi

g++ -Wall -Wextra -std=gnu++17 -o p"$DAY" src/p"$DAY".cpp
