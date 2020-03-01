#!/bin/bash

set -e
read dim
gcc Main.c Heap.c -o output
./randmst 0 262144 10 $dim
./randmst 0 131072 20 $dim
./randmst 0 65536 100 $dim
./randmst 0 1024 5000 $dim
./randmst 0 128 10000 $dim
./randmst 0 32 10000 $dim
./randmst 0 8 100000 $dim
