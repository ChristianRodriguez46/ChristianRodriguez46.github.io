# Multi-client server

**CMPS 3620 Computer Networks**, Lab 5

## What it does

`simple_daemon.c` accepts connections in a loop and forks a child for each client, which runs `simple_shell.c` connected through pipes. Several telnet sessions can use it at once. `Lab write up.md` answers how it handles multiple clients, signals and clean shutdown.

## How to run

From this folder:

```bash
make
./s_daemon                # prints a port number
telnet localhost <port>    # in other terminals
```

Requires: Linux with `gcc`. Write-ups in `.tex`/`.ltx` build with any LaTeX distribution (`pdflatex`).

## Concepts

- Concurrent servers with `fork`
- Pipes
- Daemon signal handling

[Back to CMPS 3620](../)
