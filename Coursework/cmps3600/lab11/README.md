# Memory-mapped files

**CMPS 3600 Operating Systems**, Lab 11

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3600/lab11/](https://christianrodriguez46.github.io/Coursework/cmps3600/lab11/)

## What it does

`bblab11.c` maps a file into memory with `mmap` and copies a chosen number of bytes, starting at a given offset, into an output file, handling page alignment. `article` is a sample file.

## How to run

From this folder:

```bash
make
./lab11 article out.txt 5 25
cat out.txt
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- `mmap`
- Virtual memory
- Page alignment

[Back to CMPS 3600](../)
