#!/usr/bin/env bash
echo "Running..."
[[ -z "$1" ]] && { echo "Parameter 1 (YEAR) is empty" ; exit 1; }
[[ -z "$2" ]] && { echo "Parameter 1 (DAY) is empty" ; exit 1; }

YEAR="${1}"
DAY="${2}"
INPUT="december${DAY}.py"

clear;
tput reset;
python "${INPUT}"
