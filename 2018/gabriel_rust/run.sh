#!/bin/bash

set -e

DAY=$1

cd src/day$DAY
./$DAY
if [ -x ${DAY}-2 ] ; then
	./${DAY}-2
fi
