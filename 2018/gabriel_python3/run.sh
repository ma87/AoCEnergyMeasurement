#!/bin/bash

set -e

DAY=$1

cd src/day$DAY
./$DAY.py
./${DAY}.2.py
