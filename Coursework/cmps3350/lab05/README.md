# Unit testing with build flags

**CMPS 3350 Software Engineering**, Lab 5

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3350/lab05/](https://christianrodriguez46.github.io/Coursework/cmps3350/lab05/)

## What it does

- `testing.cpp` shows how one source file can build as a normal program or as a unit test by compiling with `-D UNIT_TEST`.
- `dslab5.cpp` reads the list of logged-in users (output of the Linux `w` or `who` command), sorts the user names with bubble sort, counts each user's logins, and reports who has the most. The same file builds three ways: production runs `w`, `-D WHO_TEST` runs `who`, and `-D UNIT_TEST` reads a saved file instead.
- `file.txt` and `ggfile6.txt` are saved test data. User names and IP addresses in `file.txt` were replaced with placeholders.

## How to run

From this folder:

```bash
make
./ulab5 file.txt   # unit-test build reads saved data
./dslab5           # production build runs w on this machine
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Conditional compilation
- Unit tests
- Parsing command output

[Back to CMPS 3350](../)
