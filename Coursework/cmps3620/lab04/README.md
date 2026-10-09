# Full-duplex chat with select()

**CMPS 3620 Computer Networks**, Lab 4

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3620/lab04/](https://christianrodriguez46.github.io/Coursework/cmps3620/lab04/)

## What it does

Updates the lab 2 client and server to use `select()` so each side watches both the keyboard and the socket, letting both people type at the same time.

## How to run

From this folder:

```bash
make
./vcrec
./vcsend localhost <port>    # in a second terminal
```

Requires: Linux with `gcc`. Write-ups in `.tex`/`.ltx` build with any LaTeX distribution (`pdflatex`).

## Concepts

- Full-duplex sockets
- `select()`

[Back to CMPS 3620](../)
