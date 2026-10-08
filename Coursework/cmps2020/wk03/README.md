# Board game with structs; inheritance

**CMPS 2020 Programming II: Data Structures**, Week 3

## What it does

- `lab02_2020Th_ChrRod.cpp` (lab 2) is a one-line board game. Each step is a struct marked as a plain tile, coins, oil, glue or a bandit; you choose to step or hop and the program reacts to whatever you land on.
- `lab03_2020TH_ChrRod.cpp` (lab 3) models user-interface controls: `Checkbox` and `Textbox` inherit from a `Control` base class and each draws itself with `display()`.

## How to run

From this folder:

```bash
g++ -o lab02 lab02_2020Th_ChrRod.cpp
./lab02

g++ -o lab03 lab03_2020TH_ChrRod.cpp
./lab03
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Arrays of structs
- Inheritance
- Overriding methods

[Back to CMPS 2020](../)
