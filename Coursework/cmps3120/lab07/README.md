# Subset sum: exhaustive search vs. hashing

**CMPS 3120 Algorithm Analysis**, Lab 7

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3120/lab07/](https://christianrodriguez46.github.io/Coursework/cmps3120/lab07/)

## What it does

Finds the largest subset sum that does not exceed half of the total, first with exhaustive search and then with a hash table that remembers sums already explored, and prints the subset.

## How to run

From this folder:

```bash
gcc -o lab7 Lab7.c
./lab7
```

Requires: A C compiler such as `gcc`. The assignment needs Python 3 with NumPy, SciPy and Matplotlib.

## Concepts

- Exhaustive search
- Hash tables
- Memoization

[Back to CMPS 3120](../)
