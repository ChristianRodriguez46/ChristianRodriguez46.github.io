# Threads, fork and exec

**CMPS 3600 Operating Systems**, Lab 8

## What it does

`bblab8.c` starts five threads that compete for a shared resource guarded by a semaphore. After they finish, it runs a cleanup program with `execve`, either directly (`0`) or from a forked child (`1`). `xlab8.c` is an earlier version.

## How to run

From this folder:

```bash
make
./lab8 1
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- `execve`
- Thread synchronization
- Cleaning up IPC resources

[Back to CMPS 3600](../)
