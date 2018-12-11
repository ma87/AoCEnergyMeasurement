#!/bin/bash

set -e

DAY=$1

./adc_$DAY.out src/adc_$DAY.txt
