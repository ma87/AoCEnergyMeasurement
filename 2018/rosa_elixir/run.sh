#!/bin/bash

set -e

cd 2018

if [ "$1" -lt 10 ]; then
  DAY="0$1"
else
  DAY=$1
fi

elixir day"$DAY".exs
