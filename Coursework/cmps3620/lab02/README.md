# TCP client and server

**CMPS 3620 Computer Networks**, Lab 2

## What it does

`vcrec.c` opens a TCP socket, prints the port it was given, and waits for a connection; `vcsend.c` connects to it and sends whatever you type. Communication is half-duplex: one side talks at a time.

## How to run

From this folder:

```bash
make
./vcrec                      # prints a port number
./vcsend localhost <port>    # in a second terminal
```

Requires: Linux with `gcc`. Write-ups in `.tex`/`.ltx` build with any LaTeX distribution (`pdflatex`).

## Concepts

- `socket`, `bind`, `listen`, `accept`, `connect`
- Half-duplex communication

[Back to CMPS 3620](../)
