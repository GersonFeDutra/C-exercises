#!/bin/bash

# Compile
gcc -c benchmark.c
gcc -c utils.c
gcc -c generator.c

gcc -c main.c -fopenmp -lm

# Link
gcc main.o benchmark.o utils.o generator.o -o main.out -fopenmp -lm

./main.out
