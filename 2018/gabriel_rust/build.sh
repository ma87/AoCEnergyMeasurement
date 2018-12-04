#!/bin/bash

set -ex

DAY=$1

rustc src/day$DAY/1.rs -o src/day$DAY/1
