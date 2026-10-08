# Signal handlers

**CMPS 3600 Operating Systems**, Lab 3

## What it does

`bblab3.c` installs handlers for `SIGTERM` and `SIGUSR1` with `sigaction`. The parent forks a child, which writes the first half of a message to a log, suspends until `SIGUSR1` arrives, then finishes the message. The other files are examples of signal masks, handlers and `read`/`write`.

## How to run

From this folder:

```bash
make
./lab3
cat log
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- `sigaction`
- Sending signals with `kill`
- Signal masks

[Back to CMPS 3600](../)
