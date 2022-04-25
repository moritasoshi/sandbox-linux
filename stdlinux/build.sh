#!/bin/sh

c_files=$(ls | grep -e ".*\.c" | sed "s/\.c//")

for fn in $c_files; do
  gcc $fn.c -Wall -O2 -o $fn.o
done
