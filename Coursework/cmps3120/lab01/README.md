# Stack-sortable strings and permutations

**CMPS 3120 Algorithm Analysis**, Lab 1

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3120/lab01/](https://christianrodriguez46.github.io/Coursework/cmps3120/lab01/)

## What it does

Generates every valid push/pop sequence (*stacky string*) of length 2n, checks the count against the Catalan-number formula, then generates the permutations a stack can produce and tests random permutations to see whether they are stack-sortable.

## How to run

From this folder:

```bash
gcc -o lab1 lab1.c
./lab1 4
```

Requires: A C compiler such as `gcc`. The assignment needs Python 3 with NumPy, SciPy and Matplotlib.

## Concepts

- Recursion and backtracking
- Catalan numbers
- Stacks

[Back to CMPS 3120](../)
