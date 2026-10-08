# CMPS 3600: Operating Systems

Processes, threads, signals, interprocess communication, synchronization and memory in C.

Languages and tools: C, POSIX.

Each lab folder holds the instructor's example programs for that week alongside my lab program (`bblabN.c`), which starts from the instructor's template. The semester project was built in phases: `bbphase2.c`, `bbphase3.c` and `bbphase4.c`, all collected in lab 15. Labs that use System V IPC create their key from the `foo` file in the folder; `cleanipc.sh` removes any shared memory, semaphores or message queues left behind by a crashed run.

## Requirements

Linux with `gcc` and POSIX threads. The graphical labs also need the X11 development headers (`sudo apt install libx11-dev libxext-dev` on Ubuntu). Every folder has a `Makefile`.

## Labs and projects

| Folder | What it is |
|---|---|
| [Lab 1](lab01/) | System calls instead of the C++ library |
| [Lab 2](lab02/) | Processes with fork and wait |
| [Lab 3](lab03/) | Signal handlers |
| [Lab 4](lab04/) | Shared memory and message queues |
| [Lab 5](lab05/) | Ordering processes with semaphores |
| [Lab 6](lab06/) | Producer and consumer threads |
| [Lab 7](lab07/) | Dining philosophers |
| [Lab 8](lab08/) | Threads, fork and exec |
| [Lab 9](lab09/) | Traffic intersection with threads |
| [Lab 10](lab10/) | Dot product with threads and pipes |
| [Lab 11](lab11/) | Memory-mapped files |
| [Lab 13](lab13/) | Intersection, continued |
| [Lab 15](lab15/) | Semester project |
| [Templates](templates/) | Starter templates |

[All coursework](../)
