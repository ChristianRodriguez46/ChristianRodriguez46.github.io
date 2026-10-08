# Utility scripts

**CMPS 2650 Linux Environment and Administration**, Scripts

## What it is

- `move.sh` renames a file by adding today's date before its extension, so `notes.txt` becomes `notes_20251007.txt`.
- `test.sh` prints all its arguments joined by colons, showing how `IFS` changes the way `"$*"` joins arguments.

## Files

| File | What it is |
|---|---|
| [move.sh](move.sh) | Renames a file with today's date before the extension |
| [test.sh](test.sh) | Prints its arguments joined by colons |

## Try it

From this folder:

```bash
bash move.sh notes.txt     # notes.txt -> notes_YYYYMMDD.txt
bash test.sh a b c        # a:b:c
```

Requires: bash on Linux, macOS or WSL, plus `gcc`/`g++` for the C and C++ files.

## Answers

The commands for this lab and what they do are on the answers page: [Scripts answers](https://christianrodriguez46.github.io/Coursework/cmps2650/#scripts)

[Back to CMPS 2650](../)
