# Computing pi in parallel

**CMPS 3640 Distributed and Parallel Computation**, Lab 3

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3640/lab03/](https://christianrodriguez46.github.io/Coursework/cmps3640/lab03/)

## What it does

- Approximates pi by integrating 4/(1+x²) from 0 to 1 and reports the error and time.
- `pi.cpp` is the sequential version.
- `pi_4A.cpp` splits the steps round-robin: thread *i* takes steps *i*, *i*+N, *i*+2N and so on.
- `pi_4B.cpp` gives each thread one contiguous block of steps.
- Both parallel versions keep a partial sum per thread and add them at the end.

## How to run

From this folder:

```bash
g++ -fopenmp -O2 -o pi pi.cpp && ./pi
g++ -fopenmp -O2 -o 4a pi_4A.cpp && ./4a
g++ -fopenmp -O2 -o 4b pi_4B.cpp && ./4b
```

Requires: `g++` with OpenMP (`-fopenmp`) and POSIX threads (`-pthread`), standard on Linux.

## Concepts

- Work decomposition
- Partial sums
- Numerical integration

[Back to CMPS 3640](../)
