#!/bin/bash

# Compile
gcc -c benchmark.c
gcc -c utils.c
gcc -c generator.c

#gcc -c 01.c
#gcc -c 02.c
#gcc -c 03.c
#gcc -c 04.c
gcc -c 05.c

# Link
#gcc 01.o benchmark.o utils.o generator.o -o 01.out -fopenmp
#gcc 02.o benchmark.o -o 02.out -fopenmp
#gcc 03.o benchmark.o generator.o utils.o -o 03.out -fopenmp
#gcc 04.o benchmark.o utils.o generator.o -o 04.out -fopenmp
gcc 05.o benchmark.o utils.o generator.o -o 05.out -fopenmp
