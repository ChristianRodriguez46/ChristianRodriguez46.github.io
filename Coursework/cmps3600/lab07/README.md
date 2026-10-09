# Dining philosophers

**CMPS 3600 Operating Systems**, Lab 7

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3600/lab07/](https://christianrodriguez46.github.io/Coursework/cmps3600/lab07/)

## What it does

`bblab7.c` runs five philosopher threads that share forks, using a mutex and semaphores so they can eat without deadlock, and prints who is eating at each step. `dotprod.c`, `mutex_test.c` and `volatile.c` are the week's examples.

## How to run

From this folder:

```bash
make
./bblab7
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Deadlock avoidance
- Mutexes
- Semaphores

[Back to CMPS 3600](../)
