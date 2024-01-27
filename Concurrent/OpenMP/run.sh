#!/bin/bash
gcc -c 00_basic_thread.c -fopenmp
gcc -c 01_thread_for.c -fopenmp
gcc -c 02_multiple_tasks_threads.c -fopenmp
gcc -c 03_thread_timing.c -fopenmp
gcc -c 04_parallel_search.c -fopenmp
gcc -c 05_pi.c -fopenmp
gcc -c 06_arithmetic_medium.c -fopenmp

gcc 00_basic_thread.o -o 00_basic_thread.out -fopenmp
gcc 01_thread_for.o -o 01_thread_for.out -fopenmp
gcc 02_multiple_tasks_threads.o -o 02_multiple_tasks_threads.out -fopenmp
gcc 03_thread_timing.o -o 03_thread_timing.out -fopenmp
gcc 04_parallel_search.o -o 04_parallel_search.out -fopenmp
gcc 05_pi.o -o 05_pi.out -fopenmp
gcc 06_arithmetic_medium.o -o 06_arithmetic_medium.out -fopenmp
