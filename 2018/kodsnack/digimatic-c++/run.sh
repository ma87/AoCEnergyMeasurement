#!/bin/bash

set -e

build_folder="build"

if [ "$1" -lt 10 ]; then
  DAY="0$1"
else
  DAY=$1
fi

cd $build_folder
./Day"$DAY"/Day"$DAY"

