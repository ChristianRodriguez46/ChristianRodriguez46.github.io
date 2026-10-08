# Monster class with constructors

**CMPS 2010 Programming Fundamentals**, Lab 11

## What it does

Adds constructors to the `Monster` class: the default constructor builds a random monster from the name, type and color lists in `GLOBALS.h`, and a second constructor sets every field. `Main.cpp` allocates a dynamic array of monsters and writes a card for each into `monsters/`.

## How to run

From this folder:

```bash
g++ -o monster_cards Main.cpp Monster.cpp
./monster_cards
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Constructors
- Dynamic arrays with `new` and `delete[]`
- `toString` methods

[Back to CMPS 2010](../)
