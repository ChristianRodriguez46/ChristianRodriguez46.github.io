# Exporting data; credit card validation

**CMPS 2020 Programming II: Data Structures**, Week 4

## What it does

- `hw01_2020TH_ChrRod.cpp` (homework 1) stores county infection counts in a `CoronaData` class and saves them through two subclasses, one writing `corona.json` and one writing `corona.csv`. The two files here are its output.
- `lab05_2020TH_ChrRod.cpp` (lab 5) reads a card number, expiration date and security code, checks the number with the Luhn algorithm, and uses a factory function to create a `Visa`, `Amex` or `Mastercard` object with its own validation rules.
- `lab04_2020TH_ChrRod.txt` holds written answers for lab 4.

## How to run

From this folder:

```bash
g++ -o hw01 hw01_2020TH_ChrRod.cpp
./hw01

g++ -o lab05 lab05_2020TH_ChrRod.cpp
./lab05
```

Requires: A C++ compiler such as `g++` (Linux, macOS, or WSL on Windows).

## Concepts

- Polymorphism
- Factory functions
- Writing JSON and CSV
- Luhn checksum

[Back to CMPS 2020](../)
