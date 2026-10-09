# Prolog: facts, rules and queries

**CMPS 3500 Programming Languages**, Lab 6

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3500/lab06/](https://christianrodriguez46.github.io/Coursework/cmps3500/lab06/)

## What it does

- `lab06.pl` turns nine logical statements about four animals into Prolog rules so the query `likes(X,Y)` can infer which animals like each other.
- `family.pl`, `animals.pl`, `math.pl` and `nested.pl` are smaller examples of facts, recursion and arithmetic. `predicates.txt` and `readme.txt` are reference notes on GNU Prolog.

## How to run

From this folder:

```bash
sudo apt install gprolog   # once
make
./lab06
```

Requires: GNU Prolog (`gprolog` and `gplc`).

## Concepts

- Logic programming
- Unification and backtracking
- Recursion

[Back to CMPS 3500](../)
