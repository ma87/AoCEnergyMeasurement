#!/bin/bash

set -e

build_folder="build"

if [ ! -d "$build_folder" ]; then
  mkdir $build_folder
  cd $build_folder
  cmake ..
  cd ..
fi

if [ "$1" -lt 10 ]; then
  DAY="0$1"
else
  DAY=$1
fi

cd $build_folder
make day"$DAY"

