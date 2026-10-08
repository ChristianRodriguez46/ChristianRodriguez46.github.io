# OpenGL bouncing box

**CMPS 3350 Software Engineering**, Lab 1

## What it does

- `lab1.cpp` opens an X11 window and moves a box back and forth with OpenGL, bouncing off the window edges.
- `test.cpp` extends it so the box changes color and speed after each collision, printing the values to the terminal.
- `waitlist.cpp` is a one-line warm-up program.

## How to run

From this folder:

```bash
make
./lab1
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- OpenGL rendering loop
- X11 windows and events
- Collision detection

[Back to CMPS 3350](../)
