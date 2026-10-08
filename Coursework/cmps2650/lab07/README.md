# Bash scripting, part 1

**CMPS 2650 Linux Environment and Administration**, Lab 7

## What it is

How a script's interpreter is chosen, exit codes, and a script that reports whether a C++ file compiles.

## Files

| File | What it is |
|---|---|
| [lab7-01.sh](lab7-01.sh) | Joins two strings with +=; works in bash, fails in sh |
| [lab7-02.sh](lab7-02.sh) | Reports whether a C++ file compiles |
| [argcount.cpp](argcount.cpp) | Returns the number of arguments as its exit status |
| [hello.cpp](hello.cpp) | Broken on purpose, to test the "Compile failed" message |
| [test.sh](test.sh) | First script: prints a greeting and its own name (`$0`) |

## Try it

From this folder:

```bash
bash lab7-01.sh                  # Hello, Scripts
bash lab7-02.sh hello.cpp        # Compile failed
g++ -o argcount argcount.cpp && ./argcount a b c; echo $?   # 3
```

Requires: bash on Linux, macOS or WSL, plus `gcc`/`g++` for the C and C++ files.

## Answers

The commands for this lab and what they do are on the answers page: [Lab 7 answers](https://christianrodriguez46.github.io/Coursework/cmps2650/#lab07)

[Back to CMPS 2650](../)
