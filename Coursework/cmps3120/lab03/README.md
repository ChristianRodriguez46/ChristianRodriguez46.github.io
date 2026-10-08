# Sorting and matching with a comparison oracle

**CMPS 3120 Algorithm Analysis**, Lab 3

## What it does

Sorts a set of balls with merge sort using only a black-box comparison, then finds matching boxes two ways with quicksort-style partitioning, counting how many black-box queries each method needs.

## How to run

From this folder:

```bash
gcc -o lab3 lab3.c blackbox2.o   # blackbox2.o is from the course server
./lab3
```

Requires: A C compiler such as `gcc`. The assignment needs Python 3 with NumPy, SciPy and Matplotlib.

## Note

Links against an instructor-provided object file that is not included here, so this lab only builds on the course server. `output.txt` shows a complete run.

## Concepts

- Merge sort
- Quicksort partitioning
- Counting comparisons

[Back to CMPS 3120](../)
