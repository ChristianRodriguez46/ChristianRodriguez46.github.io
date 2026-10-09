# C++ threads

**CMPS 3640 Distributed and Parallel Computation**, Lab 10

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3640/lab10/](https://christianrodriguez46.github.io/Coursework/cmps3640/lab10/)

## What it does

Three activities with `std::thread`:

- `Lab10_Activity1.cpp` runs two threads side by side.
- `Lab10_Activity2.cpp` sums an array by giving each half to its own thread.
- `Lab10_Activity3.cpp` splits the sum across four threads, each computing a local partial sum before combining them.

## How to run

From this folder:

```bash
g++ -pthread -o act1 Lab10_Activity1.cpp && ./act1
g++ -pthread -o act3 Lab10_Activity3.cpp && ./act3
```

Requires: `g++` with OpenMP (`-fopenmp`) and POSIX threads (`-pthread`), standard on Linux.

## Concepts

- `std::thread`
- Partial sums
- Joining threads

[Back to CMPS 3640](../)
