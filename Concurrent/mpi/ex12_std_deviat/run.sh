#!/bin/bash
cd ../lib/
./build.sh
cd -
mpicc -c main.c -lm
mpicc -o ../../program.out ../lib/benchmark.o ../lib/generator.o ../lib/utils.o main.o -lm
cd ../../

if [ "$1" ]; then
    mpiexec -np $1 ./program.out # Set your number of threads
else
    printf "\33[31mNumber of threads not set, using single thread\033[m\n" >&2
    mpiexec -np 1 ./program.out
fi
cd -
