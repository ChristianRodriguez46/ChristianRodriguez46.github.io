# First OpenMP programs

**CMPS 3640 Distributed and Parallel Computation**, Lab 2

## What it does

`HelloWorldOMP.cpp` prints from every thread in an OpenMP parallel region. `ArrayOpOMP.cpp` rewrites the lab 1 array operation with OpenMP and times it for a given thread count.

## How to run

From this folder:

```bash
g++ -fopenmp -o hello HelloWorldOMP.cpp
./hello

g++ -fopenmp -O2 -o arrayomp ArrayOpOMP.cpp
./arrayomp 4
```

Requires: `g++` with OpenMP (`-fopenmp`) and POSIX threads (`-pthread`), standard on Linux.

## Concepts

- OpenMP parallel regions
- Thread IDs

[Back to CMPS 3640](../)
