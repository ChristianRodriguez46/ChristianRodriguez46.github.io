# Binary search for hidden positions

**CMPS 3120 Algorithm Analysis**, Lab 9

## What it does

Finds the positions of hidden values using a black-box query on ranges, combining binary search with parity (AND/OR) queries. The black box verifies each answer.

## How to run

From this folder:

```bash
gcc -o lab9 asgn9.c blackboxA.o   # blackboxA.o is from the course server
./lab9
```

Requires: A C compiler such as `gcc`. The assignment needs Python 3 with NumPy, SciPy and Matplotlib.

## Note

Links against an instructor-provided object file that is not included here, so this lab only builds on the course server. `output.txt` shows a complete run.

## Concepts

- Binary search
- Query-based algorithms

[Back to CMPS 3120](../)
