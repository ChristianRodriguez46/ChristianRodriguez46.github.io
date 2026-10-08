# Processes with fork and wait

**CMPS 3600 Operating Systems**, Lab 2

## What it does

`bblab2.c` forks a child process that computes the nth Fibonacci number and writes it to a log, while the parent waits and reports the child's exit code. The other files are the week's examples of `fork`, `wait`, `alarm` and `perror`.

## How to run

From this folder:

```bash
make
./lab2 9
cat log
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- `fork` and `wait`
- Exit status
- Process logs

[Back to CMPS 3600](../)
