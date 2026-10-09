# Word filtering challenge

**CMPS 3350 Software Engineering**, Lab 10

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3350/lab10/](https://christianrodriguez46.github.io/Coursework/cmps3350/lab10/)

## What it does

`laba3.cpp` reads a word list and prints the words that contain exactly one non-vowel letter, with a total. `Sample.cpp` is the starter code for reading words from a file.

## How to run

From this folder:

```bash
make
./laba3
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Note

Both programs read the instructor's dictionary file at a path on the course server. To run them elsewhere, change `fname` near the top of the file to any word list.

## Concepts

- File input
- C-string processing

[Back to CMPS 3350](../)
