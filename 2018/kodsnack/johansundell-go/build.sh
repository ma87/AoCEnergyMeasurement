#!/bin/bash

set -e

cd day$1

go build -o day$1.go_run
