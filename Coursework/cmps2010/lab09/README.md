# Monster cards with structs

**CMPS 2010 Programming Fundamentals**, Lab 9

## What it does

`monster.cpp` defines a `Monster` struct (name, type, color, eyes, arms, legs), generates as many random monsters as you ask for, prints them, and saves each one as a card in `monsters/Monsters_<name>.txt`. The `monsters/` folder holds cards from a sample run.

## How to run

From this folder:

```bash
g++ -o monster monster.cpp
./monster
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Structs
- Arrays of structs
- Writing files

[Back to CMPS 2010](../)
