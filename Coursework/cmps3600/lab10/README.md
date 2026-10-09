# Dot product with threads and pipes

**CMPS 3600 Operating Systems**, Lab 10

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3600/lab10/](https://christianrodriguez46.github.io/Coursework/cmps3600/lab10/)

## What it does

`bblab10.c` computes a dot product with eight threads. Each thread writes its partial sum into a pipe, and a forked child process reads the pipe and adds the parts. The other files explore page faults, cache behavior and resource limits.

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
