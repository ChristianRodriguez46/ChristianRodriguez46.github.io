# Ada: strong typing and concurrent tasks

**CMPS 3500 Programming Languages**, Lab 3

## What it does

- `testada.adb` demonstrates Ada's strong typing, scoping rules and arrays, reading numbers from `infile.txt` and writing `outfile.txt`.
- `dogspa.adb` simulates a dog spa, reading dog names from `names.txt`, with concurrent tasks that use selective waits with guards.

## How to run

From this folder:

```bash
sudo apt install gnat   # once
make
./testada
./dogspa
```

Requires: GNAT, the GCC Ada compiler.

## Concepts

- Ada
- Strong typing
- Concurrency with tasks

[Back to CMPS 3500](../)
