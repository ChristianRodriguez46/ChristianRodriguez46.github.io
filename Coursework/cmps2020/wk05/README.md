# Config file parser and templates

**CMPS 2020 Programming II: Data Structures**, Week 5

## What it does

- `lab06_2020TH_ChrRod.cpp` (lab 6) loads `config.ini`, skips comments, and stores `key=value` pairs. Bad lines raise custom exceptions (missing key, bad key, missing separator) derived from `std::exception`.
- `lab07_2020TH_ChrRod.cpp` (lab 7) uses function templates to read, print and average arrays of integers, doubles and strings.

## How to run

From this folder:

```bash
g++ -o lab06 lab06_2020TH_ChrRod.cpp
./lab06

g++ -o lab07 lab07_2020TH_ChrRod.cpp
./lab07
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Custom exceptions
- Parsing text files
- Function templates

[Back to CMPS 2020](../)
