# Intersection, continued

**CMPS 3600 Operating Systems**, Lab 13

## What it does

`bbcars.c` continues the lab 9 traffic simulation: press **A** to add a car and **D** to remove one while it runs (up to eight), and **C** to show collisions. `donut.c` is a spinning ASCII-art donut.

## How to run

From this folder:

```bash
make
./bbcars
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Concurrency in simulations

[Back to CMPS 3600](../)
