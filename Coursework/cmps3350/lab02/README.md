# Keyboard-controlled animation

**CMPS 3350 Software Engineering**, Lab 2

## What it does

`lab2.cpp` moves the box in two dimensions. **W** speeds it up and **S** slows it down without letting it reverse; **Esc** quits. Text is drawn with the course font library.

## How to run

From this folder:

```bash
make
./lab2
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Keyboard input
- Velocity and physics updates

[Back to CMPS 3350](../)
