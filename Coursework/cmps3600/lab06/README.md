# Producer and consumer threads

**CMPS 3600 Operating Systems**, Lab 6

## What it does

- `bblab6.c` copies a file one character at a time through a shared buffer: a producer thread fills it and a consumer thread writes it to a log, with semaphores keeping them in step so no character is lost or repeated. `poem` is the sample input.
- `bbphase2.c` is phase 2 of the semester project (see lab 15).

## How to run

From this folder:

```bash
make
./bblab6
cat log
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- POSIX threads
- Producer-consumer problem
- Semaphores

[Back to CMPS 3600](../)
