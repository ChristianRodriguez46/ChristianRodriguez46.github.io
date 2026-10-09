# Traffic intersection with threads

**CMPS 3600 Operating Systems**, Lab 9

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3600/lab09/](https://christianrodriguez46.github.io/Coursework/cmps3600/lab09/)

## What it does

- `bblab9.c` animates cars crossing an intersection in an X11 window, one thread per car. A mutex lets only one car into the intersection at a time; press **C** to see the collisions it prevents.
- `procstat.c` reads CPU statistics from `/proc/stat`. `bbphase3.c` is phase 3 of the semester project.

## How to run

From this folder:

```bash
make
./bblab9
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Mutual exclusion
- Threads in a graphics loop
- `/proc` filesystem

[Back to CMPS 3600](../)
