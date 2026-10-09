# Guessing games against a black box

**CMPS 3120 Algorithm Analysis**, Lab 2

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3120/lab02/](https://christianrodriguez46.github.io/Coursework/cmps3120/lab02/)

## What it does

Finds a hidden number between 1 and 100 million four ways: linear search, random guessing, a search using about 2 lg N guesses, and one using about lg N guesses, where the black box only says whether each guess is closer than the last. Each game is timed so the strategies can be compared.

## How to run

From this folder:

```bash
gcc -o lab2 lab2.c blackbox1.o   # blackbox1.o is from the course server
./lab2
```

Requires: A C compiler such as `gcc`. The assignment needs Python 3 with NumPy, SciPy and Matplotlib.

## Note

Links against an instructor-provided object file that is not included here, so this lab only builds on the course server. `output.txt` shows a complete run.

## Concepts

- Linear vs. binary search
- Measuring running time

[Back to CMPS 3120](../)
