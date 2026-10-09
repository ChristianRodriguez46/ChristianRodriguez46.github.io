# Guessing game and calculator

**CMPS 2010 Programming Fundamentals**, Lab 3

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps2010/lab03/](https://christianrodriguez46.github.io/Coursework/cmps2010/lab03/)

## What it does

- `lab3-1.cpp` picks a random number from -10 to 10 and gives hints (positive or negative, even or odd, near zero or not) until you guess it. `3lab-2.cpp` is the same game with a range of -20 to 20.
- `lab3-2.cpp` reads two integers and an operator (`+ - * / %`) and prints the result, rejecting anything else.

## How to run

From this folder:

```bash
g++ -o lab3-1 lab3-1.cpp
./lab3-1

g++ -o lab3-2 lab3-2.cpp
./lab3-2
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- `if`/`else` and `switch`
- Random numbers with `rand` and `srand`
- Loops

[Back to CMPS 2010](../)
