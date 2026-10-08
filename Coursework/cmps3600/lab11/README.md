# Memory-mapped files

**CMPS 3600 Operating Systems**, Lab 11

## What it does

`bblab11.c` maps a file into memory with `mmap` and prints a chosen number of characters starting at a given offset, handling page alignment. `article` is a sample file.

## How to run

From this folder:

```bash
make
./lab11 article 5 25
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- `mmap`
- Virtual memory
- Page alignment

[Back to CMPS 3600](../)
