#!/bin/bash

set -e

build_folder="build"

if [ ! -d "$build_folder" ]; then
  mkdir $build_folder
  cd $build_folder
  cmake ..
  cd ..
fi

cd $build_folder

make aocd$1

