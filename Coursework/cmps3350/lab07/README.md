# Days between dates

**CMPS 3350 Software Engineering**, Lab 7

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3350/lab07/](https://christianrodriguez46.github.io/Coursework/cmps3350/lab07/)

## What it does

A `Date` class that counts the days between two dates by stepping through the calendar, handling month lengths and leap years. With two dates on the command line it prints the difference; with none it runs a set of test dates and reports any errors.

## How to run

From this folder:

```bash
make
./lab7 01/15/2024 03/01/2025
./lab7                 # run the built-in tests
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Classes and operator overloading
- Date arithmetic
- Testing edge cases

[Back to CMPS 3350](../)
