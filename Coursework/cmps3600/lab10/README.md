# Dot product with threads and pipes

**CMPS 3600 Operating Systems**, Lab 10

## What it does

`bblab10.c` computes a dot product with several threads, using a mutex to protect the running total, and has a child process send a partial sum back to the parent through a pipe. The other files explore page faults, cache behavior and resource limits.

## How to run

From this folder:

```bash
make
./bblab10
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Pipes
- Mutexes
- Memory behavior

[Back to CMPS 3600](../)
