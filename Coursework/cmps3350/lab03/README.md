# HTTPS requests in C++

**CMPS 3350 Software Engineering**, Lab 3

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3350/lab03/](https://christianrodriguez46.github.io/Coursework/cmps3350/lab03/)

## What it does

- `lab3-ssl.cpp` opens a TCP socket, negotiates TLS with OpenSSL, sends an HTTP `GET`, and prints the page it receives. `lab3-ssl.c` is the instructor's original C version.
- `lab3.php` is a small PHP page that reads a `param` from the URL and either greets you or does arithmetic with it.

## How to run

From this folder:

```bash
sudo apt install libssl-dev   # once
make
./lab3 www.example.com index.html
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Sockets
- TLS with OpenSSL
- HTTP requests

[Back to CMPS 3350](../)
