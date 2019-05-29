#!/bin/bash

set -ex

DAY=$1

rustc src/day$DAY/$DAY.rs -o src/day$DAY/$DAY
if [ -r src/day$DAY/$DAY-2.rs ] ; then
	rustc -C opt-level=3 -C target-cpu=core2 -C lto src/day$DAY/$DAY-2.rs -o src/day$DAY/$DAY-2
fi
