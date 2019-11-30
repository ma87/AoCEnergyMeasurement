#!/bin/bash

set -e


build_folder="build"
cd $build_folder

./day$1/aocd$1 < ../day$1/input.in
