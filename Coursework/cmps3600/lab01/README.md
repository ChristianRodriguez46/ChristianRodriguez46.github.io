# System calls instead of the C++ library

**CMPS 3600 Operating Systems**, Lab 1

## What it does

`lab1.c` rewrites a C++ program (`lab1.cpp`) in C using only low-level system calls: it reads your name and a number with `read`, computes the sum from 1 to that number, and writes the results to a file named `log` with `open` and `write`. `xwin89.c` is a starter X11 program.

## How to run

From this folder:

```bash
make
./lab1c
cat log
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- `open`, `read`, `write`
- File descriptors

[Back to CMPS 3600](../)
