# diff and patch

**CMPS 2650 Linux Environment and Administration**, Lab 9

## What it is

Creating a patch file from two versions of a program, applying it, and rolling it back. `hello.patch` is the patch I produced.

## Files

| File | What it is |
|---|---|
| [hello.c](hello.c) | Original program |
| [hello_new.c](hello_new.c) | Edited version |
| [hello.patch](hello.patch) | Unified diff from the original to the edited version |

## Try it

From this folder:

```bash
patch -o hello_patched.c hello.c < hello.patch   # apply the patch to a copy
gcc hello_patched.c -o hello && ./hello          # Hello, Unix World!
```

Requires: bash on Linux, macOS or WSL, plus `gcc`/`g++` for the C and C++ files.

## Answers

The commands for this lab and what they do are on the answers page: [Lab 9 answers](https://christianrodriguez46.github.io/Coursework/cmps2650/#lab09)

[Back to CMPS 2650](../)
