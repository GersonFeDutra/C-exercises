#!/bin/bash
for f in 0*; do
    mpicc -o "$(basename $f)".out "$f"
done

if [ "$1" ]; then
    #mpirun -np $1 ./out
else
    #mpirun ./out
fi
