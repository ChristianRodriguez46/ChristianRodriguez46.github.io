# Semester project

**CMPS 3600 Operating Systems**, Lab 15

## What it does

The semester project, built in phases on top of an X11 window:

- **Phase 2** (`bbphase2.c`) launches other programs from the window with `fork` and `execve`.
- **Phase 3** (`bbphase3.c`) shows live CPU usage for each core.
- **Phase 4** (`bbphase4.c`) is the traffic-intersection simulation with a separate statistics window started with `fork` and `execve` and fed through shared memory.

## How to run

From this folder:

```bash
make
./bbphase4
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Processes and threads together
- Shared memory
- X11 graphics

[Back to CMPS 3600](../)
