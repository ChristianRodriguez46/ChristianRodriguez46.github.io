# Random numbers and Monte Carlo

**CMPS 3350 Software Engineering**, Lab 9

## What it does

- `rand.cpp` estimates a probability over 10 million random draws.
- `montecarlo.cpp` estimates how often three random numbers from 1 to 39 are consecutive and fall in the same third of the range.
- `vrlab9.cpp` prints a grid of random digits and adds the columns with carries, like long addition. Rows and columns come from the command line.

## How to run

From this folder:

```bash
make
./montecarlo
./lab9 4 6
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Random number generation
- Monte Carlo estimation

[Back to CMPS 3350](../)
