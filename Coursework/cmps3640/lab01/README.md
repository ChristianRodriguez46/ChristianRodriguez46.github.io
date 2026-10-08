# Timing a multithreaded array operation

**CMPS 3640 Distributed and Parallel Computation**, Lab 1

## What it does

`ArrayOp.cpp` adds large arrays with a chosen number of threads and reports the elapsed time over ten runs and their average. `runlab` runs it with 0, 1, 2 and more threads in a row so the speedup can be compared; `output.txt` is a sample run.

## How to run

From this folder:

```bash
g++ -O2 -pthread -o ArrayOp ArrayOp.cpp
./ArrayOp 2
bash runlab 5   # threads 0 to 4
```

Requires: `g++` with OpenMP (`-fopenmp`) and POSIX threads (`-pthread`), standard on Linux.

## Concepts

- Threads
- Measuring speedup

[Back to CMPS 3640](../)
