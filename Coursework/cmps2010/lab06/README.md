# Arrays from files and random names

**CMPS 2010 Programming Fundamentals**, Lab 6

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps2010/lab06/](https://christianrodriguez46.github.io/Coursework/cmps2010/lab06/)

## What it does

- `lab6-1.cpp` reads the numbers in `numbers.txt` into an array and prints them in reverse order. `extralab6.cpp` also prints their sum and average.
- `lab6-2.cpp` prints randomly generated first and last names: 10 by default, or as many as you pass on the command line.
- `Fall25/` holds rewritten versions of both programs from fall 2025, with a `Makefile`.

## How to run

From this folder:

```bash
g++ -o lab6-1 lab6-1.cpp
./lab6-1 numbers.txt

g++ -o lab6-2 lab6-2.cpp
./lab6-2 5

# or, for the fall 2025 versions
cd Fall25 && make
./p1 numbers.txt
./p2 5
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Arrays
- Reading numbers from a file
- `argc`/`argv`

[Back to CMPS 2010](../)
