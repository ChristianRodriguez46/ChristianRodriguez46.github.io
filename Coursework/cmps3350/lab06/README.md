# Waterfall particle simulation

**CMPS 3350 Software Engineering**, Lab 6

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3350/lab06/](https://christianrodriguez46.github.io/Coursework/cmps3350/lab06/)

## What it does

`waterlab6.cpp` spawns water particles that fall with gravity and bounce off five boxes placed down the screen, rendered with OpenGL. `test.cpp` is a working copy.

## How to run

From this folder:

```bash
make
./waterlab6
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Particle systems
- Collision with rectangles
- Gravity

[Back to CMPS 3350](../)
