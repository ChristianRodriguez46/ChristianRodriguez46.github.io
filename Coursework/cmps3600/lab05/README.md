# Ordering processes with semaphores

**CMPS 3600 Operating Systems**, Lab 5

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3600/lab05/](https://christianrodriguez46.github.io/Coursework/cmps3600/lab05/)

## What it does

`bblab5.c` has the parent compute a Fibonacci number and write it to shared memory for the child to read. A System V semaphore makes the child wait until the value is ready, fixing the race in the starter code.

## How to run

From this folder:

```bash
make
./bblab5
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Semaphores (`semget`, `semop`)
- Race conditions

[Back to CMPS 3600](../)
