#!/bin/bash

set -e

DAY=$1

cd src/day-$DAY
for src in $(ls *.c); do
    ./${src%.c}
done
