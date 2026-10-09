# File processing and prime numbers

**CMPS 2010 Programming Fundamentals**, Lab 5

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps2010/lab05/](https://christianrodriguez46.github.io/Coursework/cmps2010/lab05/)

## What it does

- `lab5-1.cpp` reads a text file one character at a time, converts it to uppercase, drops the vowels, replaces spaces with underscores, and writes the result to a second file. `input.txt` and `output.txt` are a sample run.
- `lab5-2.cpp` asks for a whole number, says whether it is prime, and lists its factors when it is not. `lab5-2-alt.cpp` is an earlier draft.

## How to run

From this folder:

```bash
g++ -o lab5-1 lab5-1.cpp
./lab5-1 input.txt output.txt

g++ -o lab5-2 lab5-2.cpp
./lab5-2
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- File streams (`ifstream`, `ofstream`)
- Command-line arguments
- Functions and reference parameters

[Back to CMPS 2010](../)
