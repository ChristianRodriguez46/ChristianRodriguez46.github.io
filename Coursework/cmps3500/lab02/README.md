# C++ templates and exceptions

**CMPS 3500 Programming Languages**, Lab 2

## What it does

`list.h` is a template `List` class with a fixed capacity of 10 that throws a custom `range_error` (`range_error.h`) on bad indexes. `lab02.cpp` fills a list of the size you pass and tests every method; sizes above 10 trigger the exception handling, and errors are written to a file named `log`.

## How to run

From this folder:

```bash
make
./lab02 8
./lab02 12    # forces range errors; see the log file
```

Requires: Linux. Each lab uses a different language toolchain, listed in its README; every folder has a `Makefile`.

## Concepts

- Class templates
- Exception handling
- Redirecting `stderr`

[Back to CMPS 3500](../)
