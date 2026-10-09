# Signals and select()

**CMPS 3620 Computer Networks**, Lab 3

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3620/lab03/](https://christianrodriguez46.github.io/Coursework/cmps3620/lab03/)

## What it does

`select.c` blocks signals with a signal mask and uses `select()` to wait on the keyboard with a timeout. The write-up (`Write-up.ltx`, questions in `Write-Up-Questions.md`) explains signal handling and how `select()` could make the lab 2 chat full-duplex.

## How to run

From this folder:

```bash
gcc -o select select.c
./select
```

Requires: Linux with `gcc`. Write-ups in `.tex`/`.ltx` build with any LaTeX distribution (`pdflatex`).

## Concepts

- Signal masks
- I/O multiplexing with `select()`

[Back to CMPS 3620](../)
