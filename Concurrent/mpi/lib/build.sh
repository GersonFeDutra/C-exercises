#!/bin/bash

mpicc -c benchmark.c
mpicc -c generator.c

for c in *.c; do
    if [ "$c" == "benchmark.c" ] || [ "$c" == "generator.c" ]; then
        continue
    fi
    gcc -c "$c"
done
