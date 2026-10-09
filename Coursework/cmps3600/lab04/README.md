# Shared memory and message queues

**CMPS 3600 Operating Systems**, Lab 4

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3600/lab04/](https://christianrodriguez46.github.io/Coursework/cmps3600/lab04/)

## What it does

`bblab4.c` has a parent and child talk through two System V IPC channels: the parent writes a number you enter into shared memory, which the child watches for, then sends a word you enter through a message queue. The child logs both.

## How to run

From this folder:

```bash
make
./lab4
cat log
./cleanipc.sh $USER   # if a run is interrupted
```

Requires: Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Concepts

- Shared memory (`shmget`)
- Message queues (`msgget`)
- IPC keys with `ftok`

[Back to CMPS 3600](../)
