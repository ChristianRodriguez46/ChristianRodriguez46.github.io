# Telnet-style shell service

**CMPS 3620 Computer Networks**, Lab 6

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3620/lab06/](https://christianrodriguez46.github.io/Coursework/cmps3620/lab06/)

## What it does

Studies a larger networking package: a shell (`s_sh.c`) served over the network and a matching client (`s_tlnt.c`), plus datagram, session and diagnostic utilities. `Lab Writeup.md` explains how the shell tracks child processes with `SIGCLD`, implements internal commands, and manages terminals.

## How to run

From this folder:

```bash
make
./s_sh
```

Requires: Linux with `gcc`. Write-ups in `.tex`/`.ltx` build with any LaTeX distribution (`pdflatex`).

## Concepts

- Network services
- Process management
- Reading a large C codebase

[Back to CMPS 3620](../)
