# Basic regular expressions with grep

**CMPS 2650 Linux Environment and Administration**, Lab 4

## What it is

Matching text with basic regular expressions (BREs) in `grep`. `text.txt` is the sample file the commands run against.

## Files

| File | What it is |
|---|---|
| [text.txt](text.txt) | Sample text the grep commands run against |

## Try it

From this folder:

```bash
grep -i "apple" text.txt
grep -E '[A-Z]{2,}' text.txt
```

Requires: bash on Linux, macOS or WSL, plus `gcc`/`g++` for the C and C++ files.

## Answers

The commands for this lab and what they do are on the answers page: [Lab 4 answers](https://christianrodriguez46.github.io/Coursework/cmps2650/#lab04)

[Back to CMPS 2650](../)
