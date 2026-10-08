# Parallel histogram with locks

**CMPS 3640 Distributed and Parallel Computation**, Lab 7

## What it does

`seq_histogram.cpp` counts values into 10 bins sequentially; `par_histogram.cpp` does the same with an OpenMP parallel loop and one lock per bin. `lab7.md` reports the timings: the parallel version ran about 39 times slower, and the write-up explains why (tiny work per iteration, high lock contention and synchronization overhead).

## How to run

From this folder:

```bash
g++ -fopenmp -o seq_hist seq_histogram.cpp && ./seq_hist
g++ -fopenmp -o par_hist par_histogram.cpp && ./par_hist
```

Requires: `g++` with OpenMP (`-fopenmp`) and POSIX threads (`-pthread`), standard on Linux.

## Concepts

- OpenMP locks
- Contention
- When parallelism does not pay off

[Back to CMPS 3640](../)
