#!/bin/bash

set -e

DAY=$1

for f in $(find src/day$DAY -name "*.py")
do
    pushd $(dirname $f)
    ./$(basename $f)
    popd
done
