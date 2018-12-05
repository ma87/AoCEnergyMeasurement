#!/bin/bash

set -e

DAY=$1

cd src/day$DAY
./$DAY
#./${DAY}.2
