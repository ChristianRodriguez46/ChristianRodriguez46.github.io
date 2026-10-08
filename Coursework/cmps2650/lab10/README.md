# sed, awk, nano and emacs

**CMPS 2650 Linux Environment and Administration**, Lab 10

## What it is

The same text edits done with `sed` and `awk` on `students.txt`, then configuring nano and emacs. `emacs-f5-compile-run.el` is my emacs setting that saves, compiles and runs the current file with F5.

## Files

| File | What it is |
|---|---|
| [students.txt](students.txt) | Sample names and scores |
| [emacs-f5-compile-run.el](emacs-f5-compile-run.el) | emacs setting: F5 saves, compiles and runs the current file |

## Try it

From this folder:

```bash
awk '{total += $2; count++} END {print total/count}' students.txt   # 86
cat emacs-f5-compile-run.el >> ~/.emacs                             # then F5 in emacs
```

Requires: bash on Linux, macOS or WSL, plus `gcc`/`g++` for the C and C++ files.

## Answers

The commands for this lab and what they do are on the answers page: [Lab 10 answers](https://christianrodriguez46.github.io/Coursework/cmps2650/#lab10)

[Back to CMPS 2650](../)
