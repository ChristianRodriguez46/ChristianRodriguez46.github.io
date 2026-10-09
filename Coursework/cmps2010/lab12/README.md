# Shapes with inheritance

**CMPS 2010 Programming Fundamentals**, Lab 12

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps2010/lab12/](https://christianrodriguez46.github.io/Coursework/cmps2010/lab12/)

## What it does

`Shapes.h` defines an abstract `Shape` class and `Rectangle`, `Square`, `Triangle` and `Circle` subclasses that compute area and perimeter. `Main.cpp` builds one of each, prints them, and compares two rectangles with an overloaded `==`.

## How to run

From this folder:

```bash
g++ -o shapes Main.cpp Shapes.cpp
./shapes
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Inheritance
- Pure virtual functions
- Operator overloading

[Back to CMPS 2010](../)
