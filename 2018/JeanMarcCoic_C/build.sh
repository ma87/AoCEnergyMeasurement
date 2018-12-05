#!/bin/bash

DAY=$1

cd src/day-$DAY
for src in $(ls *.c); do
    gcc -o ${src%.c} $src
done
